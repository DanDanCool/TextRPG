#include "Game.h"

#include <stdio.h>
#include <thread>

static void Suspense(uint32_t count, bool lineBreak = false)
{
	for (uint32_t i = 0; i < count; i++)
	{
		printf(".");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		if (lineBreak)
			printf("\n");
	}
}

Game::Game()
{
	printf("=================================\n");
	printf("           R P G   1 . 5         \n");
	printf("       B Y   M A X   L I U       \n");
	printf("   P O R T   B Y   D A N I E L   \n");
	printf("=================================\n");
}

Game::~Game()
{
}

void Game::Run()
{
	while (m_bRun)
	{
		Start();
		OnUpdate();
		End();
	}

	while (true)
	{
		printf("Type xD to quit\n");

		char quitt[3];
		scanf_s("%s", quitt, sizeof(quitt) - 1);

		if (!strcmp(quitt, "xD"))
			return;
	}
}

void Game::Start()
{
	printf("\nWhat is your name?\n");
	
	char name[256];
	scanf_s("%255s", name, sizeof(name) - 1);

	m_Player.SetName(name);

	while (true)
	{
		printf("Are you ready? (y/n) ");

		char ready;
		scanf_s("%c", &ready);

		switch (ready)
		{
		case 'y':
			printf("Welcome, %s. Your journey begins now.\n");
			break;
		case 'n':
			printf("Okay, I'll ask again in 10 seconds.\n");
			std::this_thread::sleep_for(std::chrono::seconds(10));
			break;
		default:
			printf("Poor input.\n");
			continue;
		}

		break;
	}

	Suspense(3);
}

void Game::End()
{
	printf("\n");
	printf("============================\n");
	printf("     G A M E   O V E R      \n");
	printf("============================\n");
	printf("\n");

	printf("Your final score was %d!", m_Score);

	Suspense(3, true);

	while (true)
	{
		printf("Would you like to play again? (y/n) ");
	
		char restart;
		scanf_s("%c", &restart);

		switch (restart)
		{
		case 'y':
			Reset();
			break;
		case 'n':
			break;
		default:
			printf("Poor input.");
			continue;
		}

		break;
	}
}

void Game::OnUpdate()
{
	while (m_bRun)
	{
		if (m_Player.GetMoney() < 0)
			m_Debt++;

		PrintPlayerVitals();
	
		bool moved = OnMovement();

		if (moved)
		{
			OnPlayerDebt();
			
			if (m_Player.IsAlive())
				if (m_Step % 40 == 0)
					OnShopEncounter();
				else
					OnRandomEncounter();
		}

		if (!m_Player.IsAlive())
			m_bRun = false;
	}
}

void Game::Reset()
{
	printf("\n");
	printf("============================\n");
	printf("G A M E  R E S T A R T I N G\n");
	printf("============================\n");

	Suspense(5, true);

	m_bRun = true;
	m_PlayerX = 0;
	m_PlayerY = 0;
	m_Score = 0;
	m_Step = 0;
	m_Debt = 0;
}

void Game::PrintPlayerVitals()
{
	printf("Location : %d, %d\n", m_PlayerX, m_PlayerY);
	printf("Health   : %d\n", m_Player.GetHealth());
	printf("Score    : %d\n", m_Score);
	printf("Money    : %d\n", m_Player.GetMoney());
	printf("Step     : %d\n", m_Step);
	printf("Debt     : %d\n", m_Debt);
}

bool Game::OnMovement()
{
	printf("Which way would you like to go? (n/s/e/w)");

	char direction;
	scanf_s("%c", &direction);

	switch (direction)
	{
	case 'n':
		m_PlayerY++;
		return true;

	case 's':
		m_PlayerY--;
		return true;

	case 'e':
		m_PlayerX++;
		return true;

	case 'w':
		m_PlayerX--;
		return true;

	case 'd':
	case 'die':
		while (true)
		{
			printf("This command will kill your player.\nAre you sure? (y/n) ");
			char sure;
			scanf("%c", &sure);

			switch (sure)
			{
			case 'n':
				break;

			case 'y':
				printf("\n");
				printf("---------------------------------\n");
				printf("You decide to ascend to heaven...\n");
				printf("---------------------------------\n");

				Suspense(3);
				break;

			default:
				printf("Poor input.\n");
				continue;
			}

			break;
		}

		return false;

	default:
		printf("Poor input.\n");
		return false;
	}
}

void Game::OnPlayerDebt()
{
}

void Game::OnShopEncounter()
{
}

void Game::OnRandomEncounter()
{
}
