// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

//Forward declaration
class USceneComponent;
class USkeletalMeshComponent;
class UNiagaraSystem;

UCLASS()
class CITADEL_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTriger();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	// creating the root wich is a pointe for UsceneComponent
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* Root;

	//Creating the mesh
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere, Category = "Fire System")
	UNiagaraSystem* MuzzleFlashSystem;

	UPROPERTY(EditAnywhere, Category = "Fire System")
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere, Category = "Fire System")
	UNiagaraSystem* BullethitSystem;

	UPROPERTY(EditAnywhere, Category = "Fire System")
	USoundBase* BulletHitSound;

	UPROPERTY(EditAnywhere, Category = "Fire System")
	float MaxRange = 1000;

	UPROPERTY(EditAnywhere, Category = "Fire System")
	float Damage = 10;



};
