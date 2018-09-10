// Copyright Gregory Scott Hanna 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float DegreesPerSecond);

private:
	UPROPERTY(EditAnywhere, Category = Setup) float MaxDegreesPerSecond = 20.f;
	UPROPERTY(EditAnywhere, Category = Setup) float MaxDegreesElevation = 45.f;
	UPROPERTY(EditAnywhere, Category = Setup) float MinDegreesElevation = 0.f;
};
