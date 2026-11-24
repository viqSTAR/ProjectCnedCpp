// Fill out your copyright notice in the Description page of Project Settings.



#include "ProjectCnedCpp/Attack/Attack_Base.h"
#include "GameFramework/Character.h"

void UAttack_Base::ExecuteAttack_Implementation(AActor* Target)
{
	ACharacter* Character = Cast<ACharacter>(Target);

	if (Character && AttackMontage)
	{
		

		UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();

		if (AnimInstance)
		{
			AnimInstance->Montage_Play(AttackMontage);

			
			if (!AttackSections.IsEmpty())
			{
				int32 Section = FMath::RandRange(0, AttackSections.Num() - 1);
				AnimInstance->Montage_JumpToSection(AttackSections[Section], AttackMontage);
			}

		}
	}
}
