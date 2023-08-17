// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.generated.h"

UINTERFACE(Blueprintable, MinimalAPI)
class UPickup : public UInterface
{
	GENERATED_BODY()
};

class FORSBERGSFINAL_API IPickup
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Pickup();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void LookEnter();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void LookExit();
};