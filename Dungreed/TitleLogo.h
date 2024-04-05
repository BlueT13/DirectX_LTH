#pragma once
#include <Enginecore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

// Ό³Έν :
class ATitleLogo : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ATitleLogo();
	~ATitleLogo();

	// delete Function
	ATitleLogo(const ATitleLogo& _Other) = delete;
	ATitleLogo(ATitleLogo&& _Other) noexcept = delete;
	ATitleLogo& operator=(const ATitleLogo& _Other) = delete;
	ATitleLogo& operator=(ATitleLogo&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void RendererOff();
	void RendererOn();

private:
	USpriteRenderer* Renderer = nullptr;
};

