// Fill out your copyright notice in the Description page of Project Settings.



#include "ProjectCnedCpp/Character/ActorComponents/CombatComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "ProjectCnedCpp/ItemFragments/IF_Attack.h"
#include "ProjectCnedCpp/Item/ItemDefinition.h"
#include "ProjectCnedCpp/Item/ItemInstance.h"
#include "EnhancedInputComponent.h"
#include "ProjectCnedCpp/Character/ActorComponents/ActorInventory.h"
#include "Components/StaticMeshComponent.h"
#include "ProjectCnedCpp/Attack/WeaponAttack.h"
#include "ProjectCnedCpp/Notifies/MovementTags.h"


// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();



	if (GetOwner())
	{
		WeaponMeshA = NewObject<UStaticMeshComponent>(GetOwner());
		WeaponMeshA->RegisterComponent();
		WeaponMeshA->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		WeaponMeshA->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		WeaponMeshB = NewObject<UStaticMeshComponent>(GetOwner());
		WeaponMeshB->RegisterComponent();
		WeaponMeshB->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		WeaponMeshB->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	bIsEquipping = false;
	doEquipping = false;
	bIsAttacking = false;
	// ...
	CharacterState = ECharacterState::ECSUnequipped;

	if (GetOwner())
	{
		
		EquipIndex = -1;
		UEnhancedInputComponent* Enhanced = GetOwner()->FindComponentByClass<UEnhancedInputComponent>();
		if(Enhanced && EquipSlotA && EquipSlotB && AttackA)
		{
			Enhanced->BindAction(EquipSlotA, ETriggerEvent::Started, this, &UCombatComponent::WeaponEquipUnEquip, 0);
			Enhanced->BindAction(EquipSlotB, ETriggerEvent::Started, this, &UCombatComponent::WeaponEquipUnEquip, 1);
			Enhanced->BindAction(AttackA, ETriggerEvent::Started, this, &UCombatComponent::AttackAStarted);
		}
		
		SmComponent = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
		if (SmComponent)
		{
			AnimInstance = SmComponent->GetAnimInstance();
		}
		if (AnimInstance)
		{
			AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UCombatComponent::HandleOnMontageNotifyBegin);

			AnimInstance->OnMontageEnded.AddDynamic(this, &UCombatComponent::OnMontageEndedHandler);

			
		}
		
	}

	if (AnimInstance && SmComponent && UnequippedAnimLayer && CharacterState == ECharacterState::ECSUnequipped)
	{
		CurrentAnimLayer = UnequippedAnimLayer;
		SmComponent->LinkAnimClassLayers(CurrentAnimLayer);
	}
	
}




// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombatComponent::CharacterEquipping(UItemInstance* ItemInst)
{
	if (AnimInstance && SmComponent && UnequippedAnimLayer && CharacterState == ECharacterState::ECSEquipped && ItemInst)
	{
		const UIF_Attack* AttackFragment = Cast<UIF_Attack>(UItemDefinition::FindFragmentByClass(ItemInst->Struct.ItemDefinition, UIF_Attack::StaticClass()));

		if (CurrentAnimLayer)
		{
			SmComponent->UnlinkAnimClassLayers(CurrentAnimLayer);
		}

		if (AttackFragment && AttackFragment->BaseAnimLayer)
		{
			CurrentAnimLayer = AttackFragment->BaseAnimLayer;
		}
		else
		{

			CurrentAnimLayer = UnequippedAnimLayer;
		}
		SmComponent->LinkAnimClassLayers(CurrentAnimLayer);
		AnimInstance->RequestSlotGroupInertialization(FName("DefaultGroup"), 0.35f);
	}
}

void UCombatComponent::CharacterUnEquipping()
{
	if (AnimInstance && SmComponent && UnequippedAnimLayer && CharacterState == ECharacterState::ECSUnequipped)
	{
		SmComponent->UnlinkAnimClassLayers(CurrentAnimLayer);
		CurrentAnimLayer = UnequippedAnimLayer;
		SmComponent->LinkAnimClassLayers(CurrentAnimLayer);
		AnimInstance->RequestSlotGroupInertialization(FName("DefaultGroup"), 0.35f);
	}
}

void UCombatComponent::EquipWeapon(int i)
{
	
	UActorInventory* Inventory = GetOwner()->FindComponentByClass<UActorInventory>();

	UItemInstance* ItemInst = nullptr;
	

	if (Inventory && Inventory->WeaponInventory.IsValidIndex(i))
	{
		ItemInst = Inventory->WeaponInventory[i];
	}

	if (!ItemInst || !AnimInstance) return;
	
	

	const UIF_Attack* AttackFragment = Cast<UIF_Attack>(UItemDefinition::FindFragmentByClass(ItemInst->Struct.ItemDefinition, UIF_Attack::StaticClass()));

	if (AttackFragment && AttackFragment->EquipMontage)
	{
		AnimInstance->Montage_Play(AttackFragment->EquipMontage);
		AnimInstance->Montage_JumpToSection(FName("Equip"), AttackFragment->EquipMontage);
		PendingEquipItem = ItemInst;
	
		EquipIndex = i;
		
	}

}

void UCombatComponent::UnequipWeapon(int i)
{

	UActorInventory* Inventory = GetOwner()->FindComponentByClass<UActorInventory>();
	
	UItemInstance* ItemInst = nullptr;
	

	if (Inventory && Inventory->WeaponInventory.IsValidIndex(i))
	{
		ItemInst = Inventory->WeaponInventory[i];
	}

	if (!ItemInst || !AnimInstance) return;

	const UIF_Attack* AttackFragment = Cast<UIF_Attack>(UItemDefinition::FindFragmentByClass(ItemInst->Struct.ItemDefinition, UIF_Attack::StaticClass()));

	if (AttackFragment && AttackFragment->EquipMontage)
	{
		AnimInstance->Montage_Play(AttackFragment->EquipMontage);
		AnimInstance->Montage_JumpToSection(FName("Unequip"), AttackFragment->EquipMontage);
		
		
		
	}
	
}

void UCombatComponent::WeaponEquipUnEquip(int i)
{
	if (bIsAttacking || bIsEquipping)
	{
		return;
	}
	
	UActorInventory* Inventory = GetOwner()->FindComponentByClass<UActorInventory>();
	UItemInstance* ItemInst = nullptr;
	if (!Inventory || !Inventory->WeaponInventory.IsValidIndex(i) || !Inventory->WeaponInventory[i])
	{
		return;
	}
	
	TSubclassOf<UAnimInstance> AnimLayer = nullptr;
	if (Inventory && Inventory->WeaponInventory.IsValidIndex(i))
	{
		ItemInst = Inventory->WeaponInventory[i];
		
	}

	bIsEquipping = true;
	
	if (i == EquipIndex)
	{
		UnequipWeapon(i);
	}
	else
	{
		if (CharacterState == ECharacterState::ECSEquipped)
		{
			
			UnequipWeapon(EquipIndex);
			newWeaponIndex = i;
			doEquipping = true;
		}
		else
		{
			newWeaponIndex = i;
			EquipWeapon(i);
		}
		
	}
}

void UCombatComponent::AttackAStarted()
{
	if(bIsEquipping || bIsAttacking || bIsEquipping)
	{
		return;
	}

	
	
	int i = EquipIndex;
	UActorInventory* Inventory = GetOwner()->FindComponentByClass<UActorInventory>();
	if (CharacterState == ECharacterState::ECSUnequipped)
	{
		const UIF_Attack* AttackFragment = Cast<UIF_Attack>(UItemDefinition::FindFragmentByClass(DefaultAttackDef, UIF_Attack::StaticClass()));
		if (AttackFragment && AttackFragment->BaseWeaponAttack)
		{

			AttackFragment->BaseWeaponAttack->ExecuteAttack(GetOwner());
			float Chance = FMath::RandRange(0.0f, 100.0f);


			if (Chance < 25.0f) // 25% chance for critical hit
			{
				Damage = AttackFragment->BaseWeaponAttack->CritDamage;
			}
			else
			{
				Damage = AttackFragment->BaseWeaponAttack->Damage;
			}
			bIsAttacking = true;
			GameplayTag.AddTag(MovementTags::TAG_State_DontMove_Attacking);
		}
		return;
	}

	if (Inventory)
	{
		UItemInstance* ItemInst = nullptr;
		

		if (Inventory->WeaponInventory.IsValidIndex(i) && Inventory->WeaponInventory[i])
		{
			ItemInst = Inventory->WeaponInventory[i];
			
			const UIF_Attack* AttackFragment = Cast<UIF_Attack>(UItemDefinition::FindFragmentByClass(ItemInst->Struct.ItemDefinition, UIF_Attack::StaticClass()));
			if (AttackFragment && AttackFragment->BaseWeaponAttack)
			{

				AttackFragment->BaseWeaponAttack->ExecuteAttack(GetOwner());
				float Chance = FMath::RandRange(0.0f, 100.0f);


				if (Chance < 25.0f) // 25% chance for critical hit
				{
					Damage = AttackFragment->BaseWeaponAttack->CritDamage;
				}
				else
				{
					Damage = AttackFragment->BaseWeaponAttack->Damage;
				}
				bIsAttacking = true;
				GameplayTag.AddTag(MovementTags::TAG_State_DontMove_Attacking);
			}
		}

		
	}
}

void UCombatComponent::HandleOnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	if (NotifyName == FName("Unequip"))
	{
		CharacterState = ECharacterState::ECSUnequipped;
		UCombatComponent::CharacterUnEquipping();
		AttachToHostler(EquipIndex);
		EquipIndex = -1;
		if (doEquipping)
		{
			UCombatComponent::EquipWeapon(newWeaponIndex);
			doEquipping = false;
			
		}
		else{ bIsEquipping = false; }
		
	}
	else if (NotifyName == FName("Equip") && PendingEquipItem)
	{
		CharacterState = ECharacterState::ECSEquipped;
		UCombatComponent::CharacterEquipping(PendingEquipItem);
		bIsEquipping = false;
		AttachToSocket(EquipIndex);

	}
	else if (NotifyName == FName("Attack"))
	{
		bIsAttacking = false;
		
	}
}

void UCombatComponent::AttachToSocket(int32 i)
{
	UActorInventory* Inventory = GetOwner()->FindComponentByClass<UActorInventory>();
	
	if (Inventory && Inventory->WeaponInventory.IsValidIndex(i) && Inventory->WeaponInventory[i] && SmComponent)
	{
		const UIF_Attack* AttackFragment = Cast<UIF_Attack>(UItemDefinition::FindFragmentByClass(Inventory->WeaponInventory[i]->Struct.ItemDefinition, UIF_Attack::StaticClass()));
		FName SocketName = AttackFragment ? AttackFragment->SokcetName : FName();

		UItemInstance* ItemInst = Inventory->WeaponInventory[i];
		if (ItemInst && WeaponMeshA && WeaponMeshB && ItemInst->Struct.ItemDefinition)
		{
			UStaticMeshComponent* WeaponMesh = (i == 0) ? WeaponMeshA : WeaponMeshB;
			WeaponMesh->SetStaticMesh(ItemInst->Struct.ItemDefinition->GetDefaultObject<UItemDefinition>()->Mesh);
			WeaponMesh->AttachToComponent(SmComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
			WeaponMesh->SetRelativeRotation(AttackFragment ? AttackFragment->SokcetRelativeRotation : FRotator::ZeroRotator);
			WeaponMesh->SetRelativeLocation(AttackFragment ? AttackFragment->SokcetRelativeLocation : FVector::ZeroVector);

		}
		
	}
	
}

void UCombatComponent::AttachToHostler(int32 i)
{

	UActorInventory* Inventory = GetOwner()->FindComponentByClass<UActorInventory>();

	if (Inventory && Inventory->WeaponInventory.IsValidIndex(i) && Inventory->WeaponInventory[i] && SmComponent)
	{
		const UIF_Attack* AttackFragment = Cast<UIF_Attack>(UItemDefinition::FindFragmentByClass(Inventory->WeaponInventory[i]->Struct.ItemDefinition, UIF_Attack::StaticClass()));
		FName SocketName = AttackFragment ? AttackFragment->HostlerSokcetName : FName();

		UItemInstance* ItemInst = Inventory->WeaponInventory[i];
		if (ItemInst && WeaponMeshA && WeaponMeshB && ItemInst->Struct.ItemDefinition)
		{
			UStaticMeshComponent* WeaponMesh = (i == 0) ? WeaponMeshA : WeaponMeshB;
			WeaponMesh->SetStaticMesh(ItemInst->Struct.ItemDefinition->GetDefaultObject<UItemDefinition>()->Mesh);
			WeaponMesh->AttachToComponent(SmComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
			WeaponMesh->SetRelativeRotation(AttackFragment ? AttackFragment->HostlerSokcetRelativeRotation : FRotator::ZeroRotator);
			WeaponMesh->SetRelativeLocation(AttackFragment ? AttackFragment->HostlerSokcetRelativeLocation : FVector::ZeroVector);

		}

	}
}



void UCombatComponent::OnMontageEndedHandler(UAnimMontage* Montage, bool bInterrupted)
{
	if (!bInterrupted)
	{
		bIsEquipping = false;
		doEquipping = false;
		bIsAttacking = false;
		GameplayTag.RemoveTag(MovementTags::TAG_State_DontMove_Attacking);
	}
	if (AnimInstance && AnimInstance->GetCurrentActiveMontage() != Montage)
	{
		bIsAttacking = false;
		GameplayTag.RemoveTag(MovementTags::TAG_State_DontMove_Attacking);
	}
	if(AnimInstance && !AnimInstance->GetCurrentActiveMontage())
	{
		bIsEquipping = false;
		doEquipping = false;
	}
}

