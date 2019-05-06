#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NMHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangedSignature, UNMHealthComponent*, HealthComp, float, Health, float, HealthDelta, const class UDamageType*, DamageType, class AController*, InstigatedBy, AActor*, DamageCauser);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NOTMAPLESTORY_API UNMHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UNMHealthComponent();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Component")
	float StartingHealth;
	
	UPROPERTY(BlueprintReadOnly, Category = "Health Component")
	float CurrentHealth;

	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float DamageDelt,
		const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

public:	

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChangedSignature OnHealthChangedSignature;
};
