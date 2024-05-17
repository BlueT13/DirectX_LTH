#pragma once
#include <EngineCore/GameMode.h>
#include <EngineCore/Camera.h>
#include <EngineCore/TextWidget.h>
#include <EngineCore/Image.h>
#include "TownMap.h"
#include "Background.h"
#include "Player.h"
#include "DungeonEat.h"

// Ό³Έν :
class APlayGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	APlayGameMode();
	~APlayGameMode();

	// delete Function
	APlayGameMode(const APlayGameMode& _Other) = delete;
	APlayGameMode(APlayGameMode&& _Other) noexcept = delete;
	APlayGameMode& operator=(const APlayGameMode& _Other) = delete;
	APlayGameMode& operator=(APlayGameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel) override;
	void LevelStart(ULevel* _PrevLevel) override;

private:
	std::shared_ptr<UCamera> Camera = nullptr;
	std::shared_ptr<ABackground> Background = nullptr;
	std::shared_ptr<ATownMap> TownMap = nullptr;
	std::shared_ptr<APlayer> Player = nullptr;
	std::shared_ptr<ADungeonEat> DungeonEat = nullptr;

	UTextWidget* PlayerFullHpUI = nullptr;
	UTextWidget* PlayerHpUI = nullptr;
	std::string PlayerHpString = "";
	UImage* HpImage = nullptr;

	float MapX = 0.0f;
	float MapY = 0.0f;
	float MapHalfX = 0.0f;
	float MapHalfY = 0.0f;
};

