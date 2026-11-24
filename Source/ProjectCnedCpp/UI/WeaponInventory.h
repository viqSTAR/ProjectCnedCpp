// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "WeaponInventory.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnWeaponChnaged);


class UHorizontalBox;
/**
 * 
 */
UCLASS()
class PROJECTCNEDCPP_API UWeaponInventory : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* WeaponInventoryBox;

	void AddWeaponToInventory();

	FOnWeaponChnaged OnWeaponChanged;

	class UActorInventory* InventoryRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<UUserWidget> WeaponSlots;

	
	
};
