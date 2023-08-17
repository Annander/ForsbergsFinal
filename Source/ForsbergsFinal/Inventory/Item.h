#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.h"
#include "Item.generated.h"

UCLASS(BlueprintType, Blueprintable)
class FORSBERGSFINAL_API AItem : public AActor,
	public IPickup
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Pickup(); virtual void Pickup_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void LookEnter(); virtual void LookEnter_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void LookExit(); virtual void LookExit_Implementation() override;
};