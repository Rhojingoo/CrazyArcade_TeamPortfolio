#pragma once

// ���� :
class ATestLobbyPlayer
{
public:
	// constrcuter destructer
	ATestLobbyPlayer();
	~ATestLobbyPlayer();

	// delete Function
	ATestLobbyPlayer(const ATestLobbyPlayer& _Other) = delete;
	ATestLobbyPlayer(ATestLobbyPlayer&& _Other) noexcept = delete;
	ATestLobbyPlayer& operator=(const ATestLobbyPlayer& _Other) = delete;
	ATestLobbyPlayer& operator=(ATestLobbyPlayer&& _Other) noexcept = delete;

protected:

private:

};

