// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyCharacter.generated.h"

#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")
#endif

UCLASS()
class CUBUKDENEME2_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Override the BeginDestroy method
	virtual void BeginDestroy() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetTargetLocation(const FVector& Location);

	void inline SetName(const FString& NewName) { Name = NewName; }

	UFUNCTION(BlueprintCallable, Category = "Character")
	FString GetName() const { return Name; }

	void inline SetID(const int& NewID) { ID = NewID; }
	int inline GetID() const { return ID; }

	void inline SetTeam(const int& NewTeam) { Team = NewTeam; }
	int inline GetTeam() { return Team; }

private:
	// Current target location for movement
	FVector TargetLocation;
	//FSocket* ConnectionSocket = nullptr;
	FString Name;
	int Team;
	int ID;

	float WalkSpeed = 300.0f;

	// Determines if we have a valid target location to move towards
	bool bShouldMove = false;

	void MoveTowardsTarget();

	//bool ConnectToServer();
	//bool ConnectToServer(const FString& ServerIP, int32 ServerPort);

};
