

#pragma once

#include "CoreMinimal.h"
#include "SecureHash.h"
#include "DataRecordStructs.generated.h"

USTRUCT(BlueprintType)
struct FEventInfoStruct {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
		float x;

	UPROPERTY(BlueprintReadWrite)
		float y;

	UPROPERTY(BlueprintReadWrite)
		float z;

	UPROPERTY(BlueprintReadWrite)
		FString timestamp;

	UPROPERTY(BlueprintReadWrite)
		int playerNumber;
};

USTRUCT(BlueprintType)
struct FPlayerStruct {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
		int playerNumber;

	UPROPERTY(BlueprintReadWrite)
		int hovercraftNumber;
};

// Data structure that will be fetched several times.
USTRUCT(BlueprintType)
struct FDataStruct {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
		FString filetype;

	UPROPERTY(BlueprintReadWrite)
		FString sessionKey;

	UPROPERTY(BlueprintReadWrite)
		FString timestamp;

	UPROPERTY(BlueprintReadWrite)
		TArray<FPlayerStruct> playerInfoArray;

	UPROPERTY(BlueprintReadWrite)
		TArray<FEventInfoStruct> primaryFireInfoArray;

	UPROPERTY(BlueprintReadWrite)
		TArray<FEventInfoStruct> secondaryFireInfoArray;

	UPROPERTY(BlueprintReadWrite)
		TArray<FEventInfoStruct> playerDeathInfoArray;

	UPROPERTY(BlueprintReadWrite)
		TArray<FEventInfoStruct> playerBoostInfoArray;

	UPROPERTY(BlueprintReadWrite)
		TArray<FEventInfoStruct> playerPosInfoArray;
};

// Struct that will envelope the data package.
USTRUCT(BlueprintType)
struct FJsonStruct {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
		FString cmd;

	UPROPERTY(BlueprintReadWrite)
		FDataStruct data;
};


