#pragma once
#include <vector>
#include "TickObject.h"

// 설명 : 액터가 트랜스폼을 가지는게 아니라
class ULevel;
class USceneComponent;
class AActor : public UTickObject
{
	friend ULevel;

public:
	// constrcuter destructer
	AActor();
	~AActor();

	// delete Function
	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

protected:
	void Tick(float _DeltaTime);

private:
	// 액터가 루트 컴포넌트를 가지면 
	USceneComponent* RootComponent = nullptr;
	// std::vector<UActorComponent*> Components;
};

