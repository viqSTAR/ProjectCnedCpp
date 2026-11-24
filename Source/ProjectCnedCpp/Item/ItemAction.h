// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType,EditInlineNew,DefaultToInstanced)
class PROJECTCNEDCPP_API UItemAction : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Use(AActor* Target);
	
};
