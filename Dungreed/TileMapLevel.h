#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class ATileMapLevel : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	ATileMapLevel();
	~ATileMapLevel();

	// delete Function
	ATileMapLevel(const ATileMapLevel& _Other) = delete;
	ATileMapLevel(ATileMapLevel&& _Other) noexcept = delete;
	ATileMapLevel& operator=(const ATileMapLevel& _Other) = delete;
	ATileMapLevel& operator=(ATileMapLevel&& _Other) noexcept = delete;

	std::shared_ptr<class ATileMap> TileMap = nullptr;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:

};

