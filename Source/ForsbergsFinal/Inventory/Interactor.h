// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item.h"
#include "Interactor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FORSBERGSFINAL_API UInteractor : public UActorComponent
{
	GENERATED_BODY()

private:
	FCollisionShape TraceSphere;
	float Radius;

public:	
	UInteractor();

	UFUNCTION(BlueprintCallable)
	TArray<AItem*> GetCandidates();

	UFUNCTION()
	void Init(float NewRadius);
};