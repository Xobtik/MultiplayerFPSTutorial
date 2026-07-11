// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void Initate_SwapWeapon();
	void Initate_FireWeapon_Pressed();
	void Initate_FireWeapon_Released();
	void Initate_ReloadWeapon();
	void Initate_Aim_Pressed();
	void Initate_Aim_Released();

	UPROPERTY(EditDefaultsOnly, Category = "FPS|Weapon")
	TObjectPtr<class UWeaponData> WeaponData;

	void SpawnInventory();


protected:

private:	

	UPROPERTY(Transient, Replicated)
	TArray<class ABaseWeapon*> Inventory;

	UPROPERTY(EditDefaultsOnly, Category = "FPS|Weapon")
	TArray<TSubclassOf<ABaseWeapon>> DefaultWeaponClasses;

	ABaseWeapon* SpawnWeapon(TSubclassOf<ABaseWeapon> WeaponClass) const;

		
};
