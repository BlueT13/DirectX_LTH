#include "PreCompile.h"
#include "Player.h"

void APlayer::StateInit()
{
	// ������Ʈ ����
	State.CreateState("Die");
	State.CreateState("Idle");
	State.CreateState("Run");
	State.CreateState("Jump");
	State.CreateState("Dash");

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
			JumpVector = FVector::Up * 1000.0f;
			this->Renderer->ChangeAnimation("Jump");
		});

	State.ChangeState("Idle");
}


void APlayer::Die(float _DeltaTime)
{

}

void APlayer::Idle(float _DeltaTime)
{
	ColorColCheck(_DeltaTime);
	if (Color == Color8Bit::Black)
	{
		AddActorLocation(FVector::Up);
		GravityVector = FVector::Zero;
	}

	if (true == IsPress('A') || true == IsPress('D') || true == IsPress('W') || true == IsPress('S'))
	{
		State.ChangeState("Run");
		return;
	}

	if (true == IsPress(VK_SPACE))
	{
		State.ChangeState("Jump");
		return;
	}
}

void APlayer::Jump(float _DeltaTime)
{
	PlayerDirCheck();
	Gravity();
	JumpPower = JumpVector + GravityVector;
	AddActorLocation(JumpPower * _DeltaTime);

	if (true == IsPress('A'))
	{
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
	}
	if (true == IsPress('D'))
	{
		AddActorLocation(FVector::Right * _DeltaTime * Speed);
	}

	ColorColCheck(_DeltaTime);
	if (Color == Color8Bit::Black)
	{
		AddActorLocation(FVector::Up);
		GravityVector = FVector::Zero;
		State.ChangeState("Idle");
	}
}

void APlayer::Run(float _DeltaTime)
{
	PlayerDirCheck();

	if (true == IsPress('A'))
	{
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
	}
	if (true == IsPress('D'))
	{
		AddActorLocation(FVector::Right * _DeltaTime * Speed);
	}
	if (true == IsPress('W'))
	{
		AddActorLocation(FVector::Up * _DeltaTime * Speed);
	}
	if (true == IsDown(VK_SPACE))
	{
		State.ChangeState("Jump");
		return;
	}

	if (true == IsFree('A') && true == IsFree('D') && true == IsFree('W') && true == IsFree('S'))
	{
		State.ChangeState("Idle");
		return;
	}
}

void APlayer::PlayerDirCheck()
{
	// CursorPos�� �°� ���� ��ȯ ���ǹ����� ���� �ʿ�
	if (true == IsPress('A'))
	{
		Renderer->SetDir(EEngineDir::Left);
	}
	if (true == IsPress('D'))
	{
		Renderer->SetDir(EEngineDir::Right);
	}
}

void APlayer::Gravity()
{
	GravityVector += FVector::Down;
}
