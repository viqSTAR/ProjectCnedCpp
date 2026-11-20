// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectCnedCpp/Character/AIns_Hero.h"
#include "ProjectCnedCpp/Character/Hero.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"



void UAIns_Hero::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Hero = Cast<AHero>(TryGetPawnOwner());

	if (Hero)
	{
		MovementComponent = Hero->GetCharacterMovement();
	}
}

void UAIns_Hero::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (MovementComponent)
	{
		Speed = UKismetMathLibrary::VSizeXY(MovementComponent->Velocity);
		VelocityPlayer = MovementComponent->Velocity;
		IsPlayerFalling = MovementComponent->IsFalling();
	}
	if (Hero)
	{
		IsPlayerJumped = Hero->IsJumping;
	}
}


