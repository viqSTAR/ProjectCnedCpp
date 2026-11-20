// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectCnedCpp/Item/ItemDefinition.h"

#include "ProjectCnedCpp/ItemFragments/ItemFragments.h"

const UItemFragments* UItemDefinition::FindFragmentByClass(const TSubclassOf<UItemDefinition> ItemDefinition, const TSubclassOf<UItemFragments> ItemFragments)
{
	if (!ItemDefinition) return nullptr;

	UItemDefinition* ItemCDO = ItemDefinition.GetDefaultObject();

	for (const UItemFragments* Fragment : ItemCDO->FragmentArray)
	{
		if (Fragment->IsA(ItemFragments))
		{
			return Fragment;
		}
	}
	return nullptr;
}
