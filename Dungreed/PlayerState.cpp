#include "PreCompile.h"
#include "Player.h"
#include "AfterImage.h"

void APlayer::StateInit()
{
	// 스테이트 생성
	State.CreateState("PlayerIdle");
	State.CreateState("PlayerRun");
	State.CreateState("PlayerJump");
	State.CreateState("PlayerDash");
	State.CreateState("PlayerFall");
	State.CreateState("PlayerDie");

	// 함수들 세팅
	State.SetUpdateFunction("PlayerIdle", std::bind(&APlayer::Idle, this, std::placeholders::_1));
	State.SetStartFunction("PlayerIdle", [this]()
		{
			this->BodyRenderer->ChangeAnimation("PlayerIdle");
		});


	State.SetUpdateFunction("PlayerRun", std::bind(&APlayer::Run, this, std::placeholders::_1));
	State.SetStartFunction("PlayerRun", [this]()
		{
			this->BodyRenderer->ChangeAnimation("PlayerRun");
		});

	State.SetUpdateFunction("PlayerJump", std::bind(&APlayer::Jump, this, std::placeholders::_1));
	State.SetStartFunction("PlayerJump", [this]()
		{
			// 점프 시작할 때 JumpVector값 한번만 대입
			JumpVector = FVector::Up * 1200.0f;
			this->BodyRenderer->ChangeAnimation("PlayerJump");
		});

	State.SetUpdateFunction("PlayerDash", std::bind(&APlayer::Dash, this, std::placeholders::_1));
	State.SetStartFunction("PlayerDash", [this]()
		{
			GravityVector = FVector::Zero;
			DashVector = PlayerDir * 1600.0f;
			CurDashTime = DashTime;
			this->BodyRenderer->ChangeAnimation("PlayerJump");

			// CurAfterImageTime = AfterImageTime;
		});

	State.SetUpdateFunction("PlayerFall", std::bind(&APlayer::Fall, this, std::placeholders::_1));
	State.SetStartFunction("PlayerFall", [this]()
		{
			this->BodyRenderer->ChangeAnimation("PlayerJump");
		});

	State.SetUpdateFunction("PlayerDie", std::bind(&APlayer::Die, this, std::placeholders::_1));
	State.SetStartFunction("PlayerDie", [this]()
		{
			this->BodyRenderer->ChangeAnimation("PlayerDie");
			PlayerCollision->SetActive(false);
			if (PlayerHp < 0)
			{
				PlayerHp = 0;
			}
		});

	State.ChangeState("PlayerIdle");
}

void APlayer::Idle(float _DeltaTime)
{
	PlayerDirCheck();

	// 중력
	Gravity(_DeltaTime);
	ColorColCheck();
	if (BottomColor == Color8Bit::Black || BottomColor == Color8Bit::Magenta || BottomColor == Color8Bit::Red)
	{
		GravityVector = FVector::Zero;
	}

	PlayerCollision->CollisionStay(ECollisionOrder::EnvyrokTrap, [=](std::shared_ptr<UCollision> _Collision)
		{
			GravityVector = FVector::Zero;
		}
	);

	AddActorLocation(GravityVector * _DeltaTime);
	GroundUp();

	// 공격
	if (true == IsDown(VK_LBUTTON))
	{
		Attack(_DeltaTime);
	}

	// 상태 변화
	if (true == IsPress('A') || true == IsPress('D'))
	{
		State.ChangeState("PlayerRun");
		return;
	}

	if (true == IsPress(VK_SPACE) || true == IsPress('W'))
	{
		State.ChangeState("PlayerJump");
		return;
	}

	if (true == IsDown(VK_RBUTTON))
	{
		State.ChangeState("PlayerDash");
		return;
	}

	// 하단 점프
	if (true == IsDown('S') && BottomColor != Color8Bit::Black)
	{
		IsDownJump = true;
		State.ChangeState("PlayerFall");
		return;
	}
}

void APlayer::Run(float _DeltaTime)
{
	PlayerDirCheck();

	// 중력
	Gravity(_DeltaTime);
	ColorColCheck();
	if (BottomColor == Color8Bit::Black || BottomColor == Color8Bit::Magenta)
	{
		GravityVector = FVector::Zero;
	}
	AddActorLocation(GravityVector * _DeltaTime);

	// 경사 이동
	if (BottomRightColor == Color8Bit::Red && PlayerMoveDir == EPlayerDir::Right)
	{
		GravityVector = FVector::Zero;
		AddActorLocation(FVector::Up);
	}
	if (BottomColor == Color8Bit::White && BottomRightColor == Color8Bit::Red && PlayerMoveDir == EPlayerDir::Left)
	{
		GravityVector = FVector::Zero;
		AddActorLocation(FVector::Down);
	}
	if (BottomLeftColor == Color8Bit::Red && PlayerMoveDir == EPlayerDir::Left)
	{
		GravityVector = FVector::Zero;
		AddActorLocation(FVector::Up);
	}
	if (BottomColor == Color8Bit::White && BottomLeftColor == Color8Bit::Red && PlayerMoveDir == EPlayerDir::Right)
	{
		GravityVector = FVector::Zero;
		AddActorLocation(FVector::Down);
	}

	// 이동
	if (true == IsPress('A') && LeftColor != Color8Bit::Black)
	{
		AddActorLocation(FVector::Left * Speed * _DeltaTime);
	}
	if (true == IsPress('D') && RightColor != Color8Bit::Black)
	{
		AddActorLocation(FVector::Right * Speed * _DeltaTime);
	}
	GroundUp();

	// 공격
	if (true == IsDown(VK_LBUTTON))
	{
		Attack(_DeltaTime);
	}

	// 상태 변화
	if (true == IsDown(VK_SPACE) || true == IsPress('W'))
	{
		State.ChangeState("PlayerJump");
		return;
	}

	if (true == IsFree('A') && true == IsFree('D'))
	{
		State.ChangeState("PlayerIdle");
		return;
	}

	if (true == IsDown(VK_RBUTTON))
	{
		State.ChangeState("PlayerDash");
		return;
	}

	// 하단 점프
	if (true == IsDown('S') && BottomColor != Color8Bit::Black)
	{
		IsDownJump = true;
		State.ChangeState("PlayerFall");
		return;
	}
}

void APlayer::Jump(float _DeltaTime)
{
	PlayerDirCheck();

	// 중력
	Gravity(_DeltaTime);
	JumpPower = JumpVector + GravityVector;
	ColorColCheck();

	if (TopColor == Color8Bit::Black)
	{
		JumpVector = FVector::Zero;
	}

	if (0 >= JumpPower.Y)
	{
		if (BottomColor == Color8Bit::Black || BottomColor == Color8Bit::Magenta || BottomColor == Color8Bit::Red)
		{
			GravityVector = FVector::Zero;
			State.ChangeState("PlayerIdle");
			return;
		}
	}

	PlayerCollision->CollisionStay(ECollisionOrder::EnvyrokTrap, [=](std::shared_ptr<UCollision> _Collision)
		{
			State.ChangeState("PlayerIdle");
		}
	);

	AddActorLocation(JumpPower * _DeltaTime);

	// 공중에서 이동
	if (true == IsPress('A') && LeftColor != Color8Bit::Black)
	{
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
	}
	if (true == IsPress('D') && RightColor != Color8Bit::Black)
	{
		AddActorLocation(FVector::Right * _DeltaTime * Speed);
	}

	// 공격
	if (true == IsDown(VK_LBUTTON))
	{
		Attack(_DeltaTime);
	}

	// 상태 변화
	if (true == IsDown(VK_RBUTTON))
	{
		State.ChangeState("PlayerDash");
		return;
	}

}

void APlayer::Dash(float _DeltaTime)
{
	PlayerDirCheck();
	ColorColCheck();
	CurDashTime -= _DeltaTime;

	// 잔상
	CurAfterImageTime -= _DeltaTime;
	if (CurAfterImageTime < 0)
	{
		CurAfterImageTime = AfterImageTime;

		std::shared_ptr<AAfterImage> AfterImage = GetWorld()->SpawnActor<AAfterImage>("AfterImage", EUpdateOrder::Player);
		FVector UpPos = { 0,64,0 };
		FVector AfterImagePos = GetActorLocation() + UpPos;
		AfterImage->SetActorLocation(AfterImagePos);
		if (0 <= PlayerDir.X)
		{
			AfterImage->SetActorScale3D({ 1.0f, 1.0f, 1.0f });
		}
		else
		{
			AfterImage->SetActorScale3D({ -1.0f, 1.0f, 1.0f });
		}
	}

	// Dash 끝
	if (CurDashTime <= 0)
	{
		CurDashTime = DashTime;
		DashVector = FVector::Zero;
		State.ChangeState("PlayerFall");
		return;
	}

	// PlayerNextPos 계산
	PlayerPos = GetActorLocation();
	PlayerNextPos = PlayerPos + (DashVector * _DeltaTime);
	PlayerNextPos.Y = ColMapY - PlayerPos.Y;
	PlayerNextPos /= UDungreedConstValue::AutoSize;

	// 공격
	if (true == IsDown(VK_LBUTTON))
	{
		Attack(_DeltaTime);
	}

	// 벽이 아니면 이동
	if (0 <= PlayerDir.X && NextBottomRightColor != Color8Bit::Black && NextTopColor != Color8Bit::Black && NextBottomLeftColor != Color8Bit::Black && NextTopColor != Color8Bit::Black)
	{
		AddActorLocation(DashVector * _DeltaTime);
	}
	else if (0 > PlayerDir.X && NextBottomRightColor != Color8Bit::Black && NextTopColor != Color8Bit::Black && NextBottomLeftColor != Color8Bit::Black && NextTopColor != Color8Bit::Black)
	{
		AddActorLocation(DashVector * _DeltaTime);
	}
	else
	{
		return;
	}
}

void APlayer::Fall(float _DeltaTime)
{
	PlayerDirCheck();
	Gravity(_DeltaTime);
	ColorColCheck();

	PlayerCollision->CollisionStay(ECollisionOrder::EnvyrokTrap, [=](std::shared_ptr<UCollision> _Collision)
		{
			State.ChangeState("PlayerIdle");
		}
	);

	if (true == IsPress('A') && LeftColor != Color8Bit::Black)
	{
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
	}
	if (true == IsPress('D') && RightColor != Color8Bit::Black)
	{
		AddActorLocation(FVector::Right * _DeltaTime * Speed);
	}
	AddActorLocation(GravityVector * _DeltaTime);

	// 공격
	if (true == IsDown(VK_LBUTTON))
	{
		Attack(_DeltaTime);
	}

	if (true == IsDown(VK_RBUTTON))
	{
		State.ChangeState("PlayerDash");
		return;
	}

	if (TopColor == Color8Bit::Magenta || TopColor == Color8Bit::Red || BottomColor == Color8Bit::Black)
	{
		IsDownJump = false;
	}

	if ((BottomColor == Color8Bit::Black || BottomColor == Color8Bit::Magenta || BottomColor == Color8Bit::Red) && IsDownJump == false)
	{
		GravityVector = FVector::Zero;
		State.ChangeState("PlayerIdle");
		return;
	}
}

void APlayer::Die(float _DeltaTime)
{
	// 중력
	Gravity(_DeltaTime);
	ColorColCheck();
	if (BottomColor == Color8Bit::Black || BottomColor == Color8Bit::Magenta || BottomColor == Color8Bit::Red)
	{
		GravityVector = FVector::Zero;
	}

	PlayerCollision->CollisionStay(ECollisionOrder::EnvyrokTrap, [=](std::shared_ptr<UCollision> _Collision)
		{
			GravityVector = FVector::Zero;
		}
	);

	AddActorLocation(GravityVector * _DeltaTime);
	GroundUp();
}

void APlayer::Attack(float _DeltaTime)
{
	PlayerDirCheck();

	WeaponUp = !WeaponUp;
	if (false == WeaponUp)
	{
		RotationComponent->SetPosition({ 30, 24, 0 });
		WeaponRenderer->SetPosition({ -32, -24, 0 });
		WeaponRenderer->SetRotationDeg({ 0, 0, 165 });
		WeaponRenderer->SetOrder(ERenderOrder::WeaponFront);
	}
	else
	{
		RotationComponent->SetPosition({ 24, 40, 0 });
		WeaponRenderer->SetPosition({ -4, 24, 0 });
		WeaponRenderer->SetRotationDeg({ 0, 0, 15 });
		WeaponRenderer->SetOrder(ERenderOrder::WeaponBack);
	}

	//AttackEffectRenderer->ChangeAnimation("AttackEffect");
	PlayerAttackEffect = GetWorld()->SpawnActor<APlayerAttEffect>("PlayerAttackEffect", EUpdateOrder::Player);
	FVector UpPos = { 0,40,0 };
	PlayerCenterPos = GetActorLocation() + UpPos;
	FVector AttackDir = InGameCursorPos - PlayerCenterPos;
	AttackDir = AttackDir.Normalize2DReturn();
	PlayerAttackEffect->SetActorLocation(PlayerCenterPos + AttackDir * 60);
	float AttackRot = AttackDir.RightVectorToAngle2DDeg();
	PlayerAttackEffect->SetActorRotation({ 0.0f, 0.0f, AttackRot });
}

void APlayer::GetHit(int _Damage)
{
	PlayerHp -= _Damage;

	if (PlayerHp <= 0)
	{
		State.ChangeState("PlayerDie");
		return;
	}

	BodyRenderer->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });
	PlayerCollision->SetActive(false);

	DelayCallBack(1.0f, [=]() {
		BodyRenderer->SetMulColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		PlayerCollision->SetActive(true);
		});
}

void APlayer::PlayerDirCheck()
{

	PlayerDir = InGameCursorPos - PlayerPos;
	PlayerDir = PlayerDir.Normalize2DReturn();
	Rot = PlayerDir.RightVectorToAngle2DDeg();

	if (0 <= PlayerDir.X)
	{
		DefaultComponent->SetScale({ 1.0f, 1.0f, 1.0f });
		RotationComponent->SetRotationDeg({ 0.0f, 0.0f, Rot });
	}
	else
	{
		DefaultComponent->SetScale({ -1.0f, 1.0f, 1.0f });
		RotationComponent->SetRotationDeg({ 0.0f, 0.0f, 180.0f - Rot });
	}

	if (true == IsPress('A'))
	{
		PlayerMoveDir = EPlayerDir::Left;
	}
	if (true == IsPress('D'))
	{
		PlayerMoveDir = EPlayerDir::Right;
	}
	if (true == IsPress('W') || true == IsDown(VK_SPACE))
	{
		PlayerMoveDir = EPlayerDir::Up;
	}
	if (true == IsPress('S'))
	{
		PlayerMoveDir = EPlayerDir::Down;
	}
}

void APlayer::Gravity(float _DeltaTime)
{
	GravityVector += FVector::Down * 2000.0f * _DeltaTime;
}

void APlayer::GroundUp()
{
	while (GroundColor != Color8Bit::White)
	{
		ColorColCheck();
		AddActorLocation(FVector::Up);
	}
}
