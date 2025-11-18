// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "DrawDebugHelpers.h"
#include "control.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creat the roo and setting in as the rootcomponent.
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	//creating the mesh and attacch it under the Root component
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	GunMesh->SetupAttachment(Root);

}

void AGun::PullTriger()
{
    // Spawn the Niagara System at the muzzle socket
    if (MuzzleFlashSystem) // Ensure the Niagara System is assigned
    {
        UNiagaraFunctionLibrary::SpawnSystemAttached(
            MuzzleFlashSystem,      // Niagara System asset
            GunMesh,                // Attach to the GunMesh
            TEXT("MuzzleSocket"),   // Socket name
            FVector::ZeroVector,    // Location offset (relative to socket)
            FRotator::ZeroRotator,  // Rotation offset
            EAttachLocation::SnapToTarget, // Attach type
            true                    // Auto-destroy when done
        );
    }

    // Play the fire sound
    if (MuzzleSound) // Ensure the sound is assigned
    {
        UGameplayStatics::SpawnSoundAttached(
            MuzzleSound,           // Sound asset
            GunMesh,                // Attach to the GunMesh
            TEXT("MuzzleSocket"),   // Socket name
            FVector::ZeroVector,    // Location offset (relative to socket)
            EAttachLocation::SnapToTarget, // Attach type
            true,                   // Auto-destroy when done
            1.0f,                   // Volume multiplier
            1.0f,                   // Pitch multiplier
            0.0f                    // Start time
        );
    }


    
    // casting the pawn class and get the owner of the gun.  check for null ptr
    APawn* OwnerPawn = Cast<APawn>(GetOwner());
    if (OwnerPawn == nullptr) return;
    
    AController* OwnerController = OwnerPawn->GetController();
    if (OwnerController == nullptr) return;

    // creating vector and rotator for using them as arguments for the get player view point
    FVector Location;
    FRotator Rotation;
    OwnerController->GetPlayerViewPoint(Location, Rotation);

    //creating the line trace from the bullet chanel that made in project settings
    FVector End = Location + Rotation.Vector() * MaxRange;
    
    //make the line trace
    FHitResult HitResults; // Array to store all hits

    // make dollision paramaters for not hitting him-our self 
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
    Params.AddIgnoredActor(GetOwner());

    bool bSucceeded = GetWorld()->LineTraceSingleByChannel(HitResults, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
    
    
   // DrawDebugPoint(GetWorld(), HitResults.Location, 50, FColor::Red, true);
    //DrawDebugLine(GetWorld(), HitResults.Location, End, FColor::Red, true, 1.0f, 0, 1.0f);
    if (bSucceeded)
    {
        
        //DrawDebugPoint(GetWorld(), HitResults.Location, 50, FColor::Red, true);
        //spawnning effect at a location
        //DrawDebugLine(GetWorld(), HitResults.Location, End, FColor::Red, true, 1.0f, 0, 1.0f);
            if (HitResults.GetActor())
            {
                FVector ShotDirection = -Rotation.Vector();
                UNiagaraFunctionLibrary::SpawnSystemAtLocation(
                    GetWorld(),
                    BullethitSystem,
                    HitResults.Location,
                    FRotator::ZeroRotator,
                    FVector(1.0f));

                // using the standar unreals damage event
               FPointDamageEvent DamageEvent(Damage, HitResults, ShotDirection, nullptr);
               HitResults.GetActor()->TakeDamage(Damage, DamageEvent, OwnerController, this);
                UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *HitResults.GetActor()->GetName());
                //DrawDebugPoint(GetWorld(), Hit.Location, 50, FColor::Red, true);
            
             // Play sound at hit location
                if (BulletHitSound) // Ensure BulletHitSound is assigned
                {
                    UGameplayStatics::PlaySoundAtLocation(
                        GetWorld(),
                        BulletHitSound,
                        HitResults.Location,   // Play sound at hit location
                        FRotator::ZeroRotator  // Default rotation
                    );
                }
            }

           
        
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No hits detected."));
    }
    // drawing a debug camera to see where the camera is aiming
    //DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Green, true);
    //draw debug point
    //DrawDebugPoint(GetWorld(), Location, 50, FColor::Red, true);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
