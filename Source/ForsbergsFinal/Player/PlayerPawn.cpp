// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	CapsuleComponent->InitCapsuleSize(55.f, 96.f);
	CapsuleComponent->SetSimulatePhysics(true);
	
	SetRootComponent(CapsuleComponent);

	constexpr float InertiaTensorScale = 100000.f;
	CapsuleComponent->BodyInstance.InertiaTensorScale = FVector(InertiaTensorScale, InertiaTensorScale, InertiaTensorScale);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CapsuleComponent);
	CameraComponent->SetRelativeLocation(FVector(0, 0, 100.f));

	InteractorComponent = CreateDefaultSubobject<UInteractor>(TEXT("Interactor"));
	InteractorComponent->Init(Radius);
}

void APlayerPawn::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	Candidates = InteractorComponent->GetCandidates();

	for (auto i = 0; i < Candidates.Num(); i++)
	{
		auto Candidate = Candidates[i];
		
		DrawDebugSphere(GetWorld(), Candidate->GetActorLocation(), 100.f, 32, FColor::Green);
		
		// TODO: Perform angular check or use CameraComponent viewport to determine on-screen?
		// TODO: Keep candidate closest to screen center at shortest distance
	}
}

void APlayerPawn::Move_Implementation(const FVector2D Vector)
{
	const auto MoveVector = FVector(Vector.Y, Vector.X, 0.f);

	auto TransformedVector = UKismetMathLibrary::TransformDirection(
		GetActorTransform(),
		MoveVector
	);

	auto DeltaTime = GetWorld()->GetDeltaSeconds();

	TransformedVector *= MoveSpeed;

	SetActorLocation(
		GetActorLocation() +
		TransformedVector * DeltaTime
	);
}

void APlayerPawn::Look_Implementation(const FVector2D Vector)
{
	// Rotate directly on the horizontal axis
	AddActorLocalRotation(
		FRotator(
			0.f,
			Vector.X,
			0.f)
	);

	// Clamp vertical axis
	CurrentLookRotation += Vector.Y;
	CurrentLookRotation = FMath::ClampAngle(
		CurrentLookRotation,
		RotationBoundaries.X,
		RotationBoundaries.Y
	);

	CameraComponent->SetWorldRotation(
		FRotator(
			CurrentLookRotation,
			GetActorRotation().Yaw,
			0.f)
	);

	auto PreviousItem = PossibleItem;
	
	PossibleItem = LineTraceFromCamera();

	if (PreviousItem != PossibleItem && PreviousItem != nullptr)
	{
		IPickup::Execute_LookExit(PreviousItem);
	}

	if (PossibleItem)
	{
		IPickup::Execute_LookEnter(PossibleItem);
	}
}

AItem* APlayerPawn::LineTraceFromCamera()
{
	// TODO: Shoot linecast from camera forward
	auto LineTraceCandidates = TArray<FHitResult>();

	GetWorld()->LineTraceMultiByChannel(
		LineTraceCandidates,
		CameraComponent->GetComponentLocation(),
		CameraComponent->GetComponentLocation() +
		CameraComponent->GetForwardVector() * Radius,
		ECollisionChannel::ECC_GameTraceChannel1
		);

	auto ClosestDistance = TNumericLimits<float>::Max();
	AActor* ClosestCandidate = nullptr;

	for (auto i = 0; i < LineTraceCandidates.Num(); i++)
	{
		auto TraceCandidate = LineTraceCandidates[i].GetActor();
		auto Distance = FVector::Distance(TraceCandidate->GetActorLocation(), GetActorLocation());

		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ClosestCandidate = TraceCandidate;
		}
	};

	if (ClosestCandidate)
	{
		return Cast<AItem>(ClosestCandidate);
	}

	return nullptr;
}

void APlayerPawn::Interact_Implementation()
{
	if (PossibleItem && (PossibleItem != Inventory))
	{
		// If linecast finds item in candidate list, pick it up
		Inventory = PossibleItem;
		IPickup::Execute_Pickup(PossibleItem);
	}
	else
	{
		// If linecast finds nothing, and you have a currently equipped item, throw the currently equipped item away.
		if (Inventory)
		{
			// TODO: Drop item
			Inventory = nullptr;
		}
	}
}