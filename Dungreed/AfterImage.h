#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

// Ό³Έν :
class AAfterImage : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AAfterImage();
	~AAfterImage();

	// delete Function
	AAfterImage(const AAfterImage& _Other) = delete;
	AAfterImage(AAfterImage&& _Other) noexcept = delete;
	AAfterImage& operator=(const AAfterImage& _Other) = delete;
	AAfterImage& operator=(AAfterImage&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UDefaultSceneComponent* DefaultComponent = nullptr;
	USpriteRenderer* Renderer = nullptr;
};

