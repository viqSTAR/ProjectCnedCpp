// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCnedCpp/ItemFragments/ItemFragments.h"
#include "IF_ItemAction.generated.h"

class UItemAction;
/**
 * 
 */
UCLASS()
class PROJECTCNEDCPP_API UIF_ItemAction : public UItemFragments
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Instanced,BlueprintReadOnly)
	TArray<UItemAction*> ItemActions;

	UFUNCTION(BlueprintCallable)
	void UseItemAction(AActor* Target) const;
	
};
