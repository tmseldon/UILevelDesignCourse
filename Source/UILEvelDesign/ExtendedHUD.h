// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ExtendedHUD.generated.h"

/**
 * 
 */
// Example of stadard delegate implementation
//DECLARE_DELEGATE_ThreeParams(FOnDisplayNarrative, bool, FText, float);

// Dynamic delegate implementation for Narrative Box
UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDisplayNarrativeTrigger, bool, bShow, FText, NewText, float, Duration);

// Dynamic delegate implementation for SetObjective
UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnSetNewObjectiveText, FText, ObjectivePhrase, int, ObjectiveIndex, bool, bIsObjectiveComplete);

UCLASS()
class UILEVELDESIGN_API AExtendedHUD : public AHUD
{
	GENERATED_BODY()

private:
	// References for the player
	APlayerController* CharacterController;

	// References for the Objective Text and Narrative box Widget

	class UObjectivesWidgetController* WidgetSpawnedExtended;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Objective Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UObjectivesWidgetController> ObjectivesScreen;

	// Properties and references for the Objective Mark elements

	TArray<class AActor*> ListOfAllObjectiveMarkers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Marker Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AObjectiveMarker> ObjectiveMarkerType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Marker Components", meta = (AllowPrivateAccess = "true"))
	UTexture2D* ObjMarkerFull;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Marker Components", meta = (AllowPrivateAccess = "true"))
	UTexture2D* ObjMarkerHalf;

	void DrawObjectiMarker();

	// List of phrases for the different objectives
	TArray<FText> ListTextProgression;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void DrawHUD() override;

public:
	// Example of standard delegate
	/*FOnDisplayNarrative OnStartDisplayNarrative;*/

	// Delegates for the different events related to the Objective lines and Narrative box

	UPROPERTY()
	FOnDisplayNarrativeTrigger OnDisplayNarrativeTrigger;

	UPROPERTY()
	FOnSetNewObjectiveText OnSetNewObjectiveText;
	
};
