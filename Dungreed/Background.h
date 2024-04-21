#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineCore/TileRenderer.h>

// Ό³Έν :
class ABackground : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ABackground();
	~ABackground();

	// delete Function
	ABackground(const ABackground& _Other) = delete;
	ABackground(ABackground&& _Other) noexcept = delete;
	ABackground& operator=(const ABackground& _Other) = delete;
	ABackground& operator=(ABackground&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer;
	//UTileRenderer* TileRenderer = nullptr;

	UEngineDirectory Dir;
	std::vector<std::vector<int>> TilesData;
};

