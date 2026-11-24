// Fill out your copyright notice in the Description page of Project Settings.



#include "ProjectCnedCpp/UI/SlotUI.h"
#include "ProjectCnedCpp/Item/ItemDefinition.h"
#include "ProjectCnedCpp/Item/ItemInstance.h"
#include "ProjectCnedCpp/Character/ActorComponents/ActorInventory.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"



void USlotUI::NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	Super::NativeOnMouseEnter(MyGeometry, MouseEvent);

	UActorInventory* InventoryRef = Cast<UActorInventory>(GetOwningPlayerPawn()->FindComponentByClass<UActorInventory>());
	if (InventoryRef)
	{
		InventoryRef->usableInstance = ItemInstance;
	}
}

void USlotUI::NativeOnMouseLeave(const FPointerEvent& MouseEvent)
{
	Super::NativeOnMouseLeave(MouseEvent);
	if (GetOwningPlayerPawn())
	{
		UActorInventory* InventoryRef = Cast<UActorInventory>(GetOwningPlayerPawn()->FindComponentByClass<UActorInventory>());
		if (InventoryRef && InventoryRef->usableInstance == ItemInstance)
		{
			InventoryRef->usableInstance = nullptr;
		}
	}
	
}

void USlotUI::NativeConstruct()
{
	if (ItemInstance && ItemInstance->Struct.ItemDefinition)
	{
		ItemDefinition = ItemInstance->Struct.ItemDefinition.GetDefaultObject();
	}
	
	Super::NativeConstruct();
	if (Name)
	{
		Name->SetText(ItemDefinition ? ItemDefinition->ItemName : FText::FromString(TEXT("No Item")));
	}
	if (Image)
	{
		Image->SetBrushFromTexture(ItemDefinition ? ItemDefinition->Icon : nullptr);
	}

	if (StackCount)
	{
		StackCount->SetText(FText::AsNumber(ItemInstance->Struct.StackCount));
	}

}
