#pragma once
#include <atomic>
#include "EngineProtocol.h"
#include "EngineNet.h"

// ���� :
class UNetObject
{
public:
	UNetObject();
	virtual ~UNetObject();

	// delete Function
	UNetObject(const UNetObject& _Other) = delete;
	UNetObject(UNetObject&& _Other) noexcept = delete;
	UNetObject& operator=(const UNetObject& _Other) = delete;
	UNetObject& operator=(UNetObject&& _Other) noexcept = delete;

	static int GetNewObjectToken()
	{
		return CurObjectToken++;
	}

	static bool IsNetObject(int _ObjectToken)
	{
		return AllNetObject.contains(_ObjectToken);
	}

	static UNetObject* GetNetObject(int _ObjectToken)
	{
		return AllNetObject[_ObjectToken];
	}

	template<typename ConvertType>
	static ConvertType* GetNetObject(int _ObjectToken)
	{
		if (false == AllNetObject.contains(_ObjectToken))
		{
			return nullptr;
		}

		return dynamic_cast<ConvertType*>(AllNetObject[_ObjectToken]);
	}

	// Net������Ʈ�� ��������� �� 1���� �Ǿ�� �Ѵ�.
	void SetObjectToken(int _ObjectToken)
	{
		ObjectToken = _ObjectToken;
		
		if (false == IsNetObject(_ObjectToken))
		{
			AllNetObject[_ObjectToken] = this;
		}
	}



	void InitNet(std::shared_ptr<UEngineNet> _Net)
	{
		Net = _Net;
	}

	// net�� �޾ƾ� 
	bool IsNetInit()
	{
		return Net != nullptr;
	}

	void Send(std::shared_ptr<UEngineProtocol> _Protocol);

	static void PushProtocol(std::shared_ptr<UEngineProtocol> _Protocal)
	{
		std::lock_guard<std::mutex> Lock(ProtocolLock);
		ProtocolList.push_back(_Protocal);
	}

	static void UpdateProtocol();

protected:
	static std::atomic<int> CurObjectToken;
	static std::map<int, UNetObject*> AllNetObject;
	static std::mutex ProtocolLock;
	static std::list<std::shared_ptr<UEngineProtocol>> ProtocolList;

private:
	std::shared_ptr<UEngineNet> Net = nullptr;
	// -1�̸� �ȹ������̴�.
	std::atomic<int> ObjectToken = -1;

};

