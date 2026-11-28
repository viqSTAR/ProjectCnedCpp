// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCnedCpp/ItemFragments/ItemFragments.h"
#include "IF_Attack.generated.h"

class UWeaponAttack;
class UAnimInstance;
class UAnimMontage;
class FHitActor;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UAnimInstance> BaseAnimLayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> EquipMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName SokcetName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName HostlerSokcetName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector SokcetRelativeLocation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FRotator SokcetRelativeRotation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector HostlerSokcetRelativeLocation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FRotator HostlerSokcetRelativeRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector AttackStart;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector AttackEnd;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector HalfSize;
	
	

	

	
};
