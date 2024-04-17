// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
//add
//추가
#include "MyPawn.h"
#include "MyPlayerController.h"

AMyGameModeBase::AMyGameModeBase()
{
	//FString, FText, FName
	UE_LOG(LogTemp, Warning, TEXT("안녕하세요."));

	PlayerControllerClass = AMyPlayerController::StaticClass(); //Mean : Class Name, CDO 포인터
	DefaultPawnClass = AMyPawn::StaticClass();
}
