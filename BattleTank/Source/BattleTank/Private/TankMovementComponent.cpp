// Copyright Gregory Scott Hanna 2018

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTracktoSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTracktoSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

/*
Turns tank
@param Throw positive turns right, negative turns left (-1,1)
*/
void UTankMovementComponent::IntendTurn(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
