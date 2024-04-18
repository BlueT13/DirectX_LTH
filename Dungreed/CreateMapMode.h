#pragma once
#include "TileMapMode.h"
#include "MyMap.h"

// Ό³Έν :
class ACreateMapMode : public ATileMapMode
{
	GENERATED_BODY(ATileMapMode)

public:
	// constrcuter destructer
	ACreateMapMode();
	~ACreateMapMode();

	// delete Function
	ACreateMapMode(const ACreateMapMode& _Other) = delete;
	ACreateMapMode(ACreateMapMode&& _Other) noexcept = delete;
	ACreateMapMode& operator=(const ACreateMapMode& _Other) = delete;
	ACreateMapMode& operator=(ACreateMapMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<AMyMap> MyMap = nullptr;
};

