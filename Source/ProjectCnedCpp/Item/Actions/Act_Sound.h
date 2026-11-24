// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectCnedCpp/Item/ItemAction.h"
#include "Act_Sound.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCNEDCPP_API UAct_Sound : public UItemAction
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundBase* Sound;

	virtual void Use_Implementation(AActor* Actor) override;
	
};
