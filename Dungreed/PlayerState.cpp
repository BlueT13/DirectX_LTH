#include "PreCompile.h"
#include "Player.h"

void APlayer::StateInit()
{
	// ������Ʈ ����
	State.CreateState("Idle");
	State.CreateState("Run");
	State.CreateState("Jump");
	State.CreateState("Dash");
	State.CreateState("Die");

	// �Լ��� ����
	State.SetUpdateFunction("Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));
	State.SetStartFunction("Idle", [this]()
		{
			this->Renderer->ChangeAnimation("Idle");
		});


	State.SetUpdateFunction("Run", std::bind(&APlayer::Run, this, std::placeholders::_1));
	State.SetStartFunction("Run", [this]()
		{
			this->Renderer->ChangeAnimation("Run");
		});

	State.SetUpdateFunction("Jump", std::bind(&APlayer::Jump, this, std::placeholders::_1));
	State.SetStartFunction("Jump", [this]()
		{
			// ���� ������ �� JumpVector�� �ѹ��� ����
			JumpVector = FVector::Up * 1200.0f;
			this->Renderer->ChangeAnimation("Jump");
		});

	State.ChangeState("Idle");
}

void APlayer::Idle(float _DeltaTime)
{
	PlayerDirCheck();
	Gravity();
	ColorColCheck();
	if (DownColor == Color8Bit::Black || RightColor == Color8Bit::Black || LeftColor == Color8Bit::Black)
	{
		GravityVector = FVector::Zero;
	}
	if (DownColor == Color8Bit::Magenta || RightColor == Color8Bit::Magenta || LeftColor == Color8Bit::Magenta)
	{
		GravityVector = FVector::Zero;
	}
	if (DownColor == Color8Bit::Red || RightColor == Color8Bit::Red || LeftColor == Color8Bit::Red)
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

	GroundUp();
}

void APlayer::Run(float _DeltaTime)
{
	PlayerDirCheck();
	Gravity();
	ColorColCheck();
	if (DownColor == Color8Bit::Black || DownColor == Color8Bit::Magenta)
	{
		GravityVector = FVector::Zero;
	}

	if (RightColor == Color8Bit::Red && PlayerMoveDir == EPlayerDir::Right)
	{
		GravityVector = FVector::Zero;
		AddActorLocation(FVector::Up);
	}
	if (RightColor == Color8Bit::Red && PlayerMoveDir == EPlayerDir::Left)
	{
		GravityVector = FVector::Zero;
		AddActorLocation(FVector::Down);
	}
	if (LeftColor == Color8Bit::Red && PlayerMoveDir == EPlayerDir::Left)
	{
		GravityVector = FVector::Zero;
		AddActorLocation(FVector::Up);
	}
	if (LeftColor == Color8Bit::Red && PlayerMoveDir == EPlayerDir::Right)
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

	GroundUp();
}

void APlayer::Jump(float _DeltaTime)
{
	PlayerDirCheck();
	Gravity();
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
		if (DownColor == Color8Bit::Black || RightColor == Color8Bit::Black || LeftColor == Color8Bit::Black)
		{
			GravityVector = FVector::Zero;
			State.ChangeState("Idle");
		}
		if (DownColor == Color8Bit::Magenta || RightColor == Color8Bit::Magenta || LeftColor == Color8Bit::Magenta)
		{
			GravityVector = FVector::Zero;
			State.ChangeState("Idle");
		}
		if (DownColor == Color8Bit::Red || RightColor == Color8Bit::Red || LeftColor == Color8Bit::Red)
		{
			GravityVector = FVector::Zero;
			State.ChangeState("Idle");
		}
	}

	AddActorLocation(JumpPower * _DeltaTime);
	GroundUp();
}

void APlayer::Dash(float _DeltaTime)
{
}

void APlayer::Die(float _DeltaTime)
{
}


void APlayer::PlayerDirCheck()
{
	// CursorPos�� �°� ���� ��ȯ ���ǹ����� ���� �ʿ�

	if (0 > InGameCursorPos.X - PlayerPos.X)
	{
		Renderer->SetDir(EEngineDir::Left);
	}
	else
	{
		Renderer->SetDir(EEngineDir::Right);
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

void APlayer::Gravity()
{
	GravityVector += FVector::Down * 1.5f;
}

void APlayer::GroundUp()
{

	if (BottomColor != Color8Bit::White)
	{
		AddActorLocation(FVector::Up);
	}
}
