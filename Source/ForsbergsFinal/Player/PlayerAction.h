// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "PlayerAction.generated.h"

UINTERFACE(Blueprintable, MinimalAPI)
class UPlayerAction : public UInterface
{
	GENERATED_BODY()
};

class FORSBERGSFINAL_API IPlayerAction
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Move(const FVector2D Vector);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Look(const FVector2D Vector);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact();
};