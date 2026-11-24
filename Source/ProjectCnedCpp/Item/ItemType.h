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
	EITHeal UMETA(DisplayName = "Heal"),
	EITUtility UMETA(DisplayName = "Utility"),
	EITQuest UMETA(DisplayName = "Quest"),
	EITWeapon UMETA(DisplayName = "Weapon")
};
