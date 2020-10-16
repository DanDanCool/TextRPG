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

	printf("\n");
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
	Random::Init();

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
		fgets(quitt, 3, stdin);

		if (!strcmp(quitt, "xD"))
			return;
	}
}

void Game::Start()
{
	printf("\nWhat is your name?\n");
	
	char* name = new char[256];
	scanf_s("%[^\n]255s", name, 255);

	m_Player.SetName(name);

	while (true)
	{
		printf("Are you ready? (y/n) ");

		getchar();
		char ready;
		scanf_s("%c", &ready, 1);

		switch (ready)
		{
		case 'y':
			printf("Welcome, %s. Your journey begins now.\n", name);
			break;
		case 'n':
			printf("Okay, I'll ask again in 10 seconds.\n");
			std::this_thread::sleep_for(std::chrono::seconds(10));
			continue;
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

	printf("Your final score was %d!\n", m_Score);

	Suspense(3, true);

	while (true)
	{
		printf("Would you like to play again? (y/n) ");
	
		getchar();
		char restart;
		scanf_s("%c", &restart, 1);
		getchar();

		switch (restart)
		{
		case 'y':
			Reset();
			break;
		case 'n':
			break;
		default:
			printf("Poor input.\n");
			continue;
		}

		break;
	}
}

void Game::OnUpdate()
{
	while (m_bRun)
	{
		m_Player.OnUpdate();

		if (m_Player.GetMoney() < 0)
			m_Debt++;

		PrintPlayerVitals();
	
		bool moved = OnMovement();

		if (moved && m_Player.IsAlive())
		{
			m_Score++;
			m_Step++;

			OnPlayerDebt();
			
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

	m_Player.Reset();

	m_bRun = true;
	m_PlayerX = 0;
	m_PlayerY = 0;
	m_Score = 0;
	m_Step = 0;
	m_Debt = 0;
}

void Game::PrintPlayerVitals()
{
	printf("\n");
	printf("Location : %d, %d\n", m_PlayerX, m_PlayerY);
	printf("Health   : %d\n", m_Player.GetHealth());
	printf("Damage   : %d\n", m_Player.GetDamage());
	printf("Defense  : %d\n", m_Player.GetDefense());
	printf("Money    : %d\n", m_Player.GetMoney());
	printf("Step     : %d\n", m_Step);
	printf("Debt     : %d\n", m_Debt);
	printf("Score    : %d\n", m_Score);
}

void Game::PlayerInventory()
{
	printf("--------------------------\n");
	printf("Inventory:\n");

	for (auto* item : m_Player.GetInventory())
		printf("%s\n", item->GetName());

	printf("--------------------------\n\n");

	while (true)
	{
		printf("\t1. Use item\n\t2. Discard Item\n\t0. Return\n");

		getchar();
		char selection;
		scanf_s("%c", &selection, 1);

		switch (selection)
		{
		case '1':
		{
			getchar();
			char itemName[128];
			scanf_s("%[^\n]127s", itemName, 127);

			m_Player.UseItem(itemName);
			break;
		}
		case '2':
		{
			getchar();
			char itemName[128];
			scanf_s("%[^\n]127s", itemName, 127);

			m_Player.PopItem(itemName);
			break;
		}
		case '0':
			break;
		default:
			printf("Poor input.\n");
			continue;
		}
		
		break;
	}
	
}

bool Game::OnMovement()
{
	printf("Which way would you like to go? (n/s/e/w)\n");

	getchar();
	char direction;
	scanf_s("%c", &direction, 1);

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

	case 'i':
		PlayerInventory();
		return false;

	case 'd':
	case 'die':
		while (true)
		{
			printf("This command will kill your player.\nAre you sure? (y/n) ");

			getchar();
			char sure;
			scanf_s("%c", &sure, 1);

			switch (sure)
			{
			case 'n':
				break;

			case 'y':
			{
				StatusAction action = StatusAction::Health;
				int effect = -99999999;

				StatusEffect statusEffect;
				statusEffect.Size = 1;
				statusEffect.Actions = &action;
				statusEffect.Effects = &effect;

				m_Player.HandleStatusEffect(statusEffect);

				printf("\n");
				printf("---------------------------------\n");
				printf("You decide to ascend to heaven...\n");
				printf("---------------------------------\n");

				Suspense(3);
				break;
			}

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
	printf("\n");
	printf("============================\n");
	printf("      T H E   S H O P       \n");
	printf("============================\n");
	printf("\n");
	printf("----------------------------\n");

	printf("You come across a shop with three items.\n\n");

	const char* prefix = "";

	if (m_Step < 160)
		prefix = "the ";

	Shop shop = CreateShop(m_Step);

	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	printf("The first item is %s%s, and costs %d money\n", prefix, shop.HealthItem->GetName(), shop.Costs[0]);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	printf("The second item is %s%s, and costs %d money\n", prefix, shop.WeaponItem->GetName(), shop.Costs[1]);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	printf("The third item is %s%s, and costs %d money\n", prefix, shop.ArmorItem->GetName(), shop.Costs[2]);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	printf("The fourth item is the %s, and costs %d money\n", shop.ScoreItemName, shop.Costs[3]);

	StatusAction action = StatusAction::Money;
	int effect = 0;

	StatusEffect statusEffect;
	statusEffect.Size = 1;
	statusEffect.Actions = &action;
	statusEffect.Effects = &effect;

	while (true)
	{
		printf("\nPress '1', '2', '3', or '4' to select an item. Press '0' to purchase none of them.\n");

		getchar();
		char selection;
		scanf_s("%c", &selection, 1);

		switch (selection)
		{
		case '1':
			printf("You purchased %s%s for %d money\n", prefix, shop.HealthItem->GetName(), shop.Costs[0]);
			m_Player.AddItem(shop.HealthItem);
			effect = -shop.Costs[0];
			break;
		case '2':
			printf("You purchased %s%s for %d money\n", prefix, shop.WeaponItem->GetName(), shop.Costs[1]);
			m_Player.AddItem(shop.WeaponItem);
			effect = -shop.Costs[1];
			break;
		case '3':
			printf("You purchased %s%s for %d money\n", prefix, shop.ArmorItem->GetName(), shop.Costs[2]);
			m_Player.AddItem(shop.ArmorItem);
			effect = -shop.Costs[2];
			break;
		case '4':
			printf("You purchased the %s for %d money\n", shop.ScoreItemName, shop.Costs[3]);
			printf("You gained some score!\n");
			m_Score += m_Step / 2 + Random::UInt32(0, 20);
			effect = -shop.Costs[3];
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

	m_Player.HandleStatusEffect(statusEffect);
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
			printf("You gain %d health.\n", enemy.Health / 10);

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

	DestroyEnemy(enemy);
	printf("--------------------------\n");
}

void Game::OnWizardEncounter()
{
	printf("--------------------------\n");

	int rng = Random::UInt32(0, 21);
	const char* name = Util::GetRandomName(6, true);

	StatusEffect statusEffect;
	statusEffect.Size = 1;

	if (rng < 10)
	{
		printf("A dark wizard named %s curses you!\n", name);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		printf("ZAP!\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		printf("You take 2 damage.\n");

		StatusAction actions = StatusAction::Health;
		int effects = -2;

		statusEffect.Actions = &actions;
		statusEffect.Effects = &effects;
	}
	else if (rng < 20)
	{
		printf("A holy wizard named %s blesses you!\n", name);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		printf("ZAP!\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		printf("You gain 2 health.\n");

		StatusAction actions = StatusAction::Health;
		int effects = 2;

		statusEffect.Actions = &actions;
		statusEffect.Effects = &effects;
	}
	else if (rng == 20)
	{
		printf("A shiny dark wizard named %s curses you!\n", name);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		printf("ZAP!\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		printf("You 5 damage.\n");

		StatusAction actions = StatusAction::Health;
		int effects = -5;

		statusEffect.Actions = &actions;
		statusEffect.Effects = &effects;
	}
	else
	{
		printf("A shiny holy wizard named %s blesses you!\n", name);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		printf("ZAP!\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		printf("You gain 5 health.\n");

		StatusAction actions = StatusAction::Health;
		int effects = 5;

		statusEffect.Actions = &actions;
		statusEffect.Effects = &effects;
	}

	delete[] name;
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
			printf("ANd lose\n");
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

		printf("--------------------------\n");
		printf("You fell\n");
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
			printf("You take one damage.\n");
		}
		else
		{
			effect = 3;

			printf("onto a blanket of beautiful flowers!\n");
			printf("You gain three health.\n");
		}

		statusEffect.Effects = &effect;
		m_Player.HandleStatusEffect(statusEffect);

		printf("--------------------------\n");
	}

	else if (Random::UInt32(0, 60) == 0)
	{
		StatusAction action = StatusAction::Health;
		int effect;

		StatusEffect statusEffect;
		statusEffect.Size = 1;
		statusEffect.Actions = &action;

		printf("--------------------------\n");
		printf("You picked up an orb\n");
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
		m_Player.HandleStatusEffect(statusEffect);

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