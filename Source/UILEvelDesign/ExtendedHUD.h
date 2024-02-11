// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ExtendedHUD.generated.h"

/**
 * 
 */
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
	
};
