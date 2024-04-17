// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Rocket.h"


// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);


	//FStramableManager.AsyncLoad // InPlay
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Body.SM_P38_Body'"));
	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}

	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);

	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Propeller.SM_P38_Propeller'"));
	if (SM_Propeller.Succeeded())
	{
		Left->SetStaticMesh(SM_Propeller.Object);
		Right->SetStaticMesh(SM_Propeller.Object);
	}

	Left->SetRelativeLocation(FVector(37.f, -21.f, 0.9f));
	Right->SetRelativeLocation(FVector(37.f, 21.f, 0.9f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Box);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	Movement->MaxSpeed = 0;

	//Bluprint Class File
	static ConstructorHelpers::FClassFinder<AActor> BP_Bomb(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_Bomb.BP_Bomb_C'"));
	if (BP_Bomb.Succeeded())
	{
		RocketTemplate = BP_Bomb.Class; //Class Name 등록
	}
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Left->AddLocalRotation(FRotator(0, 0, 3600 * DeltaTime));
	//Right->AddLocalRotation(FRotator(0, 0, 3600 * DeltaTime));
	this->PropellerRotate(Left);
	this->PropellerRotate(Right);

	AddMovementInput(GetActorForwardVector());
}

void AMyPawn::PropellerRotate(UStaticMeshComponent* where)
{
	where->AddLocalRotation(FRotator(0,
		0,
		3600 * UGameplayStatics::GetWorldDeltaSeconds(GetWorld())
	));
}



// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AMyPawn::Pitch);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMyPawn::Roll);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AMyPawn::Fire);
	//PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &AMyPawn::Fire);
}

void AMyPawn::Pitch(float Value)
{
	AddActorLocalRotation(FRotator(
		60 * Value * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
		0,
		0
	));
}

void AMyPawn::Roll(float Value)
{
	AddActorLocalRotation(FRotator(0,
		0,
		60 * Value * UGameplayStatics::GetWorldDeltaSeconds(GetWorld())
	));
}

void AMyPawn::Fire()
{
	//Art 이펙트 발사
	SpawnEffect(); //Blueprint

	GetWorld()->SpawnActor<AActor>(RocketTemplate,
		GetActorTransform());
}

void AMyPawn::SpawnEffect_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("이건 C++에서 구현 한 로직"));
}

