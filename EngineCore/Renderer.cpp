#include "PreCompile.h"
#include "Renderer.h"
#include "EngineInputLayOut.h"

URenderer::URenderer() 
{
}

URenderer::~URenderer() 
{
}

void URenderer::BeginPlay()
{
	Super::BeginPlay();

	// 해줘야 한다/
	GetWorld()->PushRenderer(shared_from_this());
}

void URenderer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	int a = 0;
}

void URenderer::Render(float _DeltaTime)
{
	// 순서는 상관업습니다.

	// 여기에서 이걸 하는 이유는 딱 1개입니다.
	// 교육용으로 랜더링파이프라인의 순서에 따라 세팅해주려는 것뿐이지
	// 꼭 아래의 순서대로 세팅을 해야만 랜더링이 되는게 아니에요.
	// Mesh->Setting()
	
	// InputAssembler1
	Mesh->InputAssembler1Setting();
	LayOut->Setting();

	// VertexShader
	Material->VertexShaderSetting();

	// InputAssembler2
	Mesh->InputAssembler2Setting();

	// Rasterizer
	Material->RasterizerSetting();

	// PixelShader
	Material->PixelShaderSetting();

	// OM

	// Draw
	Mesh->IndexedDraw();
}	


void URenderer::SetMesh(std::string_view _Name)
{
	Mesh = UEngineMesh::FindRes(_Name);

	if (nullptr == Mesh)
	{
		MsgBoxAssert("존재하지 않는 매쉬를 세팅하려고 했습니다." + std::string(_Name));
		return;
	}

	if (nullptr != Material)
	{
		LayOut = UEngineInputLayOut::Create(Mesh->VertexBuffer, Material->GetVertexShader());
	}
}

void URenderer::SetMaterial(std::string_view _Name)
{
	Material = UEngineMaterial::FindRes(_Name);

	if (nullptr == Material)
	{
		MsgBoxAssert("존재하지 않는 머티리얼를 세팅하려고 했습니다." + std::string(_Name));
		return;
	}

	if (nullptr != Mesh)
	{
		LayOut = UEngineInputLayOut::Create(Mesh->VertexBuffer, Material->GetVertexShader());
	}
}