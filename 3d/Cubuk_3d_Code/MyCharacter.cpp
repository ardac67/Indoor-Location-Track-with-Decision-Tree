// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Configure the character to snap to the ground
	/*GetCharacterMovement()->GroundFriction = 8.0f;
	GetCharacterMovement()->BrakingFrictionFactor = 2.0f;*/

	// Adjust properties for ground adherence
	//GetCharacterMovement()->MaxStepHeight = 45.0f; // Adjust step height for better navigation over uneven terrain
	//GetCharacterMovement()->SetWalkableFloorAngle(45.0f);

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	/*if (ConnectToServer(TEXT("192.168.100.95"), 8080) && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, TEXT("Connected to server"));
		ConnectionSocket->SetNonBlocking(true);
	}
	else if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Failed to connect to server"));
	}*/
}

void AMyCharacter::BeginDestroy()
{
	// Ensure we call the base class's BeginDestroy
	Super::BeginDestroy();

	//// Check if we have a valid socket
	//if (ConnectionSocket != nullptr)
	//{
	//	// Close the socket
	//	ConnectionSocket->Close();

	//	// Delete the socket to free its resources
	//	ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ConnectionSocket);
	//	ConnectionSocket = nullptr; // Ensure the pointer is null after deletion

	//	UE_LOG(LogTemp, Log, TEXT("Socket connection closed."));
	//}
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldMove)
	{
		MoveTowardsTarget();
	}
	/*
	if (ConnectionSocket && ConnectionSocket->GetConnectionState() == ESocketConnectionState::SCS_Connected)
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

				// Do something with the received text, for example, display it on screen
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, ReceivedText);
				}

				// Parse the received text
				if (ReceivedText.Equals(TEXT("w"), ESearchCase::IgnoreCase))
				{
					// Area forward
					SetTargetLocation(FVector(17915.0f, 20000.0f, 1200.0f));
				}
				else if (ReceivedText.Equals(TEXT("s"), ESearchCase::IgnoreCase))
				{
					SetTargetLocation(FVector(17915.0f, 8070.0f, 1200.0f));

				}
				else if (ReceivedText.Equals(TEXT("a"), ESearchCase::IgnoreCase))
				{
					SetTargetLocation(FVector(-950.0f, 8070.0f, 1200.0f));

				}
				else if (ReceivedText.Equals(TEXT("a"), ESearchCase::IgnoreCase))
				{
					SetTargetLocation(FVector(-950.0f, 20000.0f, 1200.0f));

				}
			}
		}
	}
	else
	{
		// Optionally handle disconnection or inability to receive data
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Failed to connect to server (TICK)"));
	}

	if (bShouldMove)
	{
		MoveTowardsTarget();
	}*/
}

void AMyCharacter::SetTargetLocation(const FVector& NewTargetLocation)
{
	TargetLocation = NewTargetLocation;
	bShouldMove = true;
}

void AMyCharacter::MoveTowardsTarget()
{
	FVector Direction = (TargetLocation - GetActorLocation()).GetSafeNormal();
	float Distance = FVector::Dist(GetActorLocation(), TargetLocation);

	// Check if character is "close enough" to the target location
	if (Distance > 10.0f) // Threshold to consider the character has arrived
	{
		AddMovementInput(Direction, 1.0f);
	}
	else
	{
		bShouldMove = false; // Stop moving once the target is reached
	}
}

//bool AMyCharacter::ConnectToServer(const FString& ServerIP, int32 ServerPort)
//{
//	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
//	if (!SocketSubsystem)
//	{
//		UE_LOG(LogTemp, Error, TEXT("Failed to get socket subsystem."));
//		return false;
//	}
//
//	// Create socket
//	FIPv4Address IP;
//	FIPv4Address::Parse(ServerIP, IP);
//	TSharedRef<FInternetAddr> Addr = SocketSubsystem->CreateInternetAddr();
//	Addr->SetIp(IP.Value);
//	Addr->SetPort(ServerPort);
//
//	ConnectionSocket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("TCPClient"), false);
//	if (!ConnectionSocket)
//	{
//		UE_LOG(LogTemp, Error, TEXT("Failed to create socket."));
//		return false;
//	}
//
//	// Attempt to connect
//	bool bConnected = ConnectionSocket->Connect(*Addr);
//	if (!bConnected)
//	{
//		UE_LOG(LogTemp, Error, TEXT("Failed to connect to server."));
//		// Ensure to clean up the socket if the connection is unsuccessful
//		ConnectionSocket->Close();
//		SocketSubsystem->DestroySocket(ConnectionSocket);
//		return false;
//	}
//
//	// Connection successful
//	UE_LOG(LogTemp, Log, TEXT("Successfully connected to server."));
//	return true;
//}


//bool AMyCharacter::ConnectToServer()
//{
	//// Create Socket
	//FIPv4Address Addr;
	//FIPv4Address::Parse(TheIP, Addr);

	//TSharedRef<FInternetAddr> InternetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	//InternetAddr->SetIp(Addr.GetValue());
	//InternetAddr->SetPort(ThePort);

	//FSocket* ClientSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("Default"), false);

	//// Check if the Socket is valid
	//if (!ClientSocket)
	//{
	//	// Could not create the socket, handle errors here
	//	return false;
	//}

	//// Connect to the server
	//bool bConnected = ClientSocket->Connect(*InternetAddr);
	//if (bConnected)
	//{
	//	// Successfully connected
	//	// Now you can use the ClientSocket to send and receive data.
	//}
	//else
	//{
	//	// Failed to connect, handle errors here
	//	// Ensure to clean up the socket
	//	ClientSocket->Close();
	//	ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ClientSocket);
	//	return false;
	//}

	//return true;

	//FIPv4Address IP;
//	FIPv4Address::Parse(TEXT("192.168.100.95"), IP);
//
//	TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
//	Addr->SetIp(IP.Value);
//	Addr->SetPort(8080);
//
//	FSocket* Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_DGram, TEXT("UDPExample"), false);
//	bool bIsBound = Socket->Bind(*Addr);
//	return bIsBound;
//}