#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/StateManager.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "Player.h"

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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UStateManager State;

	UDefaultSceneComponent* DefaultComponent = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;

	std::shared_ptr<UEngineTexture> ColMapTex = nullptr;
	float ColMapY = 0.0f;

	Color8Bit BottomColor;

	FVector EnvyrokColScale = { 100,100,100 };
	FVector EnvyrokPos = FVector::Zero;
	FVector GravityVector = FVector::Zero;
	FVector JumpVector = FVector::Zero;
	FVector JumpPower = FVector::Zero;

	void ColorColCheck();

	// State
	void StateInit();
	void Idle(float _DeltaTime);
	void Die(float _DeltaTime);
	void AirSpike_Start(float _DeltaTime);
	void AirSpike(float _DeltaTime);
	void AirSpike_End(float _DeltaTime);


	void EnvyrokDirCheck();
	void Gravity(float _DeltaTime);
};

