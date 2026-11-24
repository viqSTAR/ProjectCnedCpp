// Fill out your copyright notice in the Description page of Project Settings.



#include "ProjectCnedCpp/UI/WeaponInventory.h"
#include "WeaponInventory.h"
#include "Components/HorizontalBox.h"
#include "ProjectCnedCpp/UI/WeaponSlots.h"
#include "ProjectCnedCpp/Item/ItemInstance.h"
#include "ProjectCnedCpp/Character/ActorComponents/ActorInventory.h"

void UWeaponInventory::AddWeaponToInventory()
{
	if (WeaponInventoryBox)
	{
		WeaponInventoryBox->ClearChildren();

		

		for (UItemInstance* ItemInstance : InventoryRef->WeaponInventory)
		{
			if (ItemInstance)
			{
				UWeaponSlots* WeaponSlotWidget = CreateWidget<UWeaponSlots>(GetWorld(), WeaponSlots);
				if (WeaponSlotWidget)
				{
					WeaponSlotWidget->ItemInstance = ItemInstance;
					WeaponInventoryBox->AddChild(WeaponSlotWidget);
				}
			}
		}
	}
}