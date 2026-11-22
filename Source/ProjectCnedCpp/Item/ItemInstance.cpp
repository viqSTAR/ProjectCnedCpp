// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectCnedCpp/Item/ItemInstance.h"

#include "ProjectCnedCpp/Item/ItemDefinition.h"
#include "ProjectCnedCpp/ItemFragments/IF_UsesTags.h"

#include <rapidjson/document.h>
UItemInstance::UItemInstance()
{
	//ItemDefinition
}

void UItemInstance::SetStatsTag(FGameplayTag Name, float Value)
{
	StatsTag.Add(Name, Value);
}

float UItemInstance::GetStatsTag(FGameplayTag Tag)
{
	return StatsTag.FindRef(Tag);
}

void UItemInstance::Initialize(UItemDefinition* Definition)
{
	
	Struct.ItemDefinition = Definition->GetClass();
	const UIF_UsesTags* UsesTags = Cast<UIF_UsesTags>(UItemDefinition::FindFragmentByClass(Definition->GetClass(), UIF_UsesTags::StaticClass()));

	if(UsesTags)
	{
		Struct.ItemTags = UsesTags->UsesTag;
	}


	
	
}




