// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectivesWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class UILEVELDESIGN_API UObjectivesWidgetController : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UMultiLineEditableText* ObjectiveText1;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UMultiLineEditableText* ObjectiveText2;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UMultiLineEditableText* NarrativeMessage;

	// Transient means that: Property is transient, meaning it will not be saved or loaded. 
	// Properties tagged this way will be zero-filled at load time.
	UPROPERTY(BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* NarrativeFadeAnim;

private:
	// Pointers list of the Objective Text lines
	TArray<UMultiLineEditableText*> ListOfObjectivesLines;

	// Reference to HUD for listening to events
	class AExtendedHUD* HudReference;

	virtual void NativeOnInitialized() override;
	//virtual void NativeConstruct() override;

	// This method will double check if we have a valid reference for the Objective Lines in the HUD and return
	// the pointer of the UI element if this exists
	UMultiLineEditableText* GetObjectiveLinePointer(int IndexNumber) const;

	// Methods for set and change information on the HUD

	UFUNCTION()
	void OnDisplayNarrative(bool bShow, FText NewText, float Duration);

	UFUNCTION()
	void SetObjectiveStatus(FText ObjectivePhrase, int ObjectiveIndex, bool bIsObjectiveComplete = false);

	void SetStyleObjective(UMultiLineEditableText* Objective, bool bIsComplete = false);
	void ClearObjectives();
	void ToggleObjective(int ObjectiveIndex, bool bHide, bool bClearOnHide);

public:
	void TestingMethod();
};
