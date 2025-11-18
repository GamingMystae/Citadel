// Fill out your copyright notice in the Description page of Project Settings.


#include "Raven.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Gun.h"
#include "CitadelGameModeBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ARaven::ARaven()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize the ShieldMesh component
	ShieldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMesh"));
	ShieldMesh->SetupAttachment(GetMesh()); // Attach it to the character mesh
	ShieldMesh->SetVisibility(false);       // Initially hidden
	ShieldMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // No collision for visual

}

// Called when the game starts or when spawned
void ARaven::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	ShieldEnergy = MaxShieldEnergy;
	IsDead();

	// Bind the input mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{
				if (Raven) // Ensure Raven mapping context is valid
				{
					Subsystem->AddMappingContext(Raven, 0);
				}
			}
		}
	}

	// Spawn the gun in the world
	if (GunClass)
	{
		Gun = GetWorld()->SpawnActor<AGun>(GunClass);
		if (Gun)
		{
			// Attach the gun to the WeaponSocket of the character's mesh
			Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));

			// Set the owner of the gun to this character
			Gun->SetOwner(this);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Gun could not be spawned."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GunClass is not set."));
	}
}

bool ARaven::IsDead() const
{
	return Health <= 0;

}

float ARaven::GetHealthPercent() const
{
	return Health / MaxHealth;
}

float ARaven::GetSheildPercent() const
{
	return ShieldEnergy / MaxShieldEnergy;
}

void ARaven::SheildActivation()
{
	// Toggle the shield activation state
	bIsShieldActivate = !bIsShieldActivate;

	if (bIsShieldActivate)
	{
		UE_LOG(LogTemp, Warning, TEXT("Shield Activated!"));
		ShieldMesh->SetVisibility(true); // Show the shield
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Shield Deactivated!"));
		ShieldMesh->SetVisibility(false); // Hide the shield
	}
}


// Shoot method implementation
void ARaven::Shoot()
{
	if (Gun)
	{
		Gun->PullTriger(); // Corrected method name
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Gun is not initialized."));
	}
}



// Called every frame
void ARaven::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Setting up player input component
void ARaven::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Bind the Shoot action
		if (InputActionShoot) // Ensure the input action is valid
		{
			EnhancedInputComponent->BindAction(InputActionShoot, ETriggerEvent::Triggered, this, &ARaven::Shoot);
			EnhancedInputComponent->BindAction(InputActionShield, ETriggerEvent::Started, this, &ARaven::SheildActivation);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Shoot input action is not set."));
		}
	}
}

float ARaven::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (DamageToApply > 0)
	{
		if (bIsShieldActivate && ShieldEnergy > 0)
		{
			// Apply damage to the shield first
			float ShieldDamage = FMath::Min(ShieldEnergy, DamageToApply);
			ShieldEnergy -= ShieldDamage;
			DamageToApply -= ShieldDamage;

			UE_LOG(LogTemp, Warning, TEXT("Shield absorbed %f damage. Remaining shield: %f"), ShieldDamage, ShieldEnergy);

			// If shield absorbs all damage, return
			if (DamageToApply <= 0)
			{
				return 0.0f;
			}
		}

		// Apply remaining damage to health
		float HealthDamage = FMath::Min(Health, DamageToApply);
		Health -= HealthDamage;

		UE_LOG(LogTemp, Warning, TEXT("Health took %f damage. Remaining health: %f"), HealthDamage, Health);

		// Check for death
		if (IsDead())
		{
			UE_LOG(LogTemp, Warning, TEXT("Player is dead!"));

			ACitadelGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ACitadelGameModeBase>();
			if (GameMode != nullptr)
			{
				GameMode->PawnKilled(this);
			}

			DetachFromControllerPendingDestroy();
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}

	return DamageToApply;
}