#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class ATileMapMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	ATileMapMode();
	~ATileMapMode();

	// delete Function
	ATileMapMode(const ATileMapMode& _Other) = delete;
	ATileMapMode(ATileMapMode&& _Other) noexcept = delete;
	ATileMapMode& operator=(const ATileMapMode& _Other) = delete;
	ATileMapMode& operator=(ATileMapMode&& _Other) noexcept = delete;

	std::shared_ptr<class ATileMap> TileMap = nullptr;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:

};

