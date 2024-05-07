#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/StateManager.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "Cursor.h"
#include "PlayerAttEffect.h"

enum class EPlayerDir
{
	Left,
	Right,
	Up,
	Down,
};

// ���� :
class APlayer : public AActor
{
	GENERATED_BODY(AActor)
	friend class AEnvyrok;

public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;


	static std::shared_ptr<APlayer> MainPlayer;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UStateManager State;

	UDefaultSceneComponent* DefaultComponent = nullptr;
	UDefaultSceneComponent* RotationComponent = nullptr;
	USpriteRenderer* BodyRenderer = nullptr;
	USpriteRenderer* HandRenderer = nullptr;
	USpriteRenderer* WeaponRenderer = nullptr;
	//USpriteRenderer* AttackEffectRenderer = nullptr;
	UCollision* PlayerCollision = nullptr;

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
	float4 PlayerDir = float4::Zero;
	EPlayerDir PlayerMoveDir = EPlayerDir::Right;
	FVector PlayerColScale = { 64,64,100 };
	FVector GravityVector = FVector::Zero;
	FVector JumpVector = FVector::Zero;
	FVector JumpPower = FVector::Zero;
	FVector DashVector = FVector::Zero;
	FVector DashPower = FVector::Zero;
	float DashTime = 0.2f;
	float CurDashTime = 0.0f;

	FVector WindowScale = FVector::Zero;
	std::shared_ptr<ACursor> Cursor = nullptr;
	FVector CursorPos = FVector::Zero;
	FVector InGameCursorPos = FVector::Zero;

	FVector PlayerCenterPos = FVector::Zero;
	std::shared_ptr<APlayerAttEffect> PlayerAttackEffect = nullptr;

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
	void GetHit(float _Damage);

	void PlayerDirCheck();
	void Gravity(float _DeltaTime);
	void GroundUp();

	float Rot = 0.0f;
	float Speed = 360.0f;
	bool WeaponUp = true;
	float PlayerHp = 100.0f;
	float InvincibleTime = 0.5f;
	float AfterImageTime = 0.04f;
	float CurAfterImageTime = 0.0f;
};

