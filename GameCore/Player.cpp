#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Renderer.h>

APlayer::APlayer() 
{
	Renderer = CreateDefaultSubobject<URenderer>("Renderer");
}

APlayer::~APlayer() 
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();
	// ������ �̶� ������.


	// ���⼭ ��������ϴµ�.
}

void APlayer::Tick(float _DeltaTime)
{
	// ���� ������ �ľ��Ҷ��� �ִ�.
	Super::Tick(_DeltaTime);


}