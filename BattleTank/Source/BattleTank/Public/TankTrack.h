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
	UFUNCTION() void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	void CounteractSidewaysForce();
	void DriveTrack();

	UPROPERTY(EditDefaultsOnly) float MaxDrivingForce = 30000000;
	float CurrentThrottle = 0;
};
