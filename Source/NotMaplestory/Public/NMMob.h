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

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateAnimations();
	void Update();

public:

	ANMMob();

};
