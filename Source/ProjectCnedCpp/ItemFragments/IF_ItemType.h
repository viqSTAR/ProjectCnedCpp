// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCnedCpp/ItemFragments/ItemFragments.h"
#include "ProjectCnedCpp/Item/ItemType.h"
#include "IF_ItemType.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCNEDCPP_API UIF_ItemType : public UItemFragments
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EItemType> ItemType = EITItem;
	
};
