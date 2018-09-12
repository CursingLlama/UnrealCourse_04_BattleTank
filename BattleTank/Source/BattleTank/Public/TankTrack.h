// Copyright Gregory Scott Hanna 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input) void SetThrottle(float Throttle);
	
private:
	UPROPERTY(EditDefaultsOnly) float MaxTrackDrivingForce = 400000;
};