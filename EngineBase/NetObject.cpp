#include "PreCompile.h"
#include "NetObject.h"

// �� ��ū�� �ο����ټ� �ִ°� ���� �����Դϴ�.
std::atomic<int> UNetObject::CurObjectToken = 0;
std::map<int, UNetObject*> UNetObject::AllNetObject;

UNetObject::UNetObject() 
{
}

UNetObject::~UNetObject() 
{
}


void UNetObject::Send(std::shared_ptr<UEngineProtocol> _Protocol)
{
	if (nullptr == Net)
	{
		return;
	}

	// ������Ʈ ��ū�� ������ū�� ������ ä���� �־�� �Ѵ�.
	// ä���� ������ �ϰ�.
	_Protocol->SetSessionToken(Net->GetSessionToken());
	_Protocol->ObjectToken = ObjectToken;

	Net->Send(_Protocol);
}



std::shared_ptr<UEngineProtocol> UNetObject::PopProtocol()
{
	if (true == ProtocolQueue.empty())
	{
		return nullptr;
	}

	std::shared_ptr<UEngineProtocol> Protocol = ProtocolQueue.front();
	ProtocolQueue.pop();
	return Protocol;
}