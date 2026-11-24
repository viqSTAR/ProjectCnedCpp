// Fill out your copyright notice in the Description page of Project Settings.



#include "ProjectCnedCpp/UI/WeaponSlots.h"
#include "ProjectCnedCpp/Item/ItemDefinition.h"
#include "ProjectCnedCpp/Item/ItemInstance.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UWeaponSlots::NativeConstruct()
{
	Super::NativeConstruct();
	if (ItemInstance && ItemInstance->Struct.ItemDefinition)
	{
		ItemDefinition = ItemInstance->Struct.ItemDefinition.GetDefaultObject();
	}
	
	

	if (WeaponName)
	{
		WeaponName->SetText(ItemDefinition ? ItemDefinition->ItemName : FText::FromString(TEXT("No Item")));
	}
	if (WeaponImage)
	{
		WeaponImage->SetBrushFromTexture(ItemDefinition ? ItemDefinition->Icon : nullptr);
	}
}
