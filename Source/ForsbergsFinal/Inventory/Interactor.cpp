// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactor.h"

// Sets default values for this component's properties
UInteractor::UInteractor()
{
	PrimaryComponentTick.bCanEverTick = false;
	TraceSphere = FCollisionShape::MakeSphere(Radius);
}

TArray<AItem*> UInteractor::GetCandidates()
{
	const auto Owner = GetOwner();

	auto CandidateArray = TArray<AItem*>();
	auto OverlapTest = TArray<FOverlapResult>();

	const auto Origin = Owner->GetActorLocation();

	GetWorld()->OverlapMultiByChannel(
		OverlapTest,
		Origin,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		TraceSphere
	);

	for (auto i = 0; i < OverlapTest.Num(); i++)
	{
		const auto Item = Cast<AItem>(OverlapTest[i].GetActor());

		if (Item)
		{
			CandidateArray.AddUnique(Item);
		}
	}

	return CandidateArray;
}

void UInteractor::Init(float NewRadius)
{
	Radius = NewRadius;
}