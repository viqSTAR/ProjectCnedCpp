// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WeaponAttack.generated.h"

class AActor;

class UAnimMontage;
/**
 * 
 */
UCLASS(Blueprintable,BlueprintType,EditInlineNew,DefaultToInstanced)
class PROJECTCNEDCPP_API UWeaponAttack : public UObject
{
	GENERATED_BODY()

protected:
	
public:
	
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	UAnimMontage* AttackMontage;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Attack")
	void ExecuteAttack(AActor* Target);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Details")
	float Damage = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Details")
	float CritDamage = 30.0f;

	

	

	
};
