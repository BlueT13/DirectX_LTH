#pragma once
#include <EngineCore/GameMode.h>
#include "Player.h"
#include "Background.h"

// ���� :
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
	std::shared_ptr<ABackground> Background = nullptr;
	std::shared_ptr<UCamera> Camera = nullptr;
	std::shared_ptr<APlayer> Player = nullptr;
};

