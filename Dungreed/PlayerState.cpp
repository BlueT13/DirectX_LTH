#include "PreCompile.h"
#include "Player.h"

void APlayer::StateInit()
{
	// 스테이트 생성
	State.CreateState("Die");
	State.CreateState("Idle");
	State.CreateState("Run");
	State.CreateState("Jump");
	State.CreateState("Dash");

	// 함수들 세팅
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
			// 점프 시작할 때 JumpVector값 한번만 대입
			JumpVector = FVector::Up * 1000.0f;
			this->Renderer->ChangeAnimation("Jump");
		});

	State.ChangeState("Idle");
}

void APlayer::Idle(float _DeltaTime)
{
	PlayerDirCheck();
	Gravity();
	ColorColCheck(_DeltaTime);
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
}

void APlayer::Run(float _DeltaTime)
{
	PlayerDirCheck();
	Gravity();
	ColorColCheck(_DeltaTime);
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
	if (Color == Color8Bit::Black || Color == Color8Bit::Magenta && 0 >= JumpPower.Y)
	{
		State.ChangeState("Idle");
	}
}

void APlayer::Die(float _DeltaTime)
{
}


void APlayer::PlayerDirCheck()
{
	// CursorPos에 맞게 방향 전환 조건문으로 변경 필요

	if (0 > InGameCursorPos.X - PlayerPos.X)
	{
		Renderer->SetDir(EEngineDir::Left);
	}
	else
	{
		Renderer->SetDir(EEngineDir::Right);
	}
}

void APlayer::Gravity()
{
	GravityVector += FVector::Down;
}
