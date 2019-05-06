// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "NMMob.generated.h"

UCLASS()
class NOTMAPLESTORY_API ANMMob : public APaperCharacter
{
	GENERATED_BODY()
private:

	virtual void Tick(float deltaTime) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	class UPaperFlipbook* IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	class UPaperFlipbook* MoveAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	class UPaperFlipbook* HitAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	class UPaperFlipbook* DeathAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UNMHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	FString Tag;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateAnimations();
	void Update();

	UFUNCTION()
	void OnHealthChanged(UNMHealthComponent* HealthComp, float Health, float HealthDelta,
		const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

public:

	ANMMob();

	FORCEINLINE const FString& GetTag() { return this->Tag; }

};
