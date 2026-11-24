// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ItemStruct.generated.h"

/**
 *
 */




class UItemDefinition;

USTRUCT(BlueprintType)
struct FInventoryItemStruct
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UItemDefinition> ItemDefinition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StackCount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGameplayTag, float> ItemTags;

	//void SetGameplayTags(FName TagName, float value);

	//float GetValueByTag(FName TagName) const;
	
	

};
