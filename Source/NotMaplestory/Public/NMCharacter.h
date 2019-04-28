#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "NMCharacter.generated.h"

UCLASS()
class NOTMAPLESTORY_API ANMCharacter : public APaperCharacter
{
	GENERATED_BODY()

private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	const float CapsuleHeight = 35.f;
	const float CapsuleProneheight = 20.f;

	FTimerHandle AttackTimerHandle;

	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	class UPaperFlipbook* IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	class UPaperFlipbook* RunAnimation;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	//class UPaperFlipbook* DeathAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	class UPaperFlipbook* JumpAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	class UPaperFlipbook* ProneAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	class UPaperFlipbook* ProneAttackAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	class UPaperFlipbook* AttackAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	class UPaperFlipbook* ClimbRopeAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	bool bIsAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	bool bIsProne;

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Update();
	void MoveRight(float delta);
	void UpdateAnimations(const FVector& velocity);
	void Attack();

	UFUNCTION()
	void StopAttack();

	void Prone();
	void StopProne();

public:

	ANMCharacter();

	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return this->CameraComponent; }
	FORCEINLINE class USpringArmComponent* GetSpringArmComponent() const { return this->SpringArm; }
};
