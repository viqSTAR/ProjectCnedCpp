// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AIns_Hero.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCNEDCPP_API UAIns_Hero : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	class AHero* Hero;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	class UCharacterMovementComponent* MovementComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float Speed;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector VelocityPlayer;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool IsPlayerFalling;
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool IsPlayerJumped;

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

};
