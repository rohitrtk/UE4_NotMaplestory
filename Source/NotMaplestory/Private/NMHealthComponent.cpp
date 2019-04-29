#include "NMHealthComponent.h"
#include "GameFramework/Actor.h"

UNMHealthComponent::UNMHealthComponent()
{
	this->StartingHealth = 100.f;
}


void UNMHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	AActor* owner = this->GetOwner();
	if (owner)
	{
		owner->OnTakeAnyDamage.AddDynamic(this, &UNMHealthComponent::HandleTakeAnyDamage);
	}

	this->CurrentHealth = this->StartingHealth;
}

void UNMHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage,
	const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.f) return;

	this->CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, StartingHealth);

	OnHealthChanged.Broadcast(this, CurrentHealth, Damage, DamageType, InstigatedBy, DamageCauser);
}

