#include "NMMob.h"
#include "Components/CapsuleComponent.h"

ANMMob::ANMMob()
{
}

void ANMMob::BeginPlay()
{
	Super::BeginPlay();
}

void ANMMob::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void ANMMob::Update()
{
}

void ANMMob::OnHealthChanged(UNMHealthComponent* HealthComp,
	float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	// Temp
	if (Health <= 0.f)
	{
		Destroy();
	}
}
