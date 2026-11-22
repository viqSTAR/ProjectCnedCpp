// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCnedCpp/ItemFragments/ItemFragments.h"
#include "GameplayTagContainer.h"
#include "IF_UsesTags.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCNEDCPP_API UIF_UsesTags : public UItemFragments
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TMap<FGameplayTag, float> UsesTag;
	
};
