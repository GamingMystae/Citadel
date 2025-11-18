// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputActionValue.h"// need it for
#include "InputAction.h"  // Ensure the correct include for UInputAction
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Raven.generated.h"

class UInputMappingContext;
class UInputActions;
class AGun;
class UStaticMeshComponent;

UCLASS()
class CITADEL_API ARaven : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARaven();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//called when we need to apply damage using the virtual function
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	// Function to handle shooting
	void Shoot();

	void SheildActivation();
	
	UFUNCTION(BlueprintPure)
	bool IsDead() const;
	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintPure)
	float GetSheildPercent() const;

	// Gun class to spawn
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<AGun> GunClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	float MaxShieldEnergy = 80.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	float ShieldEnergy;
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	

	bool bIsShieldActivate = false;

	// Shield visual representation
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	UStaticMeshComponent* ShieldMesh;

	

	// Gun instance
	UPROPERTY()
	AGun* Gun;

	// Input mapping context for enhanced input
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* Raven;

	// Input action for shooting
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InputActionShoot;

	// Input action for shooting
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InputActionShield;


	

};
