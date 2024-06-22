// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "MyCharacter.h"
#include "EngineUtils.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Containers/Map.h"
// file
//#include "UObject/ConstructorHelpers.h"
//#include "Misc/FileHelper.h"
//#include "Misc/Paths.h"
//#include "HAL/PlatformFilemanager.h"
#include "cubukdenemeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CUBUKDENEME2_API AcubukdenemeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Override the BeginDestroy method
	virtual void BeginDestroy() override;

public:
	AcubukdenemeGameModeBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TArray<AMyCharacter*> Team1Characters;
	TArray<AMyCharacter*> Team2Characters;
	FSocket* ConnectionSocket = nullptr;
	TMap<FString, FVector> ChunckLocations;
	int team1CharacterCount = 0;
	int team2CharacterCount = 0;
	bool ConnectToServer(FString ServerIP, int32 ServerPort);

	FString ReadTextFile();
	void LogCharacterInfo();
	void initCharacters();
	bool ParsePlayerJson(FString JsonString);
	void MoveCharactersToTheirBases();
};
