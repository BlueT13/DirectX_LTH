#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

// Ό³Έν :
class AMyMap : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	AMyMap();
	~AMyMap();

	// delete Function
	AMyMap(const AMyMap& _Other) = delete;
	AMyMap(AMyMap&& _Other) noexcept = delete;
	AMyMap& operator=(const AMyMap& _Other) = delete;
	AMyMap& operator=(AMyMap&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer = nullptr;
};

