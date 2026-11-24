// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlotUI.generated.h"



class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class PROJECTCNEDCPP_API USlotUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Name;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StackCount;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemsCPP")
	class UItemDefinition* ItemDefinition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemsCPP")
	class UItemInstance* ItemInstance;

	virtual void NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& MouseEvent) override;


	

protected:
	virtual void NativeConstruct() override;

	
};
