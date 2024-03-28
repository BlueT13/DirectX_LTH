#pragma once
#include "SceneComponent.h"

// Ό³Έν :
class URenderer : public USceneComponent
{
public:
	// constrcuter destructer
	URenderer();
	~URenderer();

	// delete Function
	URenderer(const URenderer& _Other) = delete;
	URenderer(URenderer&& _Other) noexcept = delete;
	URenderer& operator=(const URenderer& _Other) = delete;
	URenderer& operator=(URenderer&& _Other) noexcept = delete;

protected:

private:

};

