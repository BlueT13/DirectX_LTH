#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

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

	void MapRendererSwitch();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UDefaultSceneComponent* DefaultComponent = nullptr;
	USpriteRenderer* Renderer0 = nullptr;
	USpriteRenderer* Renderer1 = nullptr;
	USpriteRenderer* Renderer2 = nullptr;

	FVector CameraPos = FVector::Zero;
	float4 UVTest = float4::Zero;
};

