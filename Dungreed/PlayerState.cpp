#include "PreCompile.h"
#include "Player.h"

void APlayer::StateInit()
{
	// 스테이트 생성
	State.CreateState("Idle");
	State.CreateState("Run");
	State.CreateState("Jump");
	State.CreateState("Dash");
	State.CreateState("Fall");
	State.CreateState("Die");

	// 함수들 세팅
	State.SetUpdateFunction("Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));
	State.SetStartFunction("Idle", [this]()
		{
			this->BodyRenderer->ChangeAnimation("Idle");
		});


	State.SetUpdateFunction("Run", std::bind(&APlayer::Run, this, std::placeholders::_1));
	State.SetStartFunction("Run", [this]()
		{
			this->BodyRenderer->ChangeAnimation("Run");
		});

	State.SetUpdateFunction("Jump", std::bind(&APlayer::Jump, this, std::placeholders::_1));
	State.SetStartFunction("Jump", [this]()
		{
			// 점프 시작할 때 JumpVector값 한번만 대입
			JumpVector = FVector::Up * 1000.0f;
			this->BodyRenderer->ChangeAnimation("Jump");
		});

	State.SetUpdateFunction("Dash", std::bind(&APlayer::Dash, this, std::placeholders::_1));
	State.SetStartFunction("Dash", [this]()
		{
			// 점프 시작할 때 JumpVector값 한번만 대입
			GravityVector = FVector::Zero;
			DashVector = PlayerDir * 1500.0f;
			this->BodyRenderer->ChangeAnimation("Jump");
		});

	State.SetUpdateFunction("Fall", std::bind(&APlayer::Fall, this, std::placeholders::_1));
	State.SetStartFunction("Fall", [this]()
		{
			this->BodyRenderer->ChangeAnimation("Jump");
		});

	State.SetUpdateFunction("Die", std::bind(&APlayer::Fall, this, std::placeholders::_1));
	State.SetStartFunction("Die", [this]()
		{
			this->BodyRenderer->ChangeAnimation("Die");
		});

	State.ChangeState("Idle");
}

void APlayer::Idle(float _DeltaTime)
{
	PlayerDirCheck();

	// 중력
	Gravity(_DeltaTime);
	ColorColCheck();
	if (BottomColor == Color8Bit::Black || BottomRightColor == Color8Bit::Black || BottomLeftColor == Color8Bit::Black)
	{
		GravityVector = FVector::Zero;
	}
	if (BottomColor == Color8Bit::Magenta || BottomRightColor == Color8Bit::Magenta || BottomLeftColor == Color8Bit::Magenta)
	{
		GravityVector = FVector::Zero;
	}
	if (BottomColor == Color8Bit::Red || BottomRightColor == Color8Bit::Red || BottomLeftColor == Color8Bit::Red)
	{
		GravityVector = FVector::Zero;
	}
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
		State.ChangeState("Run");
		return;
	}

	if (true == IsPress(VK_SPACE) || true == IsPress('W'))
	{
		State.ChangeState("Jump");
		return;
	}

	if (true == IsDown(VK_RBUTTON))
	{
		State.ChangeState("Dash");
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
		State.ChangeState("Jump");
		return;
	}

	if (true == IsFree('A') && true == IsFree('D'))
	{
		State.ChangeState("Idle");
		return;
	}

	if (true == IsDown(VK_RBUTTON))
	{
		State.ChangeState("Dash");
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
	if (0 >= JumpPower.Y)
	{
		if (BottomColor == Color8Bit::Black || BottomRightColor == Color8Bit::Black || BottomLeftColor == Color8Bit::Black)
		{
			GravityVector = FVector::Zero;
			State.ChangeState("Idle");
			return;
		}
		if (BottomColor == Color8Bit::Magenta || BottomRightColor == Color8Bit::Magenta || BottomLeftColor == Color8Bit::Magenta)
		{
			GravityVector = FVector::Zero;
			State.ChangeState("Idle");
			return;
		}
		if (BottomColor == Color8Bit::Red || BottomRightColor == Color8Bit::Red || BottomLeftColor == Color8Bit::Red)
		{
			GravityVector = FVector::Zero;
			State.ChangeState("Idle");
			return;
		}
	}

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
		State.ChangeState("Dash");
		return;
	}

}

void APlayer::Dash(float _DeltaTime)
{
	PlayerDirCheck();
	ColorColCheck();
	DashTime -= _DeltaTime;

	if (DashTime <= 0)
	{
		DashTime = 0.24f;
		DashVector = FVector::Zero;
		State.ChangeState("Fall");
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
	if (NextBottomLeftColor != Color8Bit::Black && NextBottomRightColor != Color8Bit::Black && NextTopColor != Color8Bit::Black)
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
	AddActorLocation(GravityVector * _DeltaTime);

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

	if (true == IsDown(VK_RBUTTON))
	{
		State.ChangeState("Dash");
		return;
	}

	ColorColCheck();
	if (BottomColor == Color8Bit::Black || BottomRightColor == Color8Bit::Black || BottomLeftColor == Color8Bit::Black)
	{
		GravityVector = FVector::Zero;
		State.ChangeState("Idle");
		return;
	}
	if (BottomColor == Color8Bit::Magenta || BottomRightColor == Color8Bit::Magenta || BottomLeftColor == Color8Bit::Magenta)
	{
		GravityVector = FVector::Zero;
		State.ChangeState("Idle");
		return;
	}
	if (BottomColor == Color8Bit::Red || BottomRightColor == Color8Bit::Red || BottomLeftColor == Color8Bit::Red)
	{
		GravityVector = FVector::Zero;
		State.ChangeState("Idle");
		return;
	}
}

void APlayer::Die(float _DeltaTime)
{
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

	AttackEffectRenderer->ChangeAnimation("AttackEffect");
}


void APlayer::PlayerDirCheck()
{

	PlayerDir = InGameCursorPos - PlayerPos;
	PlayerDir = PlayerDir.Normalize3DReturn();
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
