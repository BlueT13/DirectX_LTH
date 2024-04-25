#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/StateManager.h>
#include "Cursor.h"

enum class EPlayerDir
{
	Left,
	Right,
	Up,
	Down,
};

// Ό³Έν :
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

	static std::shared_ptr<APlayer> MainPlayer;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer = nullptr;
	float Speed = 500.0f;

	Color8Bit LeftColor;
	Color8Bit RightColor;
	Color8Bit UpColor;
	Color8Bit DownColor;
	Color8Bit BottomColor;

	FVector PlayerPos = FVector::Zero;
	EPlayerDir PlayerDir = EPlayerDir::Right;
	EPlayerDir PlayerMoveDir = EPlayerDir::Right;
	FVector PlayerScale = FVector::Zero;
	FVector JumpVector = FVector::Zero;
	FVector GravityVector = FVector::Zero;
	FVector JumpPower = FVector::Zero;

	FVector WindowScale = FVector::Zero;
	std::shared_ptr<ACursor> Cursor = nullptr;
	FVector CursorPos = FVector::Zero;
	FVector InGameCursorPos = FVector::Zero;

	void DebugMessageFunction();

	void ColorColCheck();
	void CursorCheck();

	// State
	void StateInit();
	void Idle(float _DeltaTime);
	void Run(float _DeltaTime);
	void Jump(float _DeltaTime);
	void Dash(float _DeltaTime);
	void Die(float _DeltaTime);

	void PlayerDirCheck();
	void Gravity();
	void GroundUp();
};

