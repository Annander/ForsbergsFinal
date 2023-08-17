// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Inventory/Interactor.h"
#include "../Inventory/Item.h"
#include "PlayerAction.h"
#include "PlayerPawn.generated.h"

UCLASS()
class FORSBERGSFINAL_API APlayerPawn : public APawn, 
	public IPlayerAction
{
	GENERATED_BODY()

private:
	UPROPERTY()
	float CurrentLookRotation;

	UPROPERTY()
	AItem* Inventory;

	UPROPERTY()
	AItem* PossibleItem;

	UPROPERTY()
	TArray<AItem*> Candidates;

	UFUNCTION()
	AItem* LineTraceFromCamera();

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UInteractor* InteractorComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MoveSpeed = 1000.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Radius = 500.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector2D RotationBoundaries = FVector2D(-90.f, 90.f);

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Move(const FVector2D Vector); virtual void Move_Implementation(const FVector2D Vector) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Look(const FVector2D Vector); virtual void Look_Implementation(const FVector2D Vector) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact(); virtual void Interact_Implementation() override;
};