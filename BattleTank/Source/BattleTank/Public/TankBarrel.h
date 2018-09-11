// Copyright Gregory Scott Hanna 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup) float MaxDegreesPerSecond = 10.f;
	UPROPERTY(EditDefaultsOnly, Category = Setup) float MaxDegreesElevation = 40.f;
	UPROPERTY(EditDefaultsOnly, Category = Setup) float MinDegreesElevation = 0.f;
};
