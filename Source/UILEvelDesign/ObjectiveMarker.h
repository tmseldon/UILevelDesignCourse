// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectiveMarker.generated.h"

UCLASS()
class UILEVELDESIGN_API AObjectiveMarker : public AActor
{
	GENERATED_BODY()

private:
	// We change the default root of the Blueprint for another built on the constructor
	UPROPERTY(EditAnywhere)
	USceneComponent* RootScene;

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mark Components", meta = (AllowPrivateAccess = "true"))
	class UBillboardComponent* ObjMarker;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mark Components", meta = (AllowPrivateAccess = "true"))
	class UBillboardComponent* Billboard;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mark Components", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollider;

	// Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mark Status", meta = (AllowPrivateAccess = "true"))
	bool bUseTrigger = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mark Status", meta = (AllowPrivateAccess = "true"))
	bool bEnable = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mark Status", meta = (AllowPrivateAccess = "true"))
	bool bDisabledOnReach = true;
	
public:	
	// Sets default values for this actor's properties
	AObjectiveMarker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
