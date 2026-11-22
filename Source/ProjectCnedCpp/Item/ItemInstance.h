// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ProjectCnedCpp/Item/ItemStruct.h"
#include "GameplayTagContainer.h"
#include "ItemInstance.generated.h"

/**
 * 
 */

class UItemDefinition;
UCLASS()
class PROJECTCNEDCPP_API UItemInstance : public UObject
{
	GENERATED_BODY()


public:
	UItemDefinition* ItemDefinition;

	FInventoryItemStruct Struct;


	UItemInstance();

	TMap<FGameplayTag, float> StatsTag;

	void SetStatsTag(FGameplayTag Name, float Value);

	float GetStatsTag(FGameplayTag Tag);

	void Initialize(UItemDefinition* Definition);

	
};
