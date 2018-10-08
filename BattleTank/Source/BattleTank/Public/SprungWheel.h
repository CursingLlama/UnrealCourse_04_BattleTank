// Copyright Gregory Scott Hanna 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	
	UPROPERTY(VisibleAnywhere, Category = "Setup") class UPhysicsConstraintComponent* SpringConstraint = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Setup") UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup") class USphereComponent* Wheel = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Setup") USphereComponent* Axle = nullptr;
	
	UFUNCTION() void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	float DriveForce = 0;
};