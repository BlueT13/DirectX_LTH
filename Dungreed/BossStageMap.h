#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineCore/DefaultSceneComponent.h>

// Ό³Έν :
class ABossStageMap : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	ABossStageMap();
	~ABossStageMap();

	// delete Function
	ABossStageMap(const ABossStageMap& _Other) = delete;
	ABossStageMap(ABossStageMap&& _Other) noexcept = delete;
	ABossStageMap& operator=(const ABossStageMap& _Other) = delete;
	ABossStageMap& operator=(ABossStageMap&& _Other) noexcept = delete;

	void MapRendererSwitch();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UDefaultSceneComponent* DefaultComponent = nullptr;
	USpriteRenderer* Renderer = nullptr;
	USpriteRenderer* ColMapRenderer = nullptr;

	UEngineDirectory Dir;
	std::vector<std::vector<int>> TilesData;
};

