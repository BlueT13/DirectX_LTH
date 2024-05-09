#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

// Ό³Έν :
class AEnvyrokTrap : public AActor
{
	GENERATED_BODY(AActor)
	friend class AEnvyrok;
public:
	// constrcuter destructer
	AEnvyrokTrap();
	~AEnvyrokTrap();

	// delete Function
	AEnvyrokTrap(const AEnvyrokTrap& _Other) = delete;
	AEnvyrokTrap(AEnvyrokTrap&& _Other) noexcept = delete;
	AEnvyrokTrap& operator=(const AEnvyrokTrap& _Other) = delete;
	AEnvyrokTrap& operator=(AEnvyrokTrap&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UDefaultSceneComponent* DefaultComponent = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;

	FVector ColScale = { 260, 132, 100 };

	bool IsCol = false;
};

