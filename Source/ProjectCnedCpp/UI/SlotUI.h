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
	TObjectPtr<UImage> Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UItemDefinition* ItemDefinition;

	

protected:
	virtual void NativeConstruct() override;

	
};
