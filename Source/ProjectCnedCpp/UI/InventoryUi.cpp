// Fill out your copyright notice in the Description page of Project Settings.



#include "ProjectCnedCpp/UI/InventoryUi.h"
#include "ProjectCnedCpp/Character/ActorComponents/ActorInventory.h"
#include "ProjectCnedCpp/UI/SlotUI.h"
#include "ProjectCnedCpp/Item/ItemInstance.h"
#include "ProjectCnedCpp/Item/ItemDefinition.h"
#include "ProjectCnedCpp/ItemFragments/IF_ItemType.h"

#include "ProjectCnedCpp/Item/ItemType.h"
#include "Components/VerticalBox.h"


void UInventoryUi::AddItemToInventory()
{
	if (!InventoryComponent)
		return;

	InventoryWrapBox->ClearChildren();
	InventoryWrapBoxUtil->ClearChildren();

	 TArray<TObjectPtr<UItemInstance>> InventoryArray = InventoryComponent->ItemInventory;

	 for (UItemInstance* ItemInstance : InventoryArray)
	 {
		 if (ItemInstance)
		 {
			 USlotUI* SlotWidget = CreateWidget<USlotUI>(GetWorld(), InventoryItemClass);
			 if (SlotWidget)
			 {
				 SlotWidget->ItemInstance = ItemInstance;
				 
				 const UIF_ItemType* ItemTypeFragment = Cast<UIF_ItemType>(UItemDefinition::FindFragmentByClass(ItemInstance->Struct.ItemDefinition, UIF_ItemType::StaticClass())); 

				 EItemType ItemType = ItemTypeFragment ? ItemTypeFragment->ItemType.GetValue() : EItemType::EITItem;
				 if(ItemType == EItemType::EITHeal)		
				 {
					 InventoryWrapBox->AddChild(SlotWidget);
				 }
				 else if (ItemType == EItemType::EITUtility)
				 {
					 InventoryWrapBoxUtil->AddChild(SlotWidget);
				 }
			 }
		 }
	 }
	 

}

void UInventoryUi::RemoveItemFromInventory(UUserWidget* Item)
{}

void UInventoryUi::ClearInventory()
{}
