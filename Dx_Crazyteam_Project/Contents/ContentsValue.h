#pragma once

class ALobbyMainMode;
class AMainGameMode;
class UContentsValue
{
	friend ALobbyMainMode;
	friend AMainGameMode;
private:
	// ������ ����ϴ� ��ġ�Դϴ�
	static int LobbyPlayerNum;
	static std::vector<int> PlayerIDs;
private:
	UContentsValue()
	{

	}

	~UContentsValue()
	{

	}
};