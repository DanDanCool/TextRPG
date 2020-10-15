#pragma once

#include "Player.h"

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

	void Reset();

	void PrintPlayerVitals();
	void PlayerInventory();

	bool OnMovement();
	void OnPlayerDebt();
	void OnShopEncounter();

	void OnRandomEncounter();
	void OnEnemyEncounter();
	void OnWizardEncounter();
	void OnCrateEncounter();
	void OnMiscEncounter();

private:
	Player m_Player;

	bool m_bRun = true;
	int m_PlayerX = 0;
	int m_PlayerY = 0;
	int m_Score = 0;
	int m_Step = 0;
	int m_Debt = 0;
};