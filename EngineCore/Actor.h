#pragma once
#include <vector>
#include "TickObject.h"
#include "WorldObject.h"
#include "Level.h"

// 설명 : 액터가 트랜스폼을 가지는게 아니라
class ULevel;
class UActorComponent;
class USceneComponent;
class AActor : public UTickObject, public UWorldObject
{
	friend ULevel;
	GENERATED_BODY(UTickObject)

public:
	// constrcuter destructer
	AActor();
	~AActor();

	// delete Function
	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	// 오로지 생성자에서만 호출될수 있게 만들어 놓는다.
	// 언리얼 따라할려고 그냥 함.
	template<typename ComponentType>
	std::shared_ptr<ComponentType> CreateDefaultSubobject(std::string_view _Name)
	{
		if (false == ULevel::IsActorConstructer)
		{
			MsgBoxAssert("언리얼에서는 생성자에서밖에 컴포넌트를 생성할수 없습니다.");
		}
		
		std::shared_ptr<UActorComponent> NewComponent = std::make_shared<ComponentType>();

		PushComponent(NewComponent, _Name);

		return std::dynamic_pointer_cast<ComponentType>(NewComponent);
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	// 액터가 루트 컴포넌트를 가지면 
	USceneComponent* RootComponent = nullptr;
	std::vector<std::shared_ptr<UActorComponent>> Components;

	void PushComponent(std::shared_ptr<UActorComponent> _Component, std::string_view _Name);


};

