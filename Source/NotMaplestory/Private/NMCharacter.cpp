#include "NMCharacter.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "NMHealthComponent.h"
#include "GameFramework/Actor.h"
#include "NMMob.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/GameEngine.h"

ANMCharacter::ANMCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;

	this->GetCapsuleComponent()->SetCapsuleHalfHeight(CapsuleHeight);
	this->GetCapsuleComponent()->SetCapsuleRadius(20.f);

	this->SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	this->SpringArm->SetupAttachment(RootComponent);
	this->SpringArm->bAbsoluteRotation = true;
	this->SpringArm->bDoCollisionTest = false;
	this->SpringArm->RelativeRotation = FRotator(0.f, -90.f, 0.f);
	this->SpringArm->TargetArmLength = 300.f;

	this->CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	this->CameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	this->CameraComponent->OrthoWidth = 1024.f;
	this->CameraComponent->bAutoActivate = true;
	this->CameraComponent->bUsePawnControlRotation = false;
	this->CameraComponent->SetupAttachment(this->SpringArm);

	this->GetCharacterMovement()->JumpZVelocity = 600.f;
	this->GetCharacterMovement()->MaxWalkSpeed = 500.f;
	this->GetCharacterMovement()->GroundFriction = 4.f;
	this->GetCharacterMovement()->GravityScale = 2.f;
	this->GetCharacterMovement()->AirControl = .5f;

	this->GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;
	this->GetCharacterMovement()->bConstrainToPlane = true;
	this->GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.f, -1.f, 0.f));

	this->AttackCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Attack Collider"));
	this->AttackCollider->SetupAttachment(RootComponent);
	this->AttackCollider->SetRelativeLocation(FVector(45.f, 0.f, 0.f));
	this->AttackCollider->SetBoxExtent(FVector(24.f, 8.f, 32.f));
	this->AttackCollider->bAbsoluteRotation = false;

	//this->HealthComponent = CreateDefaultSubobject<UNMHealthComponent>(TEXT("Health Component"));
}

void ANMCharacter::BeginPlay()
{
	Super::BeginPlay();

	//this->HealthComponent->OnHealthChanged.AddDynamic(this, &ANMCharacter::OnHealthChanged);
}

void ANMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Update();
}

void ANMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ANMCharacter::Jump);
	PlayerInputComponent->BindAction("Prone", IE_Pressed, this, &ANMCharacter::Prone);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ANMCharacter::Attack);

	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ANMCharacter::StopJumping);
	PlayerInputComponent->BindAction("Prone", IE_Released, this, &ANMCharacter::StopProne);

	PlayerInputComponent->BindAxis("MoveRight", this, &ANMCharacter::MoveRight);
}

void ANMCharacter::MoveRight(float delta)
{
	if (bIsAttacking || bIsProne) return;

	AddMovementInput(FVector(1.f, 0.f, 0.f), delta);
}

void ANMCharacter::Update()
{
	FVector playerVelocity = this->GetVelocity();
	UpdateAnimations(playerVelocity);
	
	float playerDirection = playerVelocity.X;
	
	if (!Controller || bIsAttacking) return;

	if (playerDirection > 0.f)
	{
		Controller->SetControlRotation(FRotator(0.f, 0.f, 0.f));
	}
	else if (playerDirection < 0.f)
	{
		Controller->SetControlRotation(FRotator(0.f, 180.f, 0.f));
	}
}

void ANMCharacter::UpdateAnimations(const FVector& velocity)
{
	float playerSpeed = velocity.SizeSquared();

	UPaperFlipbook* currentAnimation = nullptr;

	
	if (this->bIsAttacking && AttackAnimation)
	{
		currentAnimation = this->AttackAnimation;
	}
	else if (GetMovementComponent()->IsFalling() && JumpAnimation)
	{
		currentAnimation = this->JumpAnimation;
	}
	else if (this->bIsProne && ProneAnimation)
	{
		currentAnimation = this->ProneAnimation;
	}
	else if (playerSpeed > 0.f && RunAnimation)
	{
		currentAnimation = this->RunAnimation;
	}
	else if (IdleAnimation)
	{
		currentAnimation = this->IdleAnimation;
	}

	if (GetSprite()->GetFlipbook() != currentAnimation)
	{
		GetSprite()->SetFlipbook(currentAnimation);
	}
}

void ANMCharacter::Attack()
{
	if (bIsAttacking) return;

	bIsAttacking = true;

	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &ANMCharacter::StopAttack, .5f);
}

void ANMCharacter::StopAttack()
{
	bIsAttacking = false;

	TArray<AActor*> overlappingActors;
	TSubclassOf<ANMMob> mobFilter;

	this->AttackCollider->GetOverlappingActors(overlappingActors);
	for (const auto& a : overlappingActors)
	{
		ANMMob* mob = Cast<ANMMob>(a);
		if (mob)
		{	
			//GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Red, mob->GetTag());
			//UGameplayStatics::ApplyDamage(mob, 100.f, this->GetInstigatorController(), this, DamageType);
			UGameplayStatics::ApplyDamage(mob, 100.f, GetController(), this, DamageType);
			break;
		}
	}

	GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
}

void ANMCharacter::Prone()
{
	this->bIsProne = true;
	this->GetCapsuleComponent()->SetCapsuleHalfHeight(CapsuleProneheight);
}

void ANMCharacter::StopProne() 
{ 
	this->bIsProne = false; 
	this->GetCapsuleComponent()->SetCapsuleHalfHeight(CapsuleHeight);
}


void ANMCharacter::OnHealthChanged(class UNMHealthComponent* HealthComp,
	float Health, float HealthDelta, const class UDamageType* Damage, class AController* InstigatedBy, AActor* DamageCauser)
{
}
