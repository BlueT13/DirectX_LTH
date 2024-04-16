#pragma once
#include <EngineCore/Actor.h>

// ���� :
class ATileMap : public AActor
{
public:
	// constrcuter destructer
	ATileMap();
	~ATileMap();

	// delete Function
	ATileMap(const ATileMap& _Other) = delete;
	ATileMap(ATileMap&& _Other) noexcept = delete;
	ATileMap& operator=(const ATileMap& _Other) = delete;
	ATileMap& operator=(ATileMap&& _Other) noexcept = delete;

	class UTileRenderer* TileRenderer = nullptr;
protected:

private:

};

