// Fill out your copyright notice in the Description page of Project Settings.

#include "RotatingActor.h"

ARotatingActor::ARotatingActor()
{
	PrimaryActorTick.bCanEverTick = true;
	RotatorComponent = CreateDefaultSubobject<URotatorComponent>(FName("Rotator"));
}