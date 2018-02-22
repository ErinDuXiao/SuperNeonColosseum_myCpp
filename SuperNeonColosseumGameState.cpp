
#include "SuperNeonColosseumGameState.h"

class ASuperNeonColosseumGameState;

TArray<APlayerState*> ASuperNeonColosseumGameState::GetPlayerRanking() {
	
	// DeepCopy PlayerArray to RankedPlayers 
	RankedPlayers = TArray<APlayerState*>(PlayerArray);

	// Sort RankedPlayers by PlayerScore
	RankedPlayers.Sort(ASuperNeonColosseumGameState::ConstPredicate);

	return RankedPlayers;

}
