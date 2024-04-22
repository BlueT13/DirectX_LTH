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
			this->Renderer->ChangeAnimation("Jump");
		});

	State.ChangeState("Idle");
}


void APlayer::Die(float _DeltaTime)
{

}

void APlayer::Idle(float _DeltaTime)
{
	if (true == IsPress('A') || true == IsPress('D') || true == IsPress('W') || true == IsPress('S'))
	{
		State.ChangeState("Run");
		return;
	}

	if (true == IsDown(VK_SPACE))
	{
		State.ChangeState("Jump");
		return;
	}
}

void APlayer::Jump(float _DeltaTime)
{
	if (true == IsPress(VK_SPACE))
	{
		JumpVector = FVector::Up * 1000.0f;
	}
	//if (true == IsPress('A'))
	//{
	//	AddActorLocation(FVector::Left * _DeltaTime * Speed);
	//}
	//if (true == IsPress('D'))
	//{
	//	AddActorLocation(FVector::Right * _DeltaTime * Speed);
	//}

	if (true == IsFree(VK_SPACE))
	{
		State.ChangeState("Idle");
		return;
	}
}

void APlayer::Run(float _DeltaTime)
{
	PlayerDirCheck();

	//if (true == Renderer->IsCurAnimationEnd())
	//{
	//}

	float Speed = 500.0f;

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

	if (true == IsFree('A') && true == IsFree('D') && true == IsFree('W') && true == IsFree('S'))
	{
		State.ChangeState("Idle");
		return;
	}
}

void APlayer::PlayerDirCheck()
{
	// CursorPos에 맞게 방향 전환 조건문으로 변경 필요
	if (true == IsPress('A'))
	{
		Renderer->SetDir(EEngineDir::Left);
	}
	if (true == IsPress('D'))
	{
		Renderer->SetDir(EEngineDir::Right);
	}
}
