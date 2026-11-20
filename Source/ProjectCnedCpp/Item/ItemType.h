// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum EItemType : uint8
{
	EITItem UMETA(DisplayName = "Item"),
	EITHeal UMETA(DisplayName = "Item"),
	EITQuest UMETA(DisplayName = "Item"),
	EITWeapon UMETA(DisplayName = "Item")
};
