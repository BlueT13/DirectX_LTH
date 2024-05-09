#include "PreCompile.h"
//#include "FlameSnake.h"
//
//AFlameSnake::AFlameSnake() 
//{
//	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
//	SetRoot(DefaultComponent);
//
//	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
//	Renderer->SetupAttachment(DefaultComponent);
//
//	Collision = CreateDefaultSubObject<UCollision>("Collision");
//	Collision->SetupAttachment(DefaultComponent);
//	// Collision은 반드시 SetCollisionGroup을 해야 한다.
//	Collision->SetCollisionGroup(ECollisionOrder::Monster);
//	Collision->SetCollisionType(ECollisionType::Rect);
//}
//
//AFlameSnake::~AFlameSnake() 
//{
//}
//
//void AFlameSnake::BeginPlay()
//{
//	Super::BeginPlay();
//
//	Renderer->CreateAnimation("FlameSnakeGeneration", "FlameSnakeGeneration", 0.1f);
//	Renderer->CreateAnimation("FlameSnakeIdle", "FlameSnakeIdle", 0.1f);
//	Renderer->CreateAnimation("FlameSnakeAttack", "FlameSnakeAttack", 0.1f, false);
//
//	Renderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
//	Renderer->SetOrder(ERenderOrder::Monster);
//	Renderer->SetPivot(EPivot::BOT);
//
//	Collision->SetScale(FlameSnakeColScale);
//	Collision->SetPosition({ 0,0,0 });
//
//	ColMapTex = UDungreedConstValue::ColMap;
//	ColMapX = ColMapTex->GetScale().X * UDungreedConstValue::AutoSize;
//	ColMapY = ColMapTex->GetScale().Y * UDungreedConstValue::AutoSize;
//	ColMapHalfX = ColMapTex->GetScale().hX() * UDungreedConstValue::AutoSize;
//	ColMapHalfY = ColMapTex->GetScale().hY() * UDungreedConstValue::AutoSize;
//
//	StateInit();
//}
//
//void AFlameSnake::Tick(float _DeltaTime)
//{
//	Super::Tick(_DeltaTime);
//
//	State.Update(_DeltaTime);
//}
//
//void AFlameSnake::StateInit()
//{
//	// 스테이트 생성
//	State.CreateState("FlameSnakeGeneration");
//	State.CreateState("FlameSnakeIdle");
//	State.CreateState("FlameSnakeAttack");
//	State.CreateState("FlameSnakeDie");
//
//	// 함수들 세팅
//	State.SetUpdateFunction("FlameSnakeGeneration", std::bind(&AEnvyrok::Idle, this, std::placeholders::_1));
//	State.SetStartFunction("FlameSnakeGeneration", [this]()
//		{
//			this->Renderer->ChangeAnimation("EnvyrokIdle");
//		});
//
//	State.SetUpdateFunction("FlameSnakeIdle", std::bind(&AEnvyrok::Die, this, std::placeholders::_1));
//	State.SetStartFunction("FlameSnakeIdle", [this]()
//		{
//			this->Renderer->ChangeAnimation("EnvyrokDie");
//		});
//
//	State.SetUpdateFunction("FlameSnakeAttack", std::bind(&AEnvyrok::AirSpike_Start, this, std::placeholders::_1));
//	State.SetStartFunction("FlameSnakeAttack", [this]()
//		{
//			Renderer->SetPosition({ 0,-32,0 });
//			this->Renderer->ChangeAnimation("EnvyrokAirSpike_Start");
//		});
//	State.SetUpdateFunction("FlameSnakeDie", std::bind(&AEnvyrok::AirSpike, this, std::placeholders::_1));
//	State.SetStartFunction("FlameSnakeDie", [this]()
//		{
//			JumpVector = FVector::Up * 1200.0f;
//			CurFireTime = FireRate;
//
//			if (GetActorLocation().X < ColMapHalfX)
//			{
//				AirSpikeDir = FVector::Right;
//			}
//			else
//			{
//				AirSpikeDir = FVector::Left;
//			}
//
//			this->Renderer->ChangeAnimation("EnvyrokAirSpike");
//		});
//	State.SetUpdateFunction("EnvyrokAirSpike_End", std::bind(&AEnvyrok::AirSpike_End, this, std::placeholders::_1));
//	State.SetStartFunction("EnvyrokAirSpike_End", [this]()
//		{
//			this->Renderer->ChangeAnimation("EnvyrokAirSpike_End");
//		});
//	State.SetUpdateFunction("EnvyrokSpawnTrap", std::bind(&AEnvyrok::SpawnTrap, this, std::placeholders::_1));
//	State.SetStartFunction("EnvyrokSpawnTrap", [this]()
//		{
//			CurBlockTime = 2.0f;
//			LeftBlocks.push_back(GetWorld()->SpawnActor<AEnvyrokTrap>("EnvyrokTrap0"));
//			LeftBlocks.push_back(GetWorld()->SpawnActor<AEnvyrokTrap>("EnvyrokTrap1"));
//			LeftBlocks.push_back(GetWorld()->SpawnActor<AEnvyrokTrap>("EnvyrokTrap2"));
//			LeftBlocks.push_back(GetWorld()->SpawnActor<AEnvyrokTrap>("EnvyrokTrap3"));
//			RightBlocks.push_back(GetWorld()->SpawnActor<AEnvyrokTrap>("EnvyrokTrap4"));
//			RightBlocks.push_back(GetWorld()->SpawnActor<AEnvyrokTrap>("EnvyrokTrap5"));
//			RightBlocks.push_back(GetWorld()->SpawnActor<AEnvyrokTrap>("EnvyrokTrap6"));
//			RightBlocks.push_back(GetWorld()->SpawnActor<AEnvyrokTrap>("EnvyrokTrap7"));
//
//			LeftBlocks[0]->SetActorLocation({ ColMapHalfX - 640 , ColMapHalfY - 160, 0.0f });
//			//LeftBlocks[1]->SetActorLocation({ ColMapHalfX - 640 , ColMapHalfY - 28, 0.0f });
//			//LeftBlocks[2]->SetActorLocation({ ColMapHalfX - 640 , ColMapHalfY + 104, 0.0f });
//			//LeftBlocks[3]->SetActorLocation({ ColMapHalfX - 640 , ColMapHalfY + 236, 0.0f });
//			RightBlocks[0]->SetActorLocation({ ColMapHalfX + 640 , ColMapHalfY - 160, 0.0f });
//			RightBlocks[1]->SetActorLocation({ ColMapHalfX + 640 , ColMapHalfY - 28, 0.0f });
//			RightBlocks[2]->SetActorLocation({ ColMapHalfX + 640 , ColMapHalfY + 104, 0.0f });
//			RightBlocks[3]->SetActorLocation({ ColMapHalfX + 640 , ColMapHalfY + 236, 0.0f });
//		});
//
//	State.ChangeState("EnvyrokIdle");
//}
//
//void AFlameSnake::Generation(float _DeltaTime)
//{
//}
//
//void AFlameSnake::Idle(float _DeltaTime)
//{
//}
//
//void AFlameSnake::Attack(float _DeltaTime)
//{
//}
//
//void AFlameSnake::Die(float _DeltaTime)
//{
//}
//
