// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ExtendedHUD.generated.h"

/**
 * 
 */
// Example of stadard delegate implementation
DECLARE_DELEGATE_ThreeParams(FOnDisplayNarrative, bool, FText, float);

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Component", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UObjectivesWidgetController> ObjectivesScreen;

	APlayerController* CharacterController;

	class UObjectivesWidgetController* WidgetSpawnedExtended;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FOnDisplayNarrative OnStartDisplayNarrative;

	UPROPERTY()
	FOnDisplayNarrativeTrigger OnDisplayNarrativeTrigger;

	UPROPERTY()
	FOnSetNewObjectiveText OnSetNewObjectiveText;
	
};
