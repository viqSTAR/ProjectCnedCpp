// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemInfo.generated.h"

/**
 * 
 */

class UItemDefinition;

USTRUCT(BlueprintType)
struct FInventoryItemInfo
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UItemDefinition> ItemDefinition;
	
};
