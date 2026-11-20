// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectCnedCpp/Item/ItemDefs/ItemA.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Texture2D.h"
#include "ProjectCnedCpp/ItemFragments/IF_InteractionType.h"
#include "Engine/StaticMesh.h"


UItemA::UItemA()
{

	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(TEXT("/Game/Assets/ItemIcons/ue.ue"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SMesh(TEXT("/Game/Metal_Sword/Meshes/SM_Metal_Sword.SM_Metal_Sword"));

	ItemName = FText::FromString(TEXT("Item A"));
	ItemDescription = FText::FromString(TEXT("Description for Item A"));

	if (IconTexture.Succeeded())
	{
		Icon = IconTexture.Object;
	}

	if (SMesh.Succeeded())
	{
		Mesh = SMesh.Object;
	}
	FragmentArray.Add(CreateDefaultSubobject<UIF_InteractionType>(TEXT("Interact")));

	
		
	

}
