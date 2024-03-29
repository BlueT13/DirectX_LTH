#include "PreCompile.h"
#include "Actor.h"
#include "SceneComponent.h"
#include "DefaultSceneComponent.h"

AActor::AActor() 
{
	// 
}

AActor::~AActor() 
{
}

void AActor::RootCheck()
{
	if (nullptr == RootComponent)
	{
		RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>("UDefaultSceneComponent");
	}
}

void AActor::BeginPlay()
{
	Super::BeginPlay();

	for (size_t i = 0; i < Components.size(); i++)
	{
		Components[i]->SetWorld(GetWorld());
		Components[i]->BeginPlay();
	}
}

void AActor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	for (size_t i = 0; i < Components.size(); i++)
	{
		Components[i]->Tick(_DeltaTime);
	}
}

void AActor::PushComponent(std::shared_ptr<UActorComponent> _Component, std::string_view _Name)
{

	_Component->SetName(_Name);
	Components.push_back(_Component);

	// shared_ptr을 안전하게 다운캐스팅하는 함수
	std::shared_ptr<USceneComponent> SceneComponent = std::dynamic_pointer_cast<USceneComponent>(_Component);

	if (nullptr == RootComponent && nullptr != SceneComponent)
	{
		// std::shared_ptr을 그냥 포인터로 변경하는 함수
		RootComponent = SceneComponent.get();
	}
}