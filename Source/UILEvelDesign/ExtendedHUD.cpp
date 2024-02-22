// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtendedHUD.h"
#include "Blueprint/UserWidget.h"
#include "ObjectivesWidgetController.h"

// Called when the game starts or when spawned
void AExtendedHUD::BeginPlay()
{
	Super::BeginPlay();

	ListTextProgression.Add(FText::FromString(TEXT("Find a way across the river")));

	CharacterController = this->GetOwningPlayerController();

	if (ObjectivesScreen == nullptr || CharacterController == nullptr)
	{
		return;
	}

	UUserWidget* WidgetSpawned = CreateWidget(CharacterController, TSubclassOf<class UUserWidget>(ObjectivesScreen), FName(TEXT("ObjectivesDisplay")));

	if (WidgetSpawned != nullptr)
	{
		WidgetSpawnedExtended = Cast<class UObjectivesWidgetController>(WidgetSpawned);
		if (WidgetSpawnedExtended != nullptr)
		{
			WidgetSpawnedExtended->AddToViewport();
			WidgetSpawnedExtended->TestingMethod();

			OnDisplayNarrativeTrigger.ExecuteIfBound(true, FText::FromString(TEXT("Found myself on the sorroundings of the woods")), 4);
			
			FTimerDelegate TimerDelegate;
			TimerDelegate.BindLambda([&]
				{
					OnSetNewObjectiveText.ExecuteIfBound(ListTextProgression[0], 0, false);
				});

			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 2.5f, false);
		}
	}
}