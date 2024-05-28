#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/StateManager.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "Player.h"
#include "EnvyrokBullet.h"
#include "EnvyrokTrap.h"
#include "FlameSnake.h"

// Ό³Έν :
class AEnvyrok : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	AEnvyrok();
	~AEnvyrok();

	// delete Function
	AEnvyrok(const AEnvyrok& _Other) = delete;
	AEnvyrok(AEnvyrok&& _Other) noexcept = delete;
	AEnvyrok& operator=(const AEnvyrok& _Other) = delete;
	AEnvyrok& operator=(AEnvyrok&& _Other) noexcept = delete;

	void GetHit(int _Damage);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UStateManager State;

	UDefaultSceneComponent* DefaultComponent = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;

	std::shared_ptr<UEngineTexture> ColMapTex = nullptr;
	float ColMapX = 0.0f;
	float ColMapY = 0.0f;
	float ColMapHalfX = 0.0f;
	float ColMapHalfY = 0.0f;

	Color8Bit BottomColor;

	FVector EnvyrokColScale = { 100,100,100 };
	FVector EnvyrokPos = FVector::Zero;
	FVector GravityVector = FVector::Zero;
	FVector JumpVector = FVector::Zero;
	FVector JumpPower = FVector::Zero;
	FVector AirSpikeDir = FVector::Zero;

	void ColorColCheck();

	// State
	void StateInit();
	void Idle(float _DeltaTime);
	void Die(float _DeltaTime);
	void AirSpike_Start(float _DeltaTime);
	void AirSpike(float _DeltaTime);
	void AirSpike_End(float _DeltaTime);
	void SpawnTrap(float _DeltaTime);
	void SpawnFlameSnake(float _DeltaTime);


	void EnvyrokDirCheck();
	void Gravity(float _DeltaTime);

	int Hp = 20;
	float Speed = 850.0f;
	float FireRate = 0.2f;
	float CurFireTime = 0.0f;
	bool ColJump = false;

	float BlockTime = 2.0f;
	float CurBlockTime = 0.0f;
	float AwayTime = 3.0f;
	float CurAwayTime = 0.0f;

	float AttackTime = 1.0f;
	float CurAttackTime = 0.0f;
	int SafeBlockInt = 0;

	std::vector<std::shared_ptr<AEnvyrokTrap>> LeftBlocks;
	std::vector<std::shared_ptr<AEnvyrokTrap>> RightBlocks;
	
	std::vector<std::shared_ptr<AFlameSnake>> FlameSnakes;
};

