#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

// Ό³Έν :
class APlayerAttEffect : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	APlayerAttEffect();
	~APlayerAttEffect();

	// delete Function
	APlayerAttEffect(const APlayerAttEffect& _Other) = delete;
	APlayerAttEffect(APlayerAttEffect&& _Other) noexcept = delete;
	APlayerAttEffect& operator=(const APlayerAttEffect& _Other) = delete;
	APlayerAttEffect& operator=(APlayerAttEffect&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UDefaultSceneComponent* DefaultComponent = nullptr;
	USpriteRenderer* PlayerAttEffectRenderer = nullptr;
	UCollision* PlayerAttEffectCollision = nullptr;

	FVector PlayerAttColScale = { 150, 150, 100 };
};

