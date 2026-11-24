// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCnedCpp/Attack/WeaponAttack.h"
#include "Attack_Base.generated.h"

class UAnimMontage;
class AActor;
class ACharacter;
/**
 * 
 */
UCLASS()
class PROJECTCNEDCPP_API UAttack_Base : public UWeaponAttack
{
	GENERATED_BODY()
public:
	virtual void ExecuteAttack_Implementation(AActor* Target) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TArray<FName> AttackSections;
	
	
};
