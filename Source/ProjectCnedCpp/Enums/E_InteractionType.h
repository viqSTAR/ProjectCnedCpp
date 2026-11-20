// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "E_InteractionType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum EInteractionType:uint8
{
	EITpress UMETA(DisplayName = "Press"),
	EIThold UMETA(DisplayName = "Hold"),
	EITtap UMETA(DisplayName = "Tap")
};

UCLASS()
class PROJECTCNEDCPP_API UE_InteractionType : public UObject
{
	GENERATED_BODY()
	
};
