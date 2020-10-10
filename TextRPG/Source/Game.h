#pragma once

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	void Start();
	void End();
	void OnUpdate();

private:
	bool m_bRun = true;
	int m_PlayerX = 0;
	int m_PlayerY = 0;
	int m_Score = 0;
	int m_Step = 0;
	int m_Debt = 0;
};