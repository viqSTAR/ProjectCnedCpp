// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCnedCpp/ItemFragments/ItemFragments.h"
#include "ProjectCnedCpp/Enums/E_InteractionType.h"
#include "IF_InteractionType.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCNEDCPP_API UIF_InteractionType : public UItemFragments
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Type")
	TEnumAsByte<EInteractionType> InteractionType = EITpress;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Property")
	float ItemCounter = 1.f;
};
