#pragma once
#include <EngineCore/GameMode.h>
#include <EngineCore/TextWidget.h>
#include <EngineCore/Image.h>
#include "BossStageMap.h"
#include "Player.h"
#include "Envyrok.h"

// Ό³Έν :
class ABossStageMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	ABossStageMode();
	~ABossStageMode();

	// delete Function
	ABossStageMode(const ABossStageMode& _Other) = delete;
	ABossStageMode(ABossStageMode&& _Other) noexcept = delete;
	ABossStageMode& operator=(const ABossStageMode& _Other) = delete;
	ABossStageMode& operator=(ABossStageMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel) override;
	void LevelStart(ULevel* _PrevLevel) override;

private:
	std::shared_ptr<UCamera> Camera = nullptr;
	std::shared_ptr<ABossStageMap> BossStageMap = nullptr;
	std::shared_ptr<APlayer> Player = nullptr;
	std::shared_ptr<AEnvyrok> Envyrok = nullptr;
	
	UTextWidget* PlayerFullHpUI = nullptr;
	UTextWidget* PlayerHpUI = nullptr;
	std::string PlayerHpString = "";
	UImage* HpImage = nullptr;

	float MapX = 0.0f;
	float MapY = 0.0f;
	float MapHalfX = 0.0f;
	float MapHalfY = 0.0f;

	UEngineSoundPlayer BossStageSound;
};
