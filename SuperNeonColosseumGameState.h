
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SuperNeonColosseumPlayerState.h"
#include "SuperNeonColosseumGameState.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SUPERNEONCOLOSSEUM_API ASuperNeonColosseumGameState : public AGameState
{
	GENERATED_BODY()

	TArray<APlayerState*> RankedPlayers;
	
public:

	UFUNCTION(BlueprintCallable)
	TArray<APlayerState*> GetPlayerRanking();
	
	FORCEINLINE static bool ConstPredicate(APlayerState& o1, APlayerState& o2) {
		return dynamic_cast<ASuperNeonColosseumPlayerState*>(&o1)->PlayerScore
			> dynamic_cast<ASuperNeonColosseumPlayerState*>(&o2)->PlayerScore;
	}
};
