// Copyright Gregory Scott Hanna 2018

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime);

protected:
	UPROPERTY(EditDefaultsOnly) float AcceptanceRadius = 8000;

private:
};
