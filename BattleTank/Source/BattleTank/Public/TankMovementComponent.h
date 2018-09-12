// Copyright Gregory Scott Hanna 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input) void IntendMoveForward(float Throw);
	UFUNCTION(BlueprintCallable, Category = Input) void IntendTurn(float Throw);
	UFUNCTION(BluePrintCallable, Category = Setup) void Initialize(UTankTrack* Left, UTankTrack* Right);

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
	
};
