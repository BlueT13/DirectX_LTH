#include "PreCompile.h"
#include "Level.h"
#include "GameMode.h"
#include "Renderer.h"
#include "Camera.h"
#include "EngineCore.h"
#include "EngineRenderTarget.h"

bool ULevel::IsActorConstructer = true;

ULevel::ULevel() 
{
	// MainCamera = std::make_shared<UCamera>();

	MainCamera = SpawnActor<UCamera>("MainCamera");
	UICamera = SpawnActor<UCamera>("NewActor");
}

ULevel::~ULevel() 
{
}

void ULevel::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	for (std::pair<const int, std::list<std::shared_ptr<AActor>>>& TickGroup : Actors)
	{
		std::list<std::shared_ptr<AActor>>& GroupActors = TickGroup.second;

		for (std::shared_ptr<AActor> Actor : GroupActors)
		{
			Actor->Tick(_DeltaTime);
		}
	}
}

void ULevel::Render(float _DeltaTime)
{
	D3D11_VIEWPORT View;

	// ViewPort.ViewPort(1280.0f, 720.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	View.Width = 1280.0f;
	View.Height = 720.0f;
	View.TopLeftX = 0;
	View.TopLeftY = 0;
	View.MinDepth = 0;
	View.MaxDepth = 1;

	GEngine->GetDirectXContext()->RSSetViewports(1, &View);

	// 어느 그림에다가 출력할거냐?
	// 여기에 출력해라.
	GEngine->GetEngineDevice().BackBufferRenderTarget->Setting();
	
	MainCamera->CameraTransformUpdate();

	for (std::pair<const int, std::list<std::shared_ptr<URenderer>>>& RenderGroup : Renderers)
	{
		std::list<std::shared_ptr<URenderer>>& GroupRenderers = RenderGroup.second;

		for (std::shared_ptr<URenderer> Renderer : GroupRenderers)
		{
			Renderer->RenderingTransformUpdate(MainCamera);
			Renderer->Render(_DeltaTime);
		}
	}
}

void ULevel::PushActor(std::shared_ptr<AActor> _Actor)
{
	if (nullptr == _Actor)
	{
		MsgBoxAssert("만들지 않은 액터를 추가하려고 했습니다.");
		return;
	}
	
	_Actor->SetWorld(this);
	_Actor->BeginPlay();

	Actors[_Actor->GetOrder()].push_back(_Actor);
}



void ULevel::PushRenderer(std::shared_ptr<URenderer> _Renderer)
{
	Renderers[_Renderer->GetOrder()].push_front(_Renderer);
}