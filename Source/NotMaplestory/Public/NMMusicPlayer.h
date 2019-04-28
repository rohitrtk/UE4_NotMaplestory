#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NMMusicPlayer.generated.h"

UCLASS()
class NOTMAPLESTORY_API ANMMusicPlayer : public AActor
{
	GENERATED_BODY()
	
private:

	virtual void Tick(float deltaTime) override;

public:	
	ANMMusicPlayer();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Music")
	class USoundBase* CurrentTrack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category  = "Music")
	class UAudioComponent* AudioComponent;

	UFUNCTION()
	void PlayCurrentTrack();

protected:
	virtual void BeginPlay() override;

};
