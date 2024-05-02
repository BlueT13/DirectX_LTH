#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineCore/TileRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

// ���� :
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

	void MapRendererSwitch();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UDefaultSceneComponent* DefaultComponent = nullptr;
	USpriteRenderer* Renderer = nullptr;
	USpriteRenderer* ColMapRenderer = nullptr;
	//UTileRenderer* TileRenderer = nullptr;

	UEngineDirectory Dir;
	std::vector<std::vector<int>> TilesData;
};

