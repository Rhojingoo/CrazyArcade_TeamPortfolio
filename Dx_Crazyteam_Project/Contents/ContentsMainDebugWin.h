#pragma once

#include <EngineCore/EngineDebugMsgWindow.h>

class UContentsMainDebugWin : public UEngineDebugMsgWindow
{
	GENERATED_BODY(UEngineDebugMsgWindow);
public:
	// constrcuter destructer
	UContentsMainDebugWin(); // ����Ʈ ������
	~UContentsMainDebugWin(); // ����Ʈ �Ҹ���

	// delete Function
	UContentsMainDebugWin(const UContentsMainDebugWin& _Other) = delete; // ����Ʈ ���� ������
	UContentsMainDebugWin(UContentsMainDebugWin&& _Other) noexcept = delete; 
	UContentsMainDebugWin& operator=(const UContentsMainDebugWin& _Other) = delete; // ����Ʈ ���� ������
	UContentsMainDebugWin& operator=(UContentsMainDebugWin&& _Other) noexcept = delete;

	static void SetIsLevel(bool _IsLevel)
	{
		IsLevel = _IsLevel;
	}


protected:
	void Init() override;
	void OnGui(ULevel* Level, float _Delta) override;
private:

	static bool IsLevel;
};

