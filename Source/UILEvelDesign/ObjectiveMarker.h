// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectiveMarker.generated.h"

//NOTE: maybe for this one shpuld be Multicast DECLARE_MULTICAST_DELEGATE(FOnObjetiveMarkerReached);
DECLARE_DELEGATE(FOnObjetiveMarkerReached);
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

	// If the collider is active or not
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mark Status", meta = (AllowPrivateAccess = "true"))
	bool bUseTrigger = true;

	// If the objective is active to interact with the marker
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mark Status", meta = (AllowPrivateAccess = "true"))
	bool bEnable = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mark Status", meta = (AllowPrivateAccess = "true"))
	bool bDisabledOnReach = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mark Status", meta = (AllowPrivateAccess = "true"))
	//TSubclassOf<class AObjectiveMarker> NextMarker;
	AObjectiveMarker* NextMarker;

	// Flag for making check once on OnComponentBeginOverlap event
	bool bIsFirstCheck = true;

	// Methods

	void OnConstruction(const FTransform& Transform) override;

	void ToogleBoxCollider(bool bIsActive);

	UFUNCTION()
	void ManageMarkerTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AObjectiveMarker();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Delegate for the event when player reaches the marker
	FOnObjetiveMarkerReached OnReachedToMarker;

	void EnableObjectiveMarker(bool bChangeEnable, bool bChangeDisabledOnReach);	
};
