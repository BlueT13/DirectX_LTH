#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

// Ό³Έν :
class AMonster : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AMonster();
	~AMonster();

	// delete Function
	AMonster(const AMonster& _Other) = delete;
	AMonster(AMonster&& _Other) noexcept = delete;
	AMonster& operator=(const AMonster& _Other) = delete;
	AMonster& operator=(AMonster&& _Other) noexcept = delete;

	void GetHit(int _Damage);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UDefaultSceneComponent* DefaultComponent = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;

	int MonsterHp = 0;

private:

};

