// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectCnedCpp/Notifies/AttackNotifyState.h"
#include "ProjectCnedCpp/Character/ActorComponents/ActorInventory.h"
#include "ProjectCnedCpp/Character/ActorComponents/CombatComponent.h"
#include "ProjectCnedCpp/ItemFragments/IF_Attack.h"
#include "ProjectCnedCpp/Item/ItemInstance.h"
#include "ProjectCnedCpp/Item/ItemDefinition.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UAttackNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	//bcanAttack = true;
	AActor* Owner = MeshComp ? MeshComp->GetOwner() : nullptr;
	if (!Owner)
	{
		return;
	}
	//UActorInventory* Inventory = Owner ? Owner->FindComponentByClass<UActorInventory>() : nullptr;
	UCombatComponent* Combat = Owner ? Owner->FindComponentByClass<UCombatComponent>() : nullptr;

	if (!Combat)
	{
		return;
	}


	//bcanAttack = false;
	Combat->DamagedActors.Empty();
	
}

void UAttackNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	AActor* Owner = MeshComp ? MeshComp->GetOwner() : nullptr;
	if (!Owner)
	{
		return;
	}
	UActorInventory* Inventory = Owner ? Owner->FindComponentByClass<UActorInventory>() : nullptr;
	UCombatComponent* Combat = Owner ? Owner->FindComponentByClass<UCombatComponent>() : nullptr;


	
	if (!Inventory || !Combat)
	{
		return;
	}
	int i = Combat->EquipIndex;

	if (!Inventory->WeaponInventory.IsValidIndex(i)) return;
	UItemInstance* ItemInst = Inventory->WeaponInventory[i];

	

	if (!ItemInst)
	{
		return;
	}
	const UIF_Attack* AttackFragment = Cast<UIF_Attack>(UItemDefinition::FindFragmentByClass(ItemInst->Struct.ItemDefinition, UIF_Attack::StaticClass()));
	if (!AttackFragment)
	{
		return;
	}

	if (MeshComp && MeshComp->GetOwner() )
	{
		
		UWorld* World = Owner ? Owner->GetWorld() : nullptr;
		
		if (!World)
		{
			return;
		}

		TArray<AActor*> IgnoredActors;
		IgnoredActors.Add(Owner);

		TArray<FHitResult> HitResults;
		FVector Start = MeshComp->GetSocketLocation(AttackFragment->SokcetName) + AttackFragment->AttackStart;
		FVector End = MeshComp->GetSocketLocation(AttackFragment->SokcetName) + AttackFragment->AttackEnd;

		bool bHit = UKismetSystemLibrary::BoxTraceMulti(
			World,
			Start,
			End,
			AttackFragment->HalfSize,
			MeshComp->GetSocketRotation(AttackFragment->SokcetName),
			UEngineTypes::ConvertToTraceType(ECC_Pawn),
			true,
			IgnoredActors,
			EDrawDebugTrace::ForDuration,
			HitResults,
			true
			);
		if (bHit)
		{
			for (FHitResult HitResult : HitResults)
			{
				AActor* HitActor = HitResult.GetActor();
				if (HitActor && !Combat->DamagedActors.Contains(HitActor))
				{
					Combat->DamagedActors.Add(HitActor);
					UGameplayStatics::ApplyDamage(HitActor, Combat->Damage, Owner->GetInstigatorController(), Owner, nullptr);
				}
			}
		}
		

	}
	


}

void UAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AActor* Owner = MeshComp ? MeshComp->GetOwner() : nullptr;
	if (!Owner)
	{
		return;
	}
	//UActorInventory* Inventory = Owner ? Owner->FindComponentByClass<UActorInventory>() : nullptr;
	UCombatComponent* Combat = Owner ? Owner->FindComponentByClass<UCombatComponent>() : nullptr;

	if (!Combat)
	{
		return;
	}


	//bcanAttack = false;
	Combat->DamagedActors.Empty();
}

FString UAttackNotifyState::GetNotifyName_Implementation() const
{
	return FString("AttackHit");
}
