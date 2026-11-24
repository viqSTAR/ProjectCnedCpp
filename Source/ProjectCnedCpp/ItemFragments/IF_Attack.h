// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCnedCpp/ItemFragments/ItemFragments.h"
#include "IF_Attack.generated.h"

class UWeaponAttack;
/**
 * 
 */
UCLASS()
class PROJECTCNEDCPP_API UIF_Attack : public UItemFragments
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Instanced)
	TObjectPtr<UWeaponAttack> BaseWeaponAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Instanced)
	TObjectPtr<UWeaponAttack> JumpWeaponAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Instanced)
	TObjectPtr<UWeaponAttack> ProjectileWeaponAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Instanced)
	TObjectPtr<UWeaponAttack> UltimateWeaponAttack;

	
};
