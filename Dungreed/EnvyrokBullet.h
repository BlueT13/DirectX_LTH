#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

// Ό³Έν :
class AEnvyrokBullet : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AEnvyrokBullet();
	~AEnvyrokBullet();

	// delete Function
	AEnvyrokBullet(const AEnvyrokBullet& _Other) = delete;
	AEnvyrokBullet(AEnvyrokBullet&& _Other) noexcept = delete;
	AEnvyrokBullet& operator=(const AEnvyrokBullet& _Other) = delete;
	AEnvyrokBullet& operator=(AEnvyrokBullet&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UDefaultSceneComponent* DefaultComponent = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;

	FVector ColScale = { 84, 84, 84 };
};

