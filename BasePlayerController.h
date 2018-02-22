// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SUPERNEONCOLOSSEUM_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
private:

	FTimerHandle countDownTimerHandle;

	int currentCountDownNum = 5;

public:
	UFUNCTION(BlueprintCallable, Client, unreliable)
		void PlaySound(AActor* actor, const FString& eventName);

	UFUNCTION(BlueprintCallable, Client, unreliable)
		void ShowCharacterAttackedDirection(FVector cameraForward, FVector cameraLocation, FVector attackerLocation);

	UFUNCTION(BlueprintImplementableEvent)
		void ShowCompassHUD(int directionId);

	UFUNCTION(BlueprintCallable, Client, unreliable)
		void ShowHitEvent();

	UFUNCTION(BlueprintImplementableEvent)
		void ShowHitEventOnHud();

	// Be called when this character WAS ELIMINATED BY someone
	UFUNCTION(BlueprintCallable, Client, Reliable)
		void OnDeathEvent(int opponentPlayerSlot);

	// Be called when this character ELIMINATED someone
	UFUNCTION(BlueprintCallable, Client, Reliable)
		void OnKillEvent(int opponentPlayerSlot, int currentScore);

	UFUNCTION(BlueprintImplementableEvent)
		void ShowMsgOnScreen(bool isKilled, int opponentPlayerSlot);

	UFUNCTION(BlueprintCallable, Client, Reliable)
		void MatchStartCountDown();

	UFUNCTION(BlueprintCallable)
		void CountDown();

	UFUNCTION(BlueprintImplementableEvent)
		void ShowMatchStartCountDownOnScreen(int number);

	UFUNCTION(BlueprintImplementableEvent)
		void OnCountDownFinished();

	UFUNCTION(BlueprintImplementableEvent)
		void CallPlayKillVO(int score);

		void PlayVibrationScaledByDamage(float damage);
};

