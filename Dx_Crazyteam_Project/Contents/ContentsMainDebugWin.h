#pragma once

#include <EngineCore/EngineDebugMsgWindow.h>

class ContentsMainDebugWin : public UEngineDebugMsgWindow
{
	GENERATED_BODY(UEngineDebugMsgWindow);
public:
	// constrcuter destructer
	ContentsMainDebugWin(); // ����Ʈ ������
	~ContentsMainDebugWin(); // ����Ʈ �Ҹ���

	// delete Function
	ContentsMainDebugWin(const ContentsMainDebugWin& _Other) = delete; // ����Ʈ ���� ������
	ContentsMainDebugWin(ContentsMainDebugWin&& _Other) noexcept = delete; 
	ContentsMainDebugWin& operator=(const ContentsMainDebugWin& _Other) = delete; // ����Ʈ ���� ������
	ContentsMainDebugWin& operator=(ContentsMainDebugWin&& _Other) noexcept = delete;

protected:
	void Init() override;
	void OnGui(ULevel* Level, float _Delta) override;
private:
};

