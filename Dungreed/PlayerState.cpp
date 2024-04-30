#include "PreCompile.h"
#include "Player.h"

void APlayer::StateInit()
{
	// ������Ʈ ����
	State.CreateState("Idle");
	State.CreateState("Run");
	State.CreateState("Jump");
	State.CreateState("Dash");
	State.CreateState("Fall");
	State.CreateState("Die");

	// �Լ��� ����
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
			// ���� ������ �� JumpVector�� �ѹ��� ����
			JumpVector = FVector::Up * 1000.0f;
			this->BodyRenderer->ChangeAnimation("Jump");
		});

	State.SetUpdateFunction("Dash", std::bind(&APlayer::Dash, this, std::placeholders::_1));
	State.SetStartFunction("Dash", [this]()
		{
			// ���� ������ �� JumpVector�� �ѹ��� ����
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
	PlayerDirCheck(_DeltaTime);

	// �߷�
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

	// ���� ��ȭ
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
	PlayerDirCheck(_DeltaTime);

	// �߷�
	Gravity(_DeltaTime);
	ColorColCheck();
	if (BottomColor == Color8Bit::Black || BottomColor == Color8Bit::Magenta)
	{
		GravityVector = FVector::Zero;
	}
	AddActorLocation(GravityVector * _DeltaTime);

	// ��� �̵�
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

	// �̵�
	if (true == IsPress('A') && LeftColor != Color8Bit::Black)
	{
		AddActorLocation(FVector::Left * Speed * _DeltaTime);
	}
	if (true == IsPress('D') && RightColor != Color8Bit::Black)
	{
		AddActorLocation(FVector::Right * Speed * _DeltaTime);
	}
	GroundUp();

	// ���� ��ȭ
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
	PlayerDirCheck(_DeltaTime);

	// �߷�
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


	// ���߿��� �̵�
	if (true == IsPress('A') && LeftColor != Color8Bit::Black)
	{
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
	}
	if (true == IsPress('D') && RightColor != Color8Bit::Black)
	{
		AddActorLocation(FVector::Right * _DeltaTime * Speed);
	}

	// ���� ��ȭ
	if (true == IsDown(VK_RBUTTON))
	{
		State.ChangeState("Dash");
		return;
	}

}

void APlayer::Dash(float _DeltaTime)
{
	ColorColCheck();
	DashTime -= _DeltaTime;

	if (DashTime <= 0)
	{
		DashTime = 0.24f;
		DashVector = FVector::Zero;
		State.ChangeState("Fall");
		return;
	}

	// PlayerNextPos ���
	PlayerPos = GetActorLocation();
	PlayerNextPos = PlayerPos + (DashVector * _DeltaTime);
	PlayerNextPos.Y = ColMapY - PlayerPos.Y;
	PlayerNextPos /= UDungreedConstValue::AutoSize;

	// ���� �ƴϸ� �̵�
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
	PlayerDirCheck(_DeltaTime);
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

}


void APlayer::PlayerDirCheck(float _DeltaTime)
{

	PlayerDir = InGameCursorPos - RotationComponent->GetWorldPosition();
	PlayerDir = PlayerDir.Normalize3DReturn();
	float Rot = PlayerDir.RightVectorToAngle2DDeg();

	if (0 > PlayerDir.X)
	{
		DefaultComponent->SetScale({-1.0f, 1.0f, 1.0f});
		
		HandRenderer->SetPosition({ 26,20,0 });
		
		RotationComponent->SetPosition({ -20, 40, 0 });
		RotationComponent->SetRotationDeg({ 0.0f, 0.0f, -Rot });
		
		WeaponRenderer->SetPosition({ 0.0f, -30.0f, 0.0f });
		WeaponRenderer->SetRotationDeg({ 0, 0, -15 });

		// BodyRenderer->SetDir(EEngineDir::Left);

		//WeaponRenderer->SetPosition({ -32, 0, 0 });
	}
	else
	{
		DefaultComponent->SetScale({ 1.0f, 1.0f, 1.0f });
		
		HandRenderer->SetPosition({ -26, 20, 0 });
		
		RotationComponent->SetPosition({ 20, 40, 0 });
		RotationComponent->SetRotationDeg({ 0.0f, 0.0f, Rot });
		
		WeaponRenderer->SetPosition({ 0.0f, 30.0f, 0.0f });
		WeaponRenderer->SetRotationDeg({ 0, 0, 15 });		

		//RotationComponent->SetPosition({16,64,0 });
		// BodyRenderer->SetDir(EEngineDir::Right);

		// WeaponRenderer->SetPosition({ 32, 50, 0 });
		// RotationComponent->SetRotationDeg({ 0.0f, 0.0f, Rot });
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
