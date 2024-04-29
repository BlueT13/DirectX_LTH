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
	State.CreateState("Attack");
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

	State.SetUpdateFunction("Attack", std::bind(&APlayer::Fall, this, std::placeholders::_1));
	State.SetStartFunction("Attack", [this]()
		{
			// 무기 공격 이펙트 생성

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

	GroundUp();
}

void APlayer::Run(float _DeltaTime)
{
	PlayerDirCheck();
	Gravity(_DeltaTime);
	ColorColCheck();
	if (BottomColor == Color8Bit::Black || BottomColor == Color8Bit::Magenta)
	{
		GravityVector = FVector::Zero;
	}

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

	AddActorLocation(GravityVector * _DeltaTime);

	if (true == IsPress('A'))
	{
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
	}
	if (true == IsPress('D'))
	{
		AddActorLocation(FVector::Right * _DeltaTime * Speed);
	}

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

	GroundUp();
}

void APlayer::Jump(float _DeltaTime)
{
	PlayerDirCheck();
	Gravity(_DeltaTime);
	JumpPower = JumpVector + GravityVector;

	if (true == IsPress('A'))
	{
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
	}
	if (true == IsPress('D'))
	{
		AddActorLocation(FVector::Right * _DeltaTime * Speed);
	}

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

	if (true == IsDown(VK_RBUTTON))
	{
		State.ChangeState("Dash");
		return;
	}

	AddActorLocation(JumpPower * _DeltaTime);
}

void APlayer::Dash(float _DeltaTime)
{
	PlayerDirCheck();
	DashTime -= _DeltaTime;

	if (DashTime <= 0)
	{
		DashTime = 0.24f;
		State.ChangeState("Fall");
		return;
	}

	PlayerNextPos = PlayerPos + DashVector;
	ColorColCheck();
	if (NextPosColor != Color8Bit::Black)
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

	if (true == IsPress('A'))
	{
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
	}
	if (true == IsPress('D'))
	{
		AddActorLocation(FVector::Right * _DeltaTime * Speed);
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

void APlayer::Attack(float _DeltaTime)
{
	PlayerDirCheck();

	// 충돌 구현 필요

	State.ChangeState("Idle");
}

void APlayer::Die(float _DeltaTime)
{
}


void APlayer::PlayerDirCheck()
{
	PlayerDir = InGameCursorPos - PlayerPos;
	PlayerDir = PlayerDir.Normalize3DReturn();

	if (0 > PlayerDir.X)
	{
		BodyRenderer->SetDir(EEngineDir::Left);
		HandRenderer->SetPosition({ 26,20,0 });

		RotationRenderer->SetPosition({ -32, 64, 0 });
		RotationRenderer->SetRotationDeg({ 0, 0, -15 });
		//RotationRenderer->SetRotationDeg({ 0.0f, 0.0f, PlayerDir.Z });
	}
	else
	{
		BodyRenderer->SetDir(EEngineDir::Right);
		HandRenderer->SetPosition({ -26, 20, 0 });

		RotationRenderer->SetPosition({ 32, 64, 0 });
		RotationRenderer->SetRotationDeg({ 0, 0, 15 });
		//RotationRenderer->SetRotationDeg({ 0.0f, 0.0f, PlayerDir.Z });
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
