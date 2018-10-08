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
	UTankTrack();
	UFUNCTION(BlueprintCallable, Category = "Input") void SetThrottle(float Throttle);

protected:
	virtual void BeginPlay() override;
			
private:
	void DriveTrack(float CurrentThrottle);

	UPROPERTY(EditDefaultsOnly) float MaxDrivingForce = 30000000;
	
	TArray<class ASprungWheel*> GetWheels() const;
	
};
