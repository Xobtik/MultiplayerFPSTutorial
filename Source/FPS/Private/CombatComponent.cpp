// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"
#include "GameFramework/Pawn.h"
#include "BaseWeapon.h"
#include "Net/UnrealNetwork.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCombatComponent, Inventory);
	DOREPLIFETIME(UCombatComponent, CurrentWeapon);
}

void UCombatComponent::Initate_SwapWeapon()
{
}

void UCombatComponent::Initate_FireWeapon_Pressed()
{
}

void UCombatComponent::Initate_FireWeapon_Released()
{
}

void UCombatComponent::Initate_ReloadWeapon()
{
}

void UCombatComponent::Initate_Aim_Pressed()
{
}

void UCombatComponent::Initate_Aim_Released()
{
}

void UCombatComponent::Equip(ABaseWeapon* Weapon)
{
	CurrentWeapon = Weapon;
	CurrentWeapon->AttachToOwningPawn();
}

void UCombatComponent::SpawnInventory()
{
	if(GetOwner()->GetLocalRole() < ROLE_Authority)
	{
		return;
	}

	for(TSubclassOf<ABaseWeapon>& WeaponClass : DefaultWeaponClasses)
	{
		ABaseWeapon* SpawnedWeapon = SpawnWeapon(WeaponClass);
		Inventory.AddUnique(SpawnedWeapon);
	}

	if(Inventory.Num() > 0)
	{
		Equip(Inventory[0]);
	}

}

void UCombatComponent::DestroyInventory()
{
	for(ABaseWeapon* Weapon : Inventory)
	{
		if(IsValid(Weapon))
		{
			Weapon->Destroy();
		}
	}
}

void UCombatComponent::OnRep_CurrentWeapon(ABaseWeapon* LastWeapon)
{
	if (!IsValid(CurrentWeapon))
	{
		return;
	}

	CurrentWeapon->AttachToOwningPawn();
}

ABaseWeapon* UCombatComponent::SpawnWeapon(TSubclassOf<ABaseWeapon> WeaponClass) const
{
	AActor* Owner = GetOwner();
	if(!IsValid(Owner))
	{
		return nullptr;
	}
	if (Owner->GetLocalRole() < ROLE_Authority)
	{
		return nullptr;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Cast<APawn>(Owner);
	SpawnParams.Owner = Owner;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	return GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass, SpawnParams);

}

