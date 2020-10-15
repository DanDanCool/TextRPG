#include "Game.h"

#include "Enemy.h"
#include "Shop.h"

#include "Util.h"
#include "Random.h"

#include <stdio.h>
#include <thread>

static constexpr const char* ONOMATOPEIA[] = {
	"Oof!", "Ouch!", "Pew!", "Kablam!", "Pow!", "Eek!", "Eep!", "Blam!", "Ugh!", "Ah!", "Argh!", "Ough!"
};


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

static void SoundEffect(uint32_t count)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	for (uint32_t i = 0; i < count; i++)
	{
		printf("%s\n", ONOMATOPEIA[Random::UInt32(0, 11)]);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
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
			m_Score++;
			m_Step++;

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
	if (m_Debt == 75)
	{
		printf("--------------------------\n");
		printf("Daniel the Evil Banker: I have noticed you have missed your payments, please make your payments soon\n");
		printf("--------------------------\n");
		PrintPlayerVitals();
	}
	else if (m_Debt == 80)
	{
		printf("--------------------------\n");
		printf("Daniel the Evil Banker: I have noticed your debts are growing dangerously large. Please pay them soon.\n");
		printf("--------------------------\n");
		PrintPlayerVitals();
	}
	else if (m_Debt == 85)
	{
		printf("--------------------------\n");
		printf("Daniel the Evil Banker: I will be cancelling your credit card soon. Pay up!\n");
		printf("--------------------------\n");
		PrintPlayerVitals();
	}
	else if (m_Debt == 90)
	{
		printf("--------------------------\n");
		printf("Daniel the Evil Banker: I'm taking your house, a nomad like you isn't using it anyway.\n");
		printf("--------------------------\n");
		PrintPlayerVitals();
	}
	else if (m_Debt == 95)
	{
		printf("--------------------------\n");
		printf("Daniel the Evil Banker: I'm extracting the iron from your blood to sell it on the market.\n");
		printf("--------------------------\n");
		PrintPlayerVitals();
	}
	else if (m_Debt == 100)
	{
		printf("--------------------------\n");
		printf("Daniel the Evil Banker: I'm using your life insurance to pay for your debt.\n");
		printf("You take %d damage.\n", 666);
		printf("--------------------------\n");
		
		StatusAction action = StatusAction::Health;
		int effect = -666;

		StatusEffect statusEffect;
		statusEffect.Size = 1;
		statusEffect.Actions = &action;
		statusEffect.Effects = &effect;

		m_Player.HandleStatusEffect(statusEffect);
	}
}

void Game::OnShopEncounter()
{
	Shop shop = CreateShop(m_Step);

	const char* prefix = "";

	if (m_Step < 160)
		prefix = "a ";

	printf("\n");
	printf("============================\n");
	printf("      T H E   S H O P       \n");
	printf("============================\n");
	printf("\n");
	printf("----------------------------\n");

	printf("You come across a shop with three items.\n\n");
	
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	printf("The first item is %s%s, and costs %d money\n", prefix, *(shop.Items)->GetName(), *(shop.Costs));
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	printf("The second item is %s%s, and costs %d money\n", prefix, *(shop.Items + 1)->GetName(), *(shop.Costs + 1));
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	printf("The third item is %s%s, and costs %d money\n", prefix, *(shop.Items + 2)->GetName(), *(shop.Costs + 2));
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	printf("The fourth item is the %s, and costs %d money\n", shop.ScoreItemName, *(shop.Costs + 3));

	while (true)
	{
		printf("\nPress '1', '2', or '3' to select an item. Press '0' to purchase none of them.\n");

		char selection;
		scanf_s("%c", &selection);

		switch (selection)
		{
		case '1':
			printf("You purchased %s%s for %d money\n", prefix, *(shop.Items)->GetName(), *(shop.Costs));
			m_Player.AddItem(*(shop.Items));
			break;
		case '2':
			printf("You purchased %s%s for %d money\n", prefix, *(shop.Items + 1)->GetName(), *(shop.Costs + 1));
			m_Player.AddItem(shop.Items + 1);
			break;
		case '3':
			printf("You purchased %s%s for %d money\n", prefix, *(shop.Items + 2)->GetName(), *(shop.Costs + 2));
			m_Player.AddItem(shop.Items + 2);
			break;
		case '4':
			printf("You purchased the %s for %d money\n", shop.ScoreItemName, *(shop.Costs + 3));
			printf("You gained some score!\n");
			m_Score += m_Step / 2 + Random::UInt32(0, 20);
			break;
		case '0':
			printf("You don't purchase anything.\n");
			break;
		default:
			printf("Poor input.\n");
			continue;
		}

		break;
	}
}

void Game::OnRandomEncounter()
{
	int rng = Random::UInt32(0, 99);

	if (rng < 10)
		OnEnemyEncounter();
	else if (rng < 15)
		OnCrateEncounter();
	else if (rng == 99)
		OnWizardEncounter();
	else
		OnMiscEncounter();
}

void Game::OnEnemyEncounter()
{
	printf("--------------------------\n");

	Enemy enemy;

	if (Random::UInt32(0, 10) == 0)
	{
		enemy = CreateShinyEnemy(m_Step);
		printf("You fight a shiny enemy named %s\n", enemy.Name);
	}
	else
	{
		enemy = CreateNormalEnemy(m_Step);
		printf("You fight an enemy named %s\n", enemy.Name);
	}

	SoundEffect(3);

	if (enemy.Health > (m_Player.GetDamage() * 3))
	{
		printf("ANd lose\n");
		printf("You take %d damage\n", enemy.Strength);

		StatusAction action = StatusAction::Health;
		int effect = -enemy.Strength;

		StatusEffect statusEffect;
		statusEffect.Size = 1;
		statusEffect.Actions = &action;
		statusEffect.Effects = &effect;

		m_Player.HandleStatusEffect(statusEffect);
	}
	else
	{
		printf("ANd win\n");
		printf("You gain %d money.\n", enemy.Money);

		m_Score += enemy.Health / 5;

		StatusEffect statusEffect;
		StatusAction* statusActions;
		int* statusEffects;

		if (Random::UInt32(0, 3) == 0)
		{
			printf("You eat the carcass.\n");
			printf("You gain %d health.\n");

			StatusAction actions[] = {
				StatusAction::Money, StatusAction::Health
			};

			int effects[] = {
				enemy.Money, enemy.Health / 10
			};

			statusEffect.Size = 2;
			statusActions = actions;
			statusEffects = effects;
		}
		else
		{
			StatusAction actions = StatusAction::Money;
			int effects = enemy.Money;

			statusEffect.Size = 1;
			statusActions = &actions;
			statusEffects = &effects;
		}

		statusEffect.Actions = statusActions;
		statusEffect.Effects = statusEffects;

		m_Player.HandleStatusEffect(statusEffect);
	}

	printf("--------------------------\n");
}

void Game::OnWizardEncounter()
{
	printf("--------------------------\n");

	int rng = Random::UInt32(0, 21);

	StatusEffect statusEffect;
	statusEffect.Size = 1;

	if (rng < 10)
	{
		printf("A dark wizard named %s curses you!\n", Util::GetRandomName(6, true));
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		printf("ZAP!\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		printf("You take 2 damage.");

		StatusAction actions = StatusAction::Health;
		int effects = -2;

		statusEffect.Actions = &actions;
		statusEffect.Effects = &effects;
	}
	else if (rng < 20)
	{
		printf("A holy wizard named %s blesses you!\n", Util::GetRandomName(6, true));
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		printf("ZAP!\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		printf("You gain 2 health.");

		StatusAction actions = StatusAction::Health;
		int effects = 2;

		statusEffect.Actions = &actions;
		statusEffect.Effects = &effects;
	}
	else if (rng == 20)
	{
		printf("A shiny dark wizard named %s curses you!\n", Util::GetRandomName(6, true));
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		printf("ZAP!\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		printf("You 5 damage.");

		StatusAction actions = StatusAction::Health;
		int effects = -5;

		statusEffect.Actions = &actions;
		statusEffect.Effects = &effects;
	}
	else
	{
		printf("A shiny holy wizard named %s blesses you!\n", Util::GetRandomName(6, true));
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		printf("ZAP!\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		printf("You gain 5 health.");

		StatusAction actions = StatusAction::Health;
		int effects = 5;

		statusEffect.Actions = &actions;
		statusEffect.Effects = &effects;
	}

	m_Player.HandleStatusEffect(statusEffect);
}

void Game::OnCrateEncounter()
{
	printf("--------------------------\n");
	printf("You found a crate!\n");
	printf("What's inside?\n");
	Suspense(3);

	int rng = Random::UInt32(0, 6);

	if (rng == 3)
	{
		printf("You found dim sum.\n");
		printf("You gained one health.\n");
		
		StatusAction action = StatusAction::Health;
		int effect = 1;

		StatusEffect statusEffect;
		statusEffect.Size = 1;
		statusEffect.Actions = &action;
		statusEffect.Effects = &effect;

		m_Player.HandleStatusEffect(statusEffect);
	}

	else if (rng < 3)
	{
		StatusAction action = StatusAction::Money;
		int effect = m_Step / 5 + Random::UInt32(4, 8);

		printf("You found some cash.\n");
		printf("You gained %d money.\n", effect);

		StatusEffect statusEffect;
		statusEffect.Size = 1;
		statusEffect.Actions = &action;
		statusEffect.Effects = &effect;

		m_Player.HandleStatusEffect(statusEffect);
	}

	else if (rng == 4)
	{
		printf("You found a lottery ticket.\n");
		printf("You decide to enter.\n");
		Suspense(3);
		if (Random::UInt32(0, 100) == 0)
		{
			StatusAction actions[] = {
				StatusAction::Money, StatusAction::Health
			};

			int effects[] = {
				m_Step + 500, 50
			};

			StatusEffect statusEffect;
			statusEffect.Size = 2;
			statusEffect.Actions = actions;
			statusEffect.Effects = effects;

			printf("ANd win\n");
			printf("You gain %d money.\n", effects[0]);
			printf("You gain fifty health from a holy blessing.\n");
			printf("You gain a hundred score from fame due to winning the crate lottery!\n");
			printf("Seriously, go buy a lottery ticket.\n");

			m_Score += 100;
			m_Player.HandleStatusEffect(statusEffect);
		}

		else
		{
			printf("ANd lose");
		}
	}

	else
	{
		printf("There's nothing in the crate.\n");
	}

	printf("--------------------------\n");
}

void Game::OnMiscEncounter()
{
	if (Random::UInt32(0, 20) == 0)
	{
		StatusAction action = StatusAction::Health;
		int effect;

		StatusEffect statusEffect;
		statusEffect.Size = 1;
		statusEffect.Actions = &action;

		printf("--------------------------");
		printf("You fell");
		Suspense(3);

		if (Random::UInt32(0, 2) == 0)
		{
			effect = -3;

			printf("into a pit of brutally sharp spikes.\n");
			printf(" You take three damage.\n");
		}
		else if (Random::UInt32(0, 1) == 0)
		{
			effect = -1;

			printf("onto the ground.\n");
			printf(" You take one damage.\n");
		}
		else
		{
			effect += 3;

			printf("onto a blanket of beautiful flowers!\n");
			printf(" You gain three health.\n");
		}

		statusEffect.Effects = &effect;
		m_Player.HandleStatusEffect(StatusEffect);

		printf("--------------------------\n");
	}

	else if (Random::UInt32(0, 60) == 0)
	{
		StatusAction action = StatusAction::Health;
		int effect;

		StatusEffect statusEffect;
		statusEffect.Size = 1;
		statusEffect.Actions = &action;

		printf("--------------------------");
		printf("You picked up an orb");
		Suspense(3);

		if (Random::UInt32(0, 1) == 0)
		{
			effect = 1;

			printf("It's a holy orb.\n");
			printf("You gain one health.\n");
		}
		else
		{
			effect = -1;

			printf("It's a dark orb.\n");
			printf("You take one damage.\n");
		}
		if (Random::UInt32(0, 90) == 0)
		{
			printf("You picked up a greater orb\n");
			Suspense(3);

			if (Random::UInt32(0, 1) == 0)
			{
				effect = 2;

				printf("It's a greater holy orb.\n");
				printf("You gain two health.\n");
			}
			else
			{
				effect = -2;

				printf("It's a greater dark orb.\n");
				printf("You take two damage.\n");
			}
		}

		statusEffect.Effects = &effect;
		m_Player.HandleStatusEffect(StatusEffect);

		printf("--------------------------\n");
	}

	else if (Random::UInt32(0, 120) == 0)
	{
		printf("--------------------------\n");
		printf("There's a hole in the ground\n");
		printf("What's at the bottom?\n");
		Suspense(3);

		if (Random::UInt32(0, 1) == 0)
		{
			StatusAction action = StatusAction::Money;
			int effect = m_Step / 4 + Random::UInt32(25, 50);

			StatusEffect statusEffect;
			statusEffect.Size = 1;
			statusEffect.Actions = &action;
			statusEffect.Effects = &effect;

			m_Player.HandleStatusEffect(statusEffect);

			printf("It's buried treasure!\n");
			printf("You gain %d cash.\n", effect);
		}
		else
		{
			OnCrateEncounter();
		}
	}
}