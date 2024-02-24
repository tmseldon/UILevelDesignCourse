// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtendedHUD.h"
#include "ObjectiveMarker.h"
#include "ObjectivesWidgetController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

// Called when the game starts or when spawned
void AExtendedHUD::BeginPlay()
{
	Super::BeginPlay();

	// Init all the required components
	// Init Objective Widget Section:

	CharacterController = this->GetOwningPlayerController();

	if (ObjectivesScreen == nullptr || CharacterController == nullptr)
	{
		return;
	}

	// Setting all the phrases here
	ListTextProgression.Add(FText::FromString(TEXT("Find a way across the river")));




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

	// Init Objective Markers section

	// Getting all the Objective Markers pointers
	UGameplayStatics::GetAllActorsOfClass(this, ObjectiveMarkerType, ListOfAllObjectiveMarkers);

	if (ListOfAllObjectiveMarkers.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Check the scene for non exisiting references for Objective Markers: %d"), ListOfAllObjectiveMarkers.Num());
	}

	//Getting information about the ViewPort
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewPortSize);
	}
}

void AExtendedHUD::DrawHUD()
{
	Super::DrawHUD();

	AObjectiveMarker* MarkerToDraw = GetActiveObjectiveMarker();

	if (MarkerToDraw != nullptr)
	{
		DrawMarker(MarkerToDraw);
	}
}

AObjectiveMarker* AExtendedHUD::GetActiveObjectiveMarker() const
{
	if (ListOfAllObjectiveMarkers.Num() == 0)
	{
		return nullptr;
	}

	AObjectiveMarker* ActiveMarkerToDraw = nullptr;

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

	return ActiveMarkerToDraw;
}

void AExtendedHUD::DrawMarker(AObjectiveMarker* ActiveMarker)
{
	FVector ActiveMarkerLocation = ActiveMarker->GetActorLocation();
	FVector LocationOffset = FVector(0, 0, 180);
	ActiveMarkerLocation += LocationOffset;

	FVector2D ActiveMarkerLocToScreen;
	CharacterController->ProjectWorldLocationToScreen(ActiveMarkerLocation, ActiveMarkerLocToScreen);

	// Update some of the params needed for the marker drawing
	MarkerParams.ScreenX = FMath::Clamp(ActiveMarkerLocToScreen.X, 0, ViewPortSize.X * 0.95f);
	MarkerParams.ScreenY = FMath::Clamp(ActiveMarkerLocToScreen.Y, 0, ViewPortSize.Y * 0.9f);
	UTexture2D* DrawingMarker = GetMarkerTextureToDraw(ActiveMarkerLocToScreen, MarkerParams.Rotation);

	DrawTexture(
		DrawingMarker,
		MarkerParams.ScreenX,
		MarkerParams.ScreenY,
		MarkerParams.ScreenH,
		MarkerParams.ScreenW ,
		MarkerParams.TextureU,
		MarkerParams.TextureV,
		MarkerParams.TextureUWidth,
		MarkerParams.TextureUWidth,
		MarkerParams.TintColor,
		MarkerParams.BlendMode,
		MarkerParams.Scale,
		MarkerParams.bScalePosition,
		MarkerParams.Rotation,
		MarkerParams.RotPivot
	);
}

UTexture2D* AExtendedHUD::GetMarkerTextureToDraw(FVector2D MarkerScreenPos, float& Rotation)
{
	UTexture2D* TextureToDraw = ObjMarkerFull;
	Rotation = 0;
	
	bool bIsOffscreenHorizontal = MarkerScreenPos.X > ViewPortSize.X * 0.95f || MarkerScreenPos.X < 5.0f;
	bool bIsOffScreenVertical = MarkerScreenPos.Y > ViewPortSize.X * 0.9f || MarkerScreenPos.Y < 5.0f;

	if (bIsOffscreenHorizontal)
	{
		TextureToDraw = ObjMarkerHalf;
		if (MarkerScreenPos.X < 5.f)
		{
			Rotation = 180.f;
		}
	}
	else
	{
		if (bIsOffScreenVertical)
		{
			TextureToDraw = ObjMarkerHalf;

			if (MarkerScreenPos.Y < 5.f)
			{
				Rotation = -90.f;
			}
			else
			{
				Rotation = 90.f;
			}
		}
	}

	return TextureToDraw;
}
