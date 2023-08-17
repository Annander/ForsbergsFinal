// Fill out your copyright notice in the Description page of Project Settings.
#include "RotatorComponent.h"

URotatorComponent::URotatorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	//Owner = GetOwner();
}

void URotatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*
	FRotator TickRotation = FRotator(0, RotationSpeed * DeltaTime, 0);
	Owner->AddActorWorldRotation(TickRotation);
	*/

	auto Owner = GetOwner();
	auto Rotator = FRotator(0.f, RotationSpeed * DeltaTime, 0.f);

	Owner->AddActorLocalRotation(Rotator);
}