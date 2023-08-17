// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatorComponent.h"
#include "RotatingActor.generated.h"

UCLASS(Blueprintable, BlueprintType)
class FORSBERGSFINAL_API ARotatingActor : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	URotatorComponent* RotatorComponent;

public:
	ARotatingActor();
};