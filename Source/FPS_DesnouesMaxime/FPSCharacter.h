// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSProjectile.h"
#include "Blueprint/UserWidget.h"
#include "FPSCharacter.generated.h"

UCLASS()
class FPS_DESNOUESMAXIME_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Input functions
	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	// Function to handle firing projectiles
	void Fire();

	// Input rates
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float TurnRateGamepad;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float LookUpRateGamepad;

protected:
	// Projectile class to spawn
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPSProjectile> ProjectileClass;

	// Gun muzzle's offset from the camera location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	// Number of projectiles available
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 AmmoCount;

	// Widget class for the ammo display
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UUserWidget> AmmoWidgetClass;

	// Instance of the widget
	UPROPERTY()
	UUserWidget* AmmoWidget;

	// Function to update the ammo display
	void UpdateAmmoUI();

};
