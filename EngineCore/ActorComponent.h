#pragma once
#include "Actor.h"

// 설명 : 그냥 소유만 당하는 애들이 있고
class UActorComponent
{
public:
	// constrcuter destructer
	UActorComponent();
	~UActorComponent();

	// delete Function
	UActorComponent(const UActorComponent& _Other) = delete;
	UActorComponent(UActorComponent&& _Other) noexcept = delete;
	UActorComponent& operator=(const UActorComponent& _Other) = delete;
	UActorComponent& operator=(UActorComponent&& _Other) noexcept = delete;

protected:

private:
	AActor* Actor = nullptr;

};

