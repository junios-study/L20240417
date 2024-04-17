// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UFloatingPawnMovement;

UCLASS()
class LECTURE3_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PropellerRotate(UStaticMeshComponent* where);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//UBoxComponent* Box

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MyComponents")
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MyComponents")
	TObjectPtr<UStaticMeshComponent> Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MyComponents")
	TObjectPtr<UStaticMeshComponent> Left;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MyComponents")
	TObjectPtr<UStaticMeshComponent> Right;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MyComponents")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MyComponents")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MyComponents")
	TObjectPtr<UFloatingPawnMovement> Movement;

	void Pitch(float Value);

	void Roll(float Value);

	void Fire();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TSubclassOf<class ARocket> RocketTemplate;

	//UFUNCTION(BlueprintImplementableEvent)
	//void SpawnEffect(); //BP �Լ� ȣ��

	UFUNCTION(BlueprintNativeEvent) //�⺻�� c++����, �߰��� BP���� 
	void SpawnEffect(); //C++,  BP �Լ� ȣ�� �ϴ� �ڵ�
	void SpawnEffect_Implementation(); //C++���� ����Ǵ� �⺻ �ڵ�

};
