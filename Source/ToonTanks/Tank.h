// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
// #include "Camera/CameraComponent.h" // Forward Declaration
// #include "GameFramework/SpringArmComponent.h" // Forward Declaration
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

	bool bAlive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category="Component")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category="Component")
	class UCameraComponent* Camera;

	void Move(float Value);

	void Turn(float Value);

	UPROPERTY(EditAnywhere, Category="Movement", meta=(AllowPrivateAccess="true"))
	float Speed = 200.f;

	UPROPERTY(EditAnywhere, Category="Movement", meta=(AllowPrivateAccess="true"))
	float TurnRate = 45.f;

	APlayerController* TankPlayerController;
};
