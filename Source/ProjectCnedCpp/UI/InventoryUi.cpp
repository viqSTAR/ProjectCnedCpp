// Fill out your copyright notice in the Description page of Project Settings.



#include "ProjectCnedCpp/UI/InventoryUi.h"
#include "ProjectCnedCpp/Character/ActorComponents/ActorInventory.h"
#include "ProjectCnedCpp/UI/SlotUI.h"
#include "ProjectCnedCpp/Item/ItemInstance.h"
#include "Components/VerticalBox.h"


void UInventoryUi::AddItemToInventory()
{
	if (!InventoryComponent)
		return;

	 TArray<TObjectPtr<UItemInstance>> InventoryArray = InventoryComponent->ItemInventory;

	 for (UItemInstance* ItemInstance : InventoryArray)
	 {
		 if (ItemInstance && ItemInstance->Struct.ItemDefinition.GetDefaultObject())
		 {
			 USlotUI* SlotWidget = CreateWidget<USlotUI>(GetWorld(), InventoryItemClass);
			 if (SlotWidget)
			 {
				 SlotWidget->ItemDefinition = ItemInstance->Struct.ItemDefinition.GetDefaultObject();
				 InventoryWrapBox->AddChild(SlotWidget);
			 }
		 }
	 }

}

void UInventoryUi::RemoveItemFromInventory(UUserWidget* Item)
{}

void UInventoryUi::ClearInventory()
{}
