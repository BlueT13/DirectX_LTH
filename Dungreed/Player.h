#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/StateManager.h>
#include <EngineCore/DefaultSceneComponent.h>
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
	UDefaultSceneComponent* DefaultComponent = nullptr;
	USpriteRenderer* RotationRenderer = nullptr;
	USpriteRenderer* BodyRenderer = nullptr;
	USpriteRenderer* HandRenderer = nullptr;
	USpriteRenderer* WeaponRenderer = nullptr;

	std::shared_ptr<UEngineTexture> ColMapTex = nullptr;
	float ColMapY = 0.0f;

	Color8Bit BottomColor;
	Color8Bit BottomLeftColor;
	Color8Bit BottomRightColor;
	Color8Bit TopColor;
	Color8Bit LeftColor;
	Color8Bit RightColor;
	Color8Bit GroundColor;
	Color8Bit NextBottomLeftColor;
	Color8Bit NextBottomRightColor;
	Color8Bit NextTopColor;

	FVector PlayerPos = FVector::Zero;
	FVector PlayerNextPos = FVector::Zero;
	FVector PlayerDir = FVector::Zero;
	EPlayerDir PlayerMoveDir = EPlayerDir::Right;
	FVector PlayerScale = FVector::Zero;
	FVector GravityVector = FVector::Zero;
	FVector JumpVector = FVector::Zero;
	FVector JumpPower = FVector::Zero;
	FVector DashVector = FVector::Zero;
	FVector DashPower = FVector::Zero;
	float DashTime = 0.24f;

	FVector WindowScale = FVector::Zero;
	std::shared_ptr<ACursor> Cursor = nullptr;
	FVector CursorPos = FVector::Zero;
	FVector InGameCursorPos = FVector::Zero;

	void DebugMessageFunction();

	void ColorColCheck();
	void CalPlayerPos();
	void CursorCheck();

	// State
	void StateInit();
	void Idle(float _DeltaTime);
	void Run(float _DeltaTime);
	void Jump(float _DeltaTime);
	void Dash(float _DeltaTime);
	void Fall(float _DeltaTime);
	void Die(float _DeltaTime);

	void Attack(float _DeltaTime);

	void PlayerDirCheck();
	void Gravity(float _DeltaTime);
	void GroundUp();


	float Speed = 500.0f;
};

