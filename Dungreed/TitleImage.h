#pragma once
#include <Enginecore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

// Ό³Έν :
class ATitleImage : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ATitleImage();
	~ATitleImage();

	// delete Function
	ATitleImage(const ATitleImage& _Other) = delete;
	ATitleImage(ATitleImage&& _Other) noexcept = delete;
	ATitleImage& operator=(const ATitleImage& _Other) = delete;
	ATitleImage& operator=(ATitleImage&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	//void RendererOff();
	//void RendererOn();

private:
	UDefaultSceneComponent* DefaultComponent = nullptr;
	USpriteRenderer* BackgroundRenderer = nullptr;
	USpriteRenderer* TitleImageRenderer = nullptr;

	float4 UVTest = float4::Zero;
};

