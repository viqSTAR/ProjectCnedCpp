// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemDefinition.generated.h"

/**
 * 
 */
class UItemFragments;

UCLASS(BlueprintType,Blueprintable, Abstract, Const)
class PROJECTCNEDCPP_API UItemDefinition : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "ItemDetails")
	FText ItemName;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "ItemDetails")
	FText ItemDescription;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "ItemDetails")
	TObjectPtr<UTexture2D> Icon;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "ItemDetails")
	TObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Instanced, Category = "Fragments")
	TArray<TObjectPtr<UItemFragments>> FragmentArray;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DeterminesOutputType = "ItemFragments"))
	static const UItemFragments* FindFragmentByClass(const TSubclassOf<UItemDefinition> ItemDefinition, const TSubclassOf<UItemFragments> ItemFragments);
	
};
