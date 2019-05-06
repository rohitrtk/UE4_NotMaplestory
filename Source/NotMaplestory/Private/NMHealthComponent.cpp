#include "NMHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/GameEngine.h"

UNMHealthComponent::UNMHealthComponent()
{
	this->StartingHealth = 100.f;
}

void UNMHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Upon owner taking damage, call function HandleTakeAnyDamage
	AActor* owner = this->GetOwner();
	if (owner)
	{
		owner->OnTakeAnyDamage.AddDynamic(this, &UNMHealthComponent::HandleTakeAnyDamage);
	}

	this->CurrentHealth = this->StartingHealth;
}

void UNMHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float DamageDelt,
	const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamageDelt <= 0.f) return;

	this->CurrentHealth = FMath::Clamp(CurrentHealth - DamageDelt, 0.f, StartingHealth);

	// Broadcast the event
	this->OnHealthChangedSignature.Broadcast(this, CurrentHealth, DamageDelt, DamageType, InstigatedBy, DamageCauser);
}

