// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectCnedCpp/Enums/E_CharacterState.h"
#include "GameplayTagContainer.h"
#include "CombatComponent.generated.h"


class UAnimInstance;
class USkeletalMeshComponent;
class UItemInstance;
class UItemDefinition;
class UInputAction;
class UAnimMontage;
class AActor;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTCNEDCPP_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECharacterState CharacterState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimInstance> AnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAnimInstance> UnequippedAnimLayer;
	
	UPROPERTY( BlueprintReadWrite)
	TSubclassOf<UAnimInstance> CurrentAnimLayer;

	UPROPERTY(BlueprintReadWrite)
	USkeletalMeshComponent* SmComponent;
	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> DamagedActors;

	void CharacterEquipping(UItemInstance* ItemInst);
	void CharacterUnEquipping();

	void EquipWeapon(int i);
	void UnequipWeapon(int i);

	void WeaponEquipUnEquip(int i);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* EquipSlotA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* EquipSlotB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* AttackA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer GameplayTag;

	UFUNCTION()
	void AttackAStarted();

	UPROPERTY()
	bool bIsAttacking;
	UFUNCTION()
	void HandleOnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);

	UFUNCTION()
	void AttachToSocket(int32 i);
	UFUNCTION()
	void AttachToHostler(int32 i);


	// In CombatComponent.h
	UPROPERTY()
	UItemInstance* PendingEquipItem;

	UPROPERTY()
	int32 EquipIndex;

	UPROPERTY()
	int32 newWeaponIndex;
	UPROPERTY()
	bool bIsEquipping;
	UPROPERTY()
	bool doEquipping;
	UPROPERTY()
	class UStaticMeshComponent* WeaponMeshA;
	UPROPERTY()
	class UStaticMeshComponent* WeaponMeshB;

	UFUNCTION(BlueprintCallable)
	void OnMontageEndedHandler(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UItemDefinition> DefaultAttackDef;

		
};
