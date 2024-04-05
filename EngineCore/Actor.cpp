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
		if (false == Components[i]->IsActive())
		{
			continue;
		}

		Components[i]->Tick(_DeltaTime);
	}
}

void AActor::PushComponent(std::shared_ptr<UActorComponent> _Component, std::string_view _Name)
{

	_Component->SetActor(this);
	_Component->SetName(_Name);
	//_Component->BeginPlay();

	Components.push_back(_Component);

	// shared_ptr을 안전하게 다운캐스팅하는 함수
	std::shared_ptr<USceneComponent> SceneComponent = std::dynamic_pointer_cast<USceneComponent>(_Component);

	if (nullptr == RootComponent && nullptr != SceneComponent)
	{
		// std::shared_ptr을 그냥 포인터로 변경하는 함수
		RootComponent = SceneComponent.get();
	}
}


FTransform& AActor::GetActorTransform()
{
	return RootComponent->Transform;
}

FVector AActor::GetActorForwardVector()
{
	return RootComponent->Transform.GetForward();
}

FVector AActor::GetActorRightVector()
{
	return RootComponent->Transform.GetRight();
}
FVector AActor::GetActorUpVector()
{
	return RootComponent->Transform.GetUp();
}

FVector AActor::GetActorLocation()
{
	return RootComponent->Transform.GetPosition();
}

void AActor::SetActorLocation(FVector _Value)
{
	RootComponent->Transform.SetPosition(_Value);
}

void AActor::SetActorScale3D(FVector _Value)
{
	RootComponent->Transform.SetScale(_Value);
}

void AActor::AddActorLocation(FVector _Value)
{
	RootComponent->Transform.AddPosition(_Value);
}
void AActor::AddActorScale3D(FVector _Value)
{
	RootComponent->Transform.AddScale(_Value);
}