#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Renderer.h>

APlayer::APlayer() 
{
	Renderer = CreateDefaultSubObject<URenderer>("Renderer");

	Renderer->SetMesh("Rect");
	Renderer->SetMaterial("2DImage");
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