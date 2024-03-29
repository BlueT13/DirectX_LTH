#pragma once
#include <EngineBase/EngineMath.h>

// 3D로 그려지는 점은 위치만 가질필요가 없습니다.
// 자유
// 위치 빼고는 다 자유

// 이걸 내가 마음껏 넣으면 된다.
// 점 1개를 구성하는 요소들을 내가 마음대로 넣을수 있다.
// 그걸 directx는 알아요 몰라요?
// 점을 만들었어
// 그 점이 어디에 있어야 합니까?
// 저장장치중에 어디에 있냐?
// 그래픽카드 램에 들어가게 됩니다.
// => 그래픽카드야 나 도형만들래
//    크기
struct FEngineVertex
{
public:
	float4 POSITION;
	float4 TEXCOORD;
	float4 COLOR;
};


struct FEngineVertexColor
{
public:
	float4 POSITION;
	float4 COLOR;
};

