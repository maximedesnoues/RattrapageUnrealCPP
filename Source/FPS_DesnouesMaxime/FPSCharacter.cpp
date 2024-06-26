// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "FPSProjectile.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "Components/InputComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize turn and look up rates
	TurnRateGamepad = 45.f;
	LookUpRateGamepad = 45.f;

    // Initialize the muzzle offset
    MuzzleOffset = FVector(100.0f, 0.0f, 0.0f);

    // Initial ammo count
    AmmoCount = 10;

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

    if (AmmoWidgetClass)
    {
        AmmoWidget = CreateWidget<UUserWidget>(GetWorld(), AmmoWidgetClass);
        if (AmmoWidget)
        {
            AmmoWidget->AddToViewport();
            // Initial update
            UpdateAmmoUI();
        }
    }
	
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind movement functions
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// Bind camera rotation functions
	PlayerInputComponent->BindAxis("TurnRate", this, &AFPSCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFPSCharacter::LookUpAtRate);

    // Bind fire function
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);

}

void AFPSCharacter::MoveForward(float Value)
{
    if (Controller && Value != 0.0f)
    {
        // Find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // Get forward vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void AFPSCharacter::MoveRight(float Value)
{
    if (Controller && Value != 0.0f)
    {
        // Find out which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // Get right vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void AFPSCharacter::TurnAtRate(float Rate)
{
    // Calculate delta for this frame from the rate information
    AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AFPSCharacter::LookUpAtRate(float Rate)
{
    // Calculate delta for this frame from the rate information
    AddControllerPitchInput(Rate * LookUpRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AFPSCharacter::Fire()
{
    // Attempt to fire a projectile.
    if (ProjectileClass && AmmoCount > 0)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            // Get the camera transform.
            FVector Location = GetActorLocation() + MuzzleOffset;
            FRotator Rotation = GetControlRotation();

            // Transform MuzzleOffset from camera space to world space.
            FVector MuzzleLocation = Location + FTransform(Rotation).TransformVector(MuzzleOffset);
            FRotator MuzzleRotation = Rotation;
            MuzzleRotation.Pitch += 10.0f;

            // Spawn the projectile at the muzzle.
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();

            // Spawn the projectile.
            AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
            if (Projectile)
            {
                // Set the projectile's initial trajectory.
                FVector LaunchDirection = MuzzleRotation.Vector();
                Projectile->FireInDirection(LaunchDirection);

                // Decrement ammo count and Update the UI.
                AmmoCount--;
                UpdateAmmoUI();
            }
        }
    }
}

void AFPSCharacter::UpdateAmmoUI()
{
    if (AmmoWidget)
    {
        UTextBlock* AmmoText = Cast<UTextBlock>(AmmoWidget->GetWidgetFromName("AmmoText"));
        if (AmmoText)
        {
            AmmoText->SetText(FText::FromString(FString::Printf(TEXT("Ammo: %d"), AmmoCount)));
        }
    }
}

