// Fill out your copyright notice in the Description page of Project Settings.



#include "ProjectCnedCpp/UI/SlotUI.h"
#include "ProjectCnedCpp/Item/ItemDefinition.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"



void USlotUI::NativeConstruct()
{
	Super::NativeConstruct();
	if (Name)
	{
		Name->SetText(ItemDefinition ? ItemDefinition->ItemName : FText::FromString(TEXT("No Item")));
	}
	if (Image)
	{
		Image->SetBrushFromTexture(ItemDefinition ? ItemDefinition->Icon : nullptr);
	}

}
