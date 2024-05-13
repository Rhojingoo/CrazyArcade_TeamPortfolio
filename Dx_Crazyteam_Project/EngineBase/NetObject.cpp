#include "PreCompile.h"
#include "NetObject.h"

// �� ��ū�� �ο����ټ� �ִ°� ���� �����Դϴ�.
std::atomic<int> UNetObject::CurObjectToken = 0;
std::map<int, UNetObject*> UNetObject::AllNetObject;
std::mutex UNetObject::ProtocolLock;
std::list<std::shared_ptr<UEngineProtocol>> UNetObject::ProtocolList;

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

void UNetObject::UpdateProtocol()
{
	for (std::shared_ptr<UEngineProtocol> Protocol : ProtocolList)
	{
		int a = 0;
	}

	ProtocolList.clear();
}
