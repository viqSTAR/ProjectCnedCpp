// Fill out your copyright notice in the Description page of Project Settings.



#include "ProjectCnedCpp/ItemFragments/IF_ItemAction.h"
#include "ProjectCnedCpp/Item/ItemAction.h"

void UIF_ItemAction::UseItemAction(AActor* Target) const
{
	for (UItemAction* Action : ItemActions)
	{
		if (Action)
		{
			Action->Use(Target);
		}
	}
}
