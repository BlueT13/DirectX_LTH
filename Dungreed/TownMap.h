#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineCore/TileRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

// Ό³Έν :
class ATownMap : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	ATownMap();
	~ATownMap();

	// delete Function
	ATownMap(const ATownMap& _Other) = delete;
	ATownMap(ATownMap&& _Other) noexcept = delete;
	ATownMap& operator=(const ATownMap& _Other) = delete;
	ATownMap& operator=(ATownMap&& _Other) noexcept = delete;

	void MapRendererSwitch();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UDefaultSceneComponent* DefaultComponent = nullptr;
	USpriteRenderer* ColMapRenderer = nullptr;
	USpriteRenderer* Renderer = nullptr;
	//UTileRenderer* TileRenderer = nullptr;

	UEngineDirectory Dir;
	std::vector<std::vector<int>> TilesData;
};

