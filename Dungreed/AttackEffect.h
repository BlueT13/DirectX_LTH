#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

// Ό³Έν :
class AAttackEffect : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AAttackEffect();
	~AAttackEffect();

	// delete Function
	AAttackEffect(const AAttackEffect& _Other) = delete;
	AAttackEffect(AAttackEffect&& _Other) noexcept = delete;
	AAttackEffect& operator=(const AAttackEffect& _Other) = delete;
	AAttackEffect& operator=(AAttackEffect&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* AttackEffectRenderer = nullptr;
};

