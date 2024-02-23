// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtendedHUD.h"
#include "ObjectiveMarker.h"
#include "ObjectivesWidgetController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts or when spawned
void AExtendedHUD::BeginPlay()
{
	Super::BeginPlay();

	// Setting all the phrases here
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

	UGameplayStatics::GetAllActorsOfClass(this, ObjectiveMarkerType, ListOfAllObjectiveMarkers);
	/*UE_LOG(LogTemp, Warning, TEXT("The integer value is: %d"), ListOfAllObjectiveMarkers.Num());*/
}

void AExtendedHUD::DrawObjectiMarker()
{
	if (ListOfAllObjectiveMarkers.Num() == 0)
	{
		return;
	}

	AObjectiveMarker* ActiveMarkerToDraw;

	// Getting the Marker reference that is active right now
	for (AActor* Marker : ListOfAllObjectiveMarkers)
	{
		AObjectiveMarker* MarkerReference = Cast<AObjectiveMarker>(Marker);
		if (MarkerReference != nullptr)
		{
			if (MarkerReference->GetEnabled())
			{
				ActiveMarkerToDraw = MarkerReference;
				break;
			}
		}
	}
}

void AExtendedHUD::DrawHUD()
{
	Super::DrawHUD();

	FVector2D ViewPortSize;

	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewPortSize);
	}

	DrawTexture(ObjMarkerFull, 0, 0, ViewPortSize.X, ViewPortSize.Y, 0, 0, 1, 1);


}
