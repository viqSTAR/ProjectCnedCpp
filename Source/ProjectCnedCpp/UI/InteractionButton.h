// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/UserWidget.h"
#include "InteractionButton.generated.h"


class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class PROJECTCNEDCPP_API UInteractionButton : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Name;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Description;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Prompt;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Key;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> Progress;

	
};
