// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeaponSlots.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECTCNEDCPP_API UWeaponSlots : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
	UImage* WeaponImage;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeaponName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemsCPP")
	class UItemDefinition* ItemDefinition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemsCPP")
	class UItemInstance* ItemInstance;


protected:
	void NativeConstruct() override;
	
	
};
