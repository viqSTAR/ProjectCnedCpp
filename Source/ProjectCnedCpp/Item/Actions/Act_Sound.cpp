// Fill out your copyright notice in the Description page of Project Settings.



#include "ProjectCnedCpp/Item/Actions/Act_Sound.h"
#include "Act_Sound.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

void UAct_Sound::Use_Implementation(AActor* Actor)
{
	if (Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(Actor, Sound, Actor->GetActorLocation());
	}
}
