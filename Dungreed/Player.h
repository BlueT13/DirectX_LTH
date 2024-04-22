#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/StateManager.h>

enum class EPlayerDir
{
	Left,
	Right,
};

// ���� :
class APlayer : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	UStateManager State;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer = nullptr;
	float Speed = 500.0f;
	Color8Bit Color;
	FVector PlayerPos = FVector::Zero;
	EPlayerDir PlayerDir = EPlayerDir::Right;
	FVector PlayerScale = FVector::Zero;
	FVector JumpVector = FVector::Zero;
	FVector GravityVector = FVector::Zero;
	FVector JumpPower = FVector::Zero;

	void DebugMessageFunction();
	void ColorColCheck(float _DeltaTime);

	// State
	void StateInit();
	void Die(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Jump(float _DeltaTime);
	void Run(float _DeltaTime);

	void PlayerDirCheck();
	void Gravity();
};

