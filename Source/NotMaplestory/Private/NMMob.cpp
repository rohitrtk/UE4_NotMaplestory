#include "NMMob.h"
#include "Components/CapsuleComponent.h"
#include "Engine/GameEngine.h"
#include "NMHealthComponent.h"

ANMMob::ANMMob()
{
	this->HealthComponent = CreateDefaultSubobject<UNMHealthComponent>(TEXT("Health Component"));

	this->Tag = "Undefined Mob";
}

void ANMMob::BeginPlay()
{
	Super::BeginPlay();

	// Whenever we receive the broadcast from the health component, call function OnHealthChanged
	this->HealthComponent->OnHealthChangedSignature.AddDynamic(this, &ANMMob::OnHealthChanged);
}

void ANMMob::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void ANMMob::Update()
{
}

void ANMMob::OnHealthChanged(UNMHealthComponent* HealthComp, float Health, float HealthDelta,
	const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Red, "Health Changed in Mob");
	
	if (Health <= 0.f)
	{
		SetLifeSpan(2.f);
	}
}
