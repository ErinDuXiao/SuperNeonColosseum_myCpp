
#include "DataRecorder.h"

#pragma region Constructer
// Sets default values for this component's properties
UDataRecorder::UDataRecorder()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 1.0f;
	bAllowConcurrentTick = true;

}
#pragma endregion 

#pragma region BeginPlay
// Called when the game starts
void UDataRecorder::BeginPlay()
{
	if (!Enable) return;

	Super::BeginPlay();
}
#pragma endregion 

#pragma region Starting and Finishing
void UDataRecorder::StartRecording(const FString serverName, const FString timestamp, TArray<APlayerState*> playerArray)
{
	if (!Enable) return;

	DataRecordingServerURL = "http://sncdataanalysis.appspot.com/admin";

	// Put initial information to the Json Data
	JsonData = new FJsonStruct;
	JsonData->cmd = "save_playdata";
	JsonData->data.filetype = "SNCGameplayData";
	JsonData->data.sessionKey = serverName + "-" + timestamp;
	JsonData->data.timestamp = timestamp;
	JsonData->data.playerInfoArray = TArray<FPlayerStruct>();
	JsonData->data.primaryFireInfoArray = TArray<FEventInfoStruct>();
	JsonData->data.secondaryFireInfoArray = TArray<FEventInfoStruct>();
	JsonData->data.playerDeathInfoArray = TArray<FEventInfoStruct>();
	JsonData->data.playerPosInfoArray = TArray<FEventInfoStruct>();
	JsonData->data.playerBoostInfoArray = TArray<FEventInfoStruct>();

	FPlayerStruct* playerInfo;
	ASuperNeonColosseumPlayerState* playerState;
	for (int i = 0; i < playerArray.Num(); i++) {

		playerState = (ASuperNeonColosseumPlayerState*)playerArray[i];

		// Store player info
		playerInfo = new FPlayerStruct;
		playerInfo->playerNumber = playerState->PlayerSlot;
		playerInfo->hovercraftNumber = playerState->SelectedHovercraftNum;
		JsonData->data.playerInfoArray.Add(*playerInfo);
		
		// Keep player controller to get location information later
		RecordTargetPlayers.Add((APlayerController*)playerArray[i]->GetOwner());
	}

}

void UDataRecorder::FinishRecording()
{
	if (!Enable || !JsonData) return;

	MakeJson();
}
#pragma endregion

#pragma region Tick
void UDataRecorder::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (!Enable) return;

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RecordPlayerLocation();
}
#pragma endregion

#pragma region Event Recording API
void UDataRecorder::RecordPrimary(const APlayerController* player, const FVector& eventPos)
{
	if (!Enable || !JsonData) return;
	JsonData->data.primaryFireInfoArray.Add(UDataRecorder::RecordEvent(player, eventPos));
}

void UDataRecorder::RecordSecondary(const APlayerController* player, const FVector& eventPos)
{
	if (!Enable || !JsonData) return;
	JsonData->data.secondaryFireInfoArray.Add(UDataRecorder::RecordEvent(player, eventPos));
}

void UDataRecorder::RecordBoost(const APlayerController* player, const FVector& eventPos)
{
	if (!Enable || !JsonData) return;
	JsonData->data.playerBoostInfoArray.Add(UDataRecorder::RecordEvent(player, eventPos));
}

void UDataRecorder::RecordDeath(const APlayerController* player, const FVector& eventPos)
{
	if (!Enable || !JsonData) return;

	JsonData->data.playerDeathInfoArray.Add(UDataRecorder::RecordEvent(player, eventPos));
}
#pragma endregion

#pragma region Player Location Recording API
void UDataRecorder::RecordPlayerLocation()
{
	if (!Enable || !JsonData) return;

	APawn* hovercraft;
	for (int i = 0; i < RecordTargetPlayers.Num(); i++) {
		hovercraft = RecordTargetPlayers[i]->GetPawn();
		if (hovercraft) {
			JsonData->data.playerPosInfoArray.Add(UDataRecorder::RecordEvent(RecordTargetPlayers[i], hovercraft->GetActorLocation()));
		}
	}
}
#pragma endregion

#pragma region Event Recording Common Function
FEventInfoStruct UDataRecorder::RecordEvent(const APlayerController* player, const FVector& eventPos)
{
	FEventInfoStruct eventInfo;
	eventInfo.x = eventPos.X;
	eventInfo.y = eventPos.Y;
	eventInfo.z = eventPos.Z;
	eventInfo.timestamp = GetCurrentTimestampString();
	eventInfo.playerNumber = Cast<ASuperNeonColosseumPlayerState>(player->PlayerState)->PlayerSlot;
	return eventInfo;
}
#pragma endregion 

#pragma region Timestamp getting function
FString UDataRecorder::GetCurrentTimestampString()
{
	FDateTime timestampObj = UKismetMathLibrary::Now();
	FString timestamp = FString();
	timestamp.AppendInt(timestampObj.GetYear());
	timestamp.AppendInt(timestampObj.GetMonth());
	timestamp.AppendInt(timestampObj.GetDay());
	timestamp.AppendInt(timestampObj.GetHour());
	timestamp.AppendInt(timestampObj.GetMinute());
	timestamp.AppendInt(timestampObj.GetSecond());
	return timestamp;
}
#pragma endregion 

#pragma region MakeJson
void UDataRecorder::MakeJson()
{
	// Create a json object and convert the given stuct into a serializable object.
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject = FJsonObjectConverter::UStructToJsonObject<FJsonStruct>(*JsonData);

	// Create a string will get our formated data.
	FString OutputString;

	// Serialize the json object with our data into a Json structure.
	TSharedRef< TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>> > JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
	SaveFile(OutputString);
	SendJson(OutputString);
}
#pragma endregion
#pragma region SaveFile
void UDataRecorder::SaveFile(FString json)
{
	// Create a file with the given string in the project directory folder
	FFileHelper::SaveStringToFile(json, *(FPaths::GameDir() + "Saved/" + JsonData->data.sessionKey + ".json"));
}
#pragma endregion
#pragma region SendFile
void UDataRecorder::SendJson(FString json)
{

}
#pragma endregion