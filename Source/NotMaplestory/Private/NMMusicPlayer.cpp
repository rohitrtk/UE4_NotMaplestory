#include "NMMusicPlayer.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/GameEngine.h"

static float CurrentVolume = 1.f;
static TAutoConsoleVariable<float> CVarVolume
(	
	TEXT("SetBGM"),
	CurrentVolume,
	TEXT("Sets volume of BGM"),
	ECVF_Cheat
);

ANMMusicPlayer::ANMMusicPlayer()
{
	this->AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	this->AudioComponent->SetupAttachment(RootComponent);

}

void ANMMusicPlayer::BeginPlay()
{
	Super::BeginPlay();

	this->AudioComponent->Sound = this->CurrentTrack;

}

void ANMMusicPlayer::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

}

void ANMMusicPlayer::PlayCurrentTrack()
{
	if (!this->CurrentTrack) return;

	AudioComponent->Play();
}
