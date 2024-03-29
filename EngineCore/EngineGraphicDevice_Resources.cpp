#include "PreCompile.h"
#include "EngineGraphicDevice.h"
#include "EngineVertex.h"
#include "EngineMesh.h"
#include "EngineTexture.h"

void UEngineGraphicDevice::EngineResourcesRelease()
{
	// 어차피 자동으로 지워지는 리소스들을 왜 굳이 여기서 클리어를 직접 해주지?
	// 엔진이 종료되는 시점에 텍스처를 모두다 삭제한다.
	UEngineSound::ResourcesRelease();
	UEngineTexture::ResourcesRelease();
	UEngineVertexBuffer::ResourcesRelease();
	UEngineIndexBuffer::ResourcesRelease();
	UEngineMesh::ResourcesRelease();
}


// 엔진에서 박스하나도 지원안해주면 
void UEngineGraphicDevice::EngineResourcesInit()
{
	{
		std::vector<FEngineVertex> VertexData;
		VertexData.resize(4);
		// 0     1
		//   중앙
		// 3     2
		// w에 1을 넣었다.

		// 이녀석가지고 그래픽카드에게 도형을 만들기 위한 점을 저장해줘.
		VertexData[0] = { {-0.5f, 0.5f, 0.0f, 1.0f} };
		VertexData[1] = { {0.5f, 0.5f, 0.0f, 1.0f} };
		VertexData[2] = { {0.5f, -0.5f, 0.0f, 1.0f} };
		VertexData[3] = { {-0.5f, -0.5f, 0.0f, 1.0f} };

		// 점은 버퍼가 아니다.
		// 사각형을 지원 안합니다. directx는 삼각형으로만 픽셀을 건져낼수 있다. 
		// 삼각형으로 그려야 면이 만들어지는데 점을 4개만 넣었다.
		std::shared_ptr<UEngineVertexBuffer> VertexBuffer = UEngineVertexBuffer::Create("Rect", VertexData);

		// 삼각형을 어떻게 그릴지에 대한 순서.
		std::vector<UINT> IndexData = {0, 1, 2, 0, 2, 3};

		std::shared_ptr<UEngineIndexBuffer> IndexBuffer = UEngineIndexBuffer::Create("Rect", IndexData);

		UEngineMesh::Create("Rect");

		// IndexBuffer
	}
}