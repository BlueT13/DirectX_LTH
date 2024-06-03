#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineCore/TileRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

// Ό³Έν :
class ABossStageTileMap : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	ABossStageTileMap();
	~ABossStageTileMap();

	// delete Function
	ABossStageTileMap(const ABossStageTileMap& _Other) = delete;
	ABossStageTileMap(ABossStageTileMap&& _Other) noexcept = delete;
	ABossStageTileMap& operator=(const ABossStageTileMap& _Other) = delete;
	ABossStageTileMap& operator=(ABossStageTileMap&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UDefaultSceneComponent* DefaultComponent = nullptr;
	UTileRenderer* TileRenderer = nullptr;

	UEngineDirectory Dir;
	std::vector<std::vector<int>> TilesData;
};

