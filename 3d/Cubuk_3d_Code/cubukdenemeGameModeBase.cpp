// Copyright Epic Games, Inc. All Rights Reserved.


#include "cubukdenemeGameModeBase.h"

AcubukdenemeGameModeBase::AcubukdenemeGameModeBase()
{
	this->ChunckLocations.Add("b2", FVector(680, 940, 0));
	this->ChunckLocations.Add("b1", FVector(2400, 940, 0));
	this->ChunckLocations.Add("a1", FVector(2400, 1410, 0));
	this->ChunckLocations.Add("a2", FVector(1880, 1410, 0));
	this->ChunckLocations.Add("a3", FVector(1330, 1410, 0));
	this->ChunckLocations.Add("a4", FVector(500, 1410, 0));
	this->ChunckLocations.Add("a5", FVector(500, 400, 0));
	this->ChunckLocations.Add("a6", FVector(1320, 400, 0));
	this->ChunckLocations.Add("a7", FVector(1870, 400, 0));
	this->ChunckLocations.Add("a8", FVector(2560, 400, 0));

	PrimaryActorTick.bCanEverTick = true;
}

FString AcubukdenemeGameModeBase::ReadTextFile()
{
	FString FilePath = TEXT("C:/cubuk/config.txt");

	FString FileContents;

	if (FFileHelper::LoadFileToString(FileContents, *FilePath))
	{
		UE_LOG(LogTemp, Log, TEXT("File read successfully: %s"), *FileContents);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("File read successfully: %s"), *FileContents));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to read file: %s"), *FilePath);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Failed to read file: %s"), *FilePath));
		}
	}

	return FileContents;
}

// Called when the game starts
void AcubukdenemeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	this->initCharacters();

	FString IP = this->ReadTextFile();

	if (IP == TEXT(""))
	{
		FGenericPlatformMisc::RequestExit(false);
		return;
	}

	if (ConnectToServer(IP, 8080) && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, TEXT("Connected to server"));
		ConnectionSocket->SetNonBlocking(true);
	}
	else if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Failed to connect to server"));
	}
}

void AcubukdenemeGameModeBase::initCharacters()
{
	UWorld* World = GetWorld();
	if (!World) return;

	int wteam = 0;
	for (TActorIterator<AMyCharacter> It(World, AMyCharacter::StaticClass()); It; ++It)
	{
		AMyCharacter* Character = *It;
		if (Character)
		{
			if (wteam < 2)
				Team1Characters.Add(Character);
			else
				Team2Characters.Add(Character);
			++wteam;
		}
	}
}

bool AcubukdenemeGameModeBase::ConnectToServer(FString ServerIP, int32 ServerPort)
{
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	if (!SocketSubsystem)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get socket subsystem."));
		return false;
	}

	// Create socket
	FIPv4Address IP;
	FIPv4Address::Parse(ServerIP, IP);
	TSharedRef<FInternetAddr> Addr = SocketSubsystem->CreateInternetAddr();
	Addr->SetIp(IP.Value);
	Addr->SetPort(ServerPort);

	ConnectionSocket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("TCPClient"), false);
	if (!ConnectionSocket)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create socket."));
		return false;
	}

	// Attempt to connect
	bool bConnected = ConnectionSocket->Connect(*Addr);
	if (!bConnected)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to connect to server."));
		// Ensure to clean up the socket if the connection is unsuccessful
		ConnectionSocket->Close();
		SocketSubsystem->DestroySocket(ConnectionSocket);
		return false;
	}

	// Connection successful
	UE_LOG(LogTemp, Log, TEXT("Successfully connected to server."));
	return true;
}

void AcubukdenemeGameModeBase::LogCharacterInfo()
{
	UWorld* World = GetWorld();
	if (!World) return;

	for (TActorIterator<AMyCharacter> It(World, AMyCharacter::StaticClass()); It; ++It)
	{
		AMyCharacter* Character = *It;
		if (Character)
		{
			// Example: log character's position and health
			FString CharacterInfo = FString::Printf(TEXT("Character Name: %s, ID: %d, Team: %d"),
				*Character->GetName(), Character->GetID(), Character->GetTeam());

			// Display on screen
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, CharacterInfo);
			}

			// Alternatively, log to console
			UE_LOG(LogTemp, Log, TEXT("%s"), *CharacterInfo);
		}
	}
}

void AcubukdenemeGameModeBase::BeginDestroy()
{
	//// Ensure we call the base class's BeginDestroy
	Super::BeginDestroy();

	// Check if we have a valid socket
	if (ConnectionSocket != nullptr)
	{
		// Close the socket
		ConnectionSocket->Close();

		// Delete the socket to free its resources
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ConnectionSocket);
		ConnectionSocket = nullptr; // Ensure the pointer is null after deletion

		UE_LOG(LogTemp, Log, TEXT("Socket connection closed."));
	}
}

void AcubukdenemeGameModeBase::MoveCharactersToTheirBases()
{
	for (int i = 0; i < 2; ++i)
	{
		this->Team1Characters[i]->SetTargetLocation(this->ChunckLocations[this->Team1Characters[i]->GetTeam() == 0 ? "b1" : "b2"]);
		this->Team2Characters[i]->SetTargetLocation(this->ChunckLocations[this->Team2Characters[i]->GetTeam() == 0 ? "b1" : "b2"]);
	}
}

void AcubukdenemeGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//this->ReadTextFile();

	if (ConnectionSocket != nullptr && ConnectionSocket->GetConnectionState() == ESocketConnectionState::SCS_Connected)
	{
		uint32 PendingDataSize = 0;
		if (ConnectionSocket->HasPendingData(PendingDataSize))
		{
			TArray<uint8> ReceivedData;
			ReceivedData.SetNumUninitialized(PendingDataSize);

			int32 BytesRead = 0;
			if (ConnectionSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), BytesRead))
			{
				// Assuming the data is ASCII text. For other data types, you'll need appropriate parsing.
				FString ReceivedText = FString(ANSI_TO_TCHAR(reinterpret_cast<const char*>(ReceivedData.GetData())));

				// Optionally trim the FString to the actual number of bytes read
				ReceivedText = ReceivedText.Left(BytesRead);

				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Black, ReceivedText);
					GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Black, "DENEME BAGLANTI");
				}

				ParsePlayerJson(ReceivedText);
			}
		}
	}
	else
	{
		// Optionally handle disconnection or inability to receive data
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Failed to connect to server (TICK)"));
	}
}


bool AcubukdenemeGameModeBase::ParsePlayerJson(FString JsonString)
{
	// Create a JSON Reader from the JSON string
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	bool isSuccess = FJsonSerializer::Deserialize(Reader, JsonObject);

	if (isSuccess)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("VALID DESERIALIZE")));
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("NOT VALID DESERIALIZE")));
		}
	}

	if (JsonObject.IsValid())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("VALID")));
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("NOT VALID")));
		}
	}

	// Deserialize the JSON data into a JsonObject
	if (isSuccess && JsonObject.IsValid())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("JSON parsed successfully")));
		}
		FString RequestType;
		if (!JsonObject->TryGetStringField(TEXT("type"), RequestType))
		{
			UE_LOG(LogTemp, Warning, TEXT("type field not found or not a string"));
			return false;
		}

		if (RequestType == "game_start")
		{
			if (this->team1CharacterCount + this->team2CharacterCount == 4)
			{
				this->MoveCharactersToTheirBases();
			}
			// write else here
			return true;
		}
		else if (RequestType == "game_end")
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Game End")));
			}

			return true;
		}
		else if (RequestType == "set_player_location")
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Set Player Location")));
			}

			int32 ID;
			if (!JsonObject->TryGetNumberField(TEXT("id"), ID))
			{
				UE_LOG(LogTemp, Warning, TEXT("ID field not found or not a number"));
				return false;
			}

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("VALID MI ID: %d"), ID));
			}

			FString Chunck;
			if (!JsonObject->TryGetStringField(TEXT("chunk"), Chunck))
			{
				UE_LOG(LogTemp, Warning, TEXT("Chunck field not found or not a string"));
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Chunk alinamadi")));
				}
				return false;
			}

			/*if (this->Characters.IsValidIndex(ID))
			{*/
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Chunk -> VALID ID: %d, Chunck: %s"), ID, *Chunck));
				}
				
				for (int i = 0; i < 2; ++i)
				{
					if (this->Team1Characters[i]->GetID() == ID)
					{
						this->Team1Characters[i]->SetTargetLocation(this->ChunckLocations[*Chunck]);
						break;
					}
					else if (this->Team2Characters[i]->GetID() == ID)
					{
						this->Team2Characters[i]->SetTargetLocation(this->ChunckLocations[*Chunck]);
						break;
					}
				}
			//}
		}
		else if (RequestType == "create")
		{
			// Extract the string field "name"
			FString Name;
			if (!JsonObject->TryGetStringField(TEXT("name"), Name))
			{
				UE_LOG(LogTemp, Warning, TEXT("Name field not found or not a string"));
				return false;
			}

			// Extract the number fields "team" and "id"
			int32 Team, ID;
			if (!JsonObject->TryGetNumberField(TEXT("team"), Team))
			{
				UE_LOG(LogTemp, Warning, TEXT("Team field not found or not a number"));
				return false;
			}

			if (!JsonObject->TryGetNumberField(TEXT("id"), ID))
			{
				UE_LOG(LogTemp, Warning, TEXT("ID field not found or not a number"));
				return false;
			}

			// Log extracted values
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Player Name: %s"), *Name));
			}
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Team: %d"), Team));
			}
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("ID: %d"), ID));
			}

			if (this->team1CharacterCount + this->team2CharacterCount < 4)
			{
				if (Team == 0)
				{
					this->Team1Characters[this->team1CharacterCount]->SetID(ID);
					this->Team1Characters[this->team1CharacterCount]->SetTeam(Team);
					this->Team1Characters[this->team1CharacterCount]->SetName(Name);
					++this->team1CharacterCount;
				}
				else if (Team == 1)
				{
					this->Team2Characters[this->team2CharacterCount]->SetID(ID);
					this->Team2Characters[this->team2CharacterCount]->SetTeam(Team);
					this->Team2Characters[this->team2CharacterCount]->SetName(Name);
					++this->team2CharacterCount;
				}
			}
			else
			{
				this->LogCharacterInfo();
			}
		}
		else {
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Invalid Request Type")));
			}
		}

		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("Failed to parse JSON."));
	return false;
}
