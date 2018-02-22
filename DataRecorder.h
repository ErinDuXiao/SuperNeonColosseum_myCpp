#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SuperNeonColosseumPlayerState.h"
#include "Classes/Kismet/KismetMathLibrary.h"
#include "DataRecordStructs.h"
#include "JsonObject.h"
#include "JsonObjectConverter.h"
#include "JsonPrintPolicy.h"
#include "JsonWriter.h"
#include "JsonSerializer.h"
#include "DataRecorder.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPERNEONCOLOSSEUM_API UDataRecorder : public USceneComponent
{
	GENERATED_BODY()

public:
	/** UDataRecorder Constructor */
	UDataRecorder();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Recorder")
		bool Enable;

	/** 
	* Start to record data - initialise record
	* @param sessionKey - 
	* @param timestamp - 
	*/
	UFUNCTION(BlueprintCallable)
		void StartRecording(const FString serverName, const FString timestamp, TArray<APlayerState*> playerArray);
	
	/**
	* Finish recording data - make json in file
	*/
	UFUNCTION(BlueprintCallable)
		void FinishRecording();

protected:

	virtual void BeginPlay() override;

private:
	FJsonStruct* JsonData;

	FString DataRecordingServerURL;

	TArray<APlayerController*> RecordTargetPlayers;

	float DeltaTimeFromLastRecord;

	/**
	* Common function to record player event information as FEventInfoStruct.
	* @param player - Player controller reference.
	* @param eventPos - World location of the player when the event happened.
	*/
	FEventInfoStruct RecordEvent(const APlayerController* player, const FVector& eventPos);

	/**
	* Create Json file under ../Saved/DA/${sessionKey}.json
	*/
	UFUNCTION(BlueprintCallable)
		void MakeJson();

	/**
	* Create Json file under ../Saved/DA/${sessionKey}.json
	*/
	UFUNCTION(BlueprintCallable)
		void SaveFile(FString json);

	/**
	* Create Json file under ../Saved/DA/${sessionKey}.json
	*/
	UFUNCTION(BlueprintCallable)
		void SendJson(FString json);

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	* Interface for recording primary fire event.
	* @param player - player controller reference.
	* @param eventPos - World location of the player when the event happened.
	*/
	UFUNCTION(BlueprintCallable)
		void RecordPrimary(const APlayerController* player, const FVector& eventPos);

	/**
	* Interface for recording secondary fire event.
	* @param player - player controller reference.
	* @param eventPos - World location of the player when the event happened.
	*/
	UFUNCTION(BlueprintCallable)
		void RecordSecondary(const APlayerController* player, const FVector& eventPos);

	/**
	* Interface for recording boost event.
	* @param player - player controller reference.
	* @param eventPos - World location of the player when the event happened.
	*/
	UFUNCTION(BlueprintCallable)
		void RecordBoost(const APlayerController* player, const FVector& eventPos);

	/**
	* Interface for recording death event.
	* @param player - player controller reference.
	* @param eventPos - World location of the player when the event happened.
	*/
	UFUNCTION(BlueprintCallable)
		void RecordDeath(const APlayerController* player, const FVector& eventPos);

	/**
	* Interface for recording player location.
	* @param player - player controller reference.
	* @param eventPos - World location of the player when the event happened.
	*/
	UFUNCTION(BlueprintCallable)
		void RecordPlayerLocation();

	/**
	* Interface to get timestamp string.
	* @param player - player controller reference.
	* @param eventPos - World location of the player when the event happened.
	*/
	UFUNCTION(BlueprintCallable)
		FString GetCurrentTimestampString();
};
