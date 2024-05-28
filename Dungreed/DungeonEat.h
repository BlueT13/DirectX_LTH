#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

// Ό³Έν :
class ADungeonEat : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	ADungeonEat();
	~ADungeonEat();

	// delete Function
	ADungeonEat(const ADungeonEat& _Other) = delete;
	ADungeonEat(ADungeonEat&& _Other) noexcept = delete;
	ADungeonEat& operator=(const ADungeonEat& _Other) = delete;
	ADungeonEat& operator=(ADungeonEat&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UDefaultSceneComponent* DefaultComponent = nullptr;
	USpriteRenderer* Renderer0 = nullptr;
	USpriteRenderer* Renderer1 = nullptr;
	UCollision* Collision = nullptr;

	FVector ColScale = { 50, 50, 100 };
};

