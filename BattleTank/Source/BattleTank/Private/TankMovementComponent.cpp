// Copyright Gregory Scott Hanna 2018

#include "TankMovementComponent.h"

#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTracktoSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTracktoSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector ForwardIntent = MoveVelocity.GetSafeNormal();
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	IntendTurn(FVector::CrossProduct(TankForward, ForwardIntent).Z);
	IntendMoveForward(FVector::DotProduct(ForwardIntent, TankForward));
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

/*
* Turns tank
* @param Throw positive turns right, negative turns left (-1,1)
*/
void UTankMovementComponent::IntendTurn(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
