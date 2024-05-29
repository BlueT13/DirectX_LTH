#pragma once
#include "Monster.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/StateManager.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "EnvyrokBullet.h"

// Ό³Έν :
class AFlameSnake : public AMonster
{
	GENERATED_BODY(AMonster)
public:
	// constrcuter destructer
	AFlameSnake();
	~AFlameSnake();

	// delete Function
	AFlameSnake(const AFlameSnake& _Other) = delete;
	AFlameSnake(AFlameSnake&& _Other) noexcept = delete;
	AFlameSnake& operator=(const AFlameSnake& _Other) = delete;
	AFlameSnake& operator=(AFlameSnake&& _Other) noexcept = delete;

	void ChangeDir();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UStateManager State;

	std::shared_ptr<UEngineTexture> ColMapTex = nullptr;
	float ColMapX = 0.0f;
	float ColMapY = 0.0f;
	float ColMapHalfX = 0.0f;
	float ColMapHalfY = 0.0f;

	FVector FlameSnakeColScale = { 244, 288, 100 };

	// State
	void StateInit();
	void Generation(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Attack(float _DeltaTime);

	float FireRate = 3.0f;
	float CurFireTime = 0.0f;
};

