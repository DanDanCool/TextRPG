/*
 * Game.h only provides a declaration for the class 'Game,' but all declarations have to be defined
 * somewhere. C++ has a one declaration rule, since the header file is likely to be included in
 * multiple places, it's unwise to define the class there.
 */

#include "Game.h"

#include "Enemy.h"
#include "Shop.h"

//utility functions
#include "Util.h"

//for random numbers
#include "Random.h"

//print stuff and get input from the console
#include <stdio.h>

//control how the program runs, such as pausing and starting
#include <thread>

/*
 * The following variable is a bit exotic, here's a breakdown of what it all means.
 * The variable name is ONOMATOPEIA, the square braces next to it means it is an array. Arrays have the
 * property that items in it is layed out contiguously in memory. Arrays have a fixed size, you can't
 * resize an array.
 * The 'static' keyword has multiple meanings. ONOMATOPEIA is declared in the global scope, so the static
 * keyword means that it is only visible in this translation unit/file.
 * The 'constexpr' and 'const' keyword means that the variable is constant, and cannot be changed.
 * constexpr has the additional property of the variable being evaluated at compile time, which might allow
 * the compiler to make some more optimizations.
 * 'const char*' is the type of the array. Strings in C++ are arrays of characters, they are also 'null
 * terminated.' This is so that the program knows where to stop reading the string. If this character isn't
 * present, the program will access memory that does not belong to the string, which may crash the program.
 * A 'char*' is a pointer to the first character in the string, the 'const' modifier signifies that the
 * string the pointer is pointing to may not be modified.
 */

static constexpr const char* ONOMATOPEIA[] = {
	"Oof!", "Ouch!", "Pew!", "Kablam!", "Pow!", "Eek!", "Eep!", "Blam!", "Ugh!", "Ah!", "Argh!", "Ough!"
};

/*
 * Same as above, this function is marked as static so it is only visible in this file
 * uint32_t is an unsigned 32 bit integer, the actual sizes of 'int' and 'unsigned int' is usually 32 bits,
 * but this is not guaranteed, so it's usually better to use uin32_t and int32_t than unsigned int and int,
 * also unsigned int is a bit of a hassle to type.
 */

//print periods to console every half a second, used for suspense
static void Suspense(uint32_t count, bool lineBreak = false)
{
	/*
	 * for loops are one of the loops that you will use when programming, the statement consists of three
	 * parts, the 'iterator,' the comparison statement, and the increment. The iterator is a value that
	 * increases or decreases, it is often used to access values in an array. The comparison statement is
	 * used to control how many times the for loop loops, and the increment increments the iterator.
	 */

	//the iterator is an unsigned int named 'i,' and is initialized to 0
	for (uint32_t i = 0; i < count; i++)
	{
		//first a check is done to see if the comparison value is true, if so loop, if not, skip this scope
		//this block is executed everytime this loops

		//print '.' to console
		printf(".");

		//wait for half a second
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		//if 'linebreak' is true, print a newline (start a new line)
		if (lineBreak)
			printf("\n");

		//at the end of the block, the iterator is incremented
	}

	//print newline
	printf("\n");
}

//prints a newline to console
static void SoundEffect(uint32_t count)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	for (uint32_t i = 0; i < count; i++)
	{
		/*
		 * Random::Uint32() is a static method in the Random class, it takes two parameters, which are
		 * values you give the function, and it returns an integer in that range.
		 * It is used to access a random string in the array ONOMATOPEIA, which is then printed to console.
		 */

		printf("%s\n", ONOMATOPEIA[Random::UInt32(0, 11)]);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

//constructor
Game::Game()
{
	//Random uses a Mersenne Twister internally, this is called to seed the twister
	Random::Init();

	printf("=================================\n");
	printf("           R P G   1 . 5         \n");
	printf("       B Y   M A X   L I U       \n");
	printf("   P O R T   B Y   D A N I E L   \n");
	printf("=================================\n");
}

//destructor, doesn't really do anything, might as well not exist
Game::~Game()
{
}

void Game::Run()
{
	/*
	 * While loops are another type of loop, each time it loops, it checks a boolean value, if it evaluates
	 * to true, then it runs the block of code inside. It keeps on looping until the boolean value evaluates
	 * to false.
	 */

	while (m_bRun)
	{
		//if m_bRun is true, run this code

		//handle starting inputs
		Start();

		//'meat' of the function, when it finishes executing, m_bRun is set to false
		OnUpdate();

		//ask user if they would like to continue, if so m_bRun is set to true
		End();
	}

	//loops infinitely until the user inputs 'xD'
	while (true)
	{
		printf("Type xD to quit\n");

		//string of size 2, the last character is reserved for the null termination character
		char quitt[3];

		//get the input from user, tried using scanf, didn't work for some reason
		fgets(quitt, 3, stdin);

		/*
		 * strcmp is a function in the string.h header file, it takes in two strings and returns 0 if
		 * they are equal. The '!' in front of it is the boolean operator 'not.' Since 0 is evaluated
		 * as false, the ! in front of it changes it to be true, so the check passes if the strings
		 * are equal.
		 * The return statement exits out of the loop.
		 */

		//if statements only execute the code if the comparison is true
		if (!strcmp(quitt, "xD"))
			return;
	}
}

//handles starting input
void Game::Start()
{
	printf("\nWhat is your name?\n");
	
	//Get the name from the user, allocated on the stack as it is needed outside of this function.
	char* name = new char[256];

	/*
	 * scanf is a function that gets input from the console, it takes in a formatted string and variable
	 * arguments. The % is used to get something from console and assign it to the argument, the [^\n]
	 * tells the function to keep reading until it hits a newline character (when you press enter).
	 * 255s tells the function to read until 255 characters is reached and assign it to a string. The
	 * second argument is the string, and the last argument is how many characters the function should read.
	 * 
	 * In this case the 'scanf_s' function is used, this is a function only available on Microsoft's Visual
	 * C++, however, MSVC will not compile your code if you use scanf as it is very dangerous.
	 */

	//Read 255 characters (last one is \0 or null termination character) and assign it to 'name'
	scanf_s("%[^\n]255s", name, 255);

	//set the player name to be 'name'
	m_Player.SetName(name);

	while (true)
	{
		printf("Are you ready? (y/n) ");

		//clear the input stream of any newline characters
		getchar();

		char ready;

		//read in a character from the input stream (console) and assign it to ready
		scanf_s("%c", &ready, 1);

		/*
		 * switch statements are a conditonal branch statement, like if statements.
		 * They can be used interchangeably with if else statments, but are slightly faster.
		 * 
		 */

		switch (ready)
		{
		//if ready is equal to 'y'
		case 'y':
			printf("Welcome, %s. Your journey begins now.\n", name);

			//tells the program to break out the switch statement, otherwise, the program would
			//continue with the next statement (case 'n')
			break;
			
		//if ready is equal to 'n'
		case 'n':
			printf("Okay, I'll ask again in 10 seconds.\n");
			
			//wait 10 seconds
			std::this_thread::sleep_for(std::chrono::seconds(10));

			//this statement tells the program to skip all the code below and start the next loop
			//of the while statement
			continue;

		//handles invalid input
		default:
			printf("Poor input.\n");
			continue;
		}

		//this statement tells the program to stop the loop and skip all the code below it
		//which in this case is none
		break;
	}

	Suspense(3);
}

//handles what happens when the game is over
void Game::End()
{
	printf("\n");
	printf("============================\n");
	printf("     G A M E   O V E R      \n");
	printf("============================\n");
	printf("\n");

	printf("Your final score was %d!\n", m_Score);

	Suspense(3, true);

	//ask the user if they would like to play again
	while (true)
	{
		printf("Would you like to play again? (y/n) ");
	
		//in hindsight scanf was not the best thing to use...
		getchar();
		char restart;
		scanf_s("%c", &restart, 1);
		getchar();

		switch (restart)
		{
		case 'y':
			//reset the stats
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

//meat of the Run loop
void Game::OnUpdate()
{
	while (m_bRun)
	{
		//handle any player updates
		m_Player.OnUpdate();

		//check if the player has gone into debt
		if (m_Player.GetMoney() < 0)
			m_Debt++;

		//print the player stats
		PrintPlayerVitals();
	
		//get input from the player and check if the player moved
		bool moved = OnMovement();

		if (moved && m_Player.IsAlive())
		{
			m_Score++;
			m_Step++;

			//special events happen if the player goes into sufficient debt
			OnPlayerDebt();
			
			//shops appear every 40 steps
			if (m_Step % 40 == 0)
				OnShopEncounter();
			
			//random events happen otherwise
			else
				OnRandomEncounter();
		}

		//check if the player is alive, stop looping if not
		if (!m_Player.IsAlive())
			m_bRun = false;
	}
}

//resets the stats
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

//print player stats
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

//method that handles inventory access, couldn't think of a better name
void Game::PlayerInventory()
{
	printf("--------------------------\n");
	printf("Inventory:\n");

	//print everything in the player inventory
	for (auto* item : m_Player.GetInventory())
		printf("%s\n", item->GetName());

	printf("--------------------------\n\n");

	//self explanatory... I hope
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

//returns true if a movement was made
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
		//handle inventory access
		PlayerInventory();
		return false;

	case 'd':
	case 'die':
		//if player wants to prematurely end the run
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
				//status effect system is used everywhere to interact with the player

				//StatusAction is a 'enum class,' basically a special type of integer that can't be
				//compared to integers normally
				StatusAction action = StatusAction::Health;

				//this is hard coded and not guaranteed to kill the player...
				int effect = -99999999;

				//actual status effect
				StatusEffect statusEffect;
				statusEffect.Size = 1;
				statusEffect.Actions = &action;
				statusEffect.Effects = &effect;

				//let the player handle the status effect, in this case, the player takes 99999999 damage
				m_Player.HandleStatusEffect(statusEffect);

				//bit awkard if the player doesn't die
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

//special events when the player goes into debt
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
		
		//another status effect, inflicts 666 damage on the player
		StatusAction action = StatusAction::Health;
		int effect = -666;

		StatusEffect statusEffect;
		statusEffect.Size = 1;
		statusEffect.Actions = &action;
		statusEffect.Effects = &effect;

		m_Player.HandleStatusEffect(statusEffect);
	}
}

//handles what happens when the player encounters a shop
void Game::OnShopEncounter()
{
	printf("\n");
	printf("============================\n");
	printf("      T H E   S H O P       \n");
	printf("============================\n");
	printf("\n");
	printf("----------------------------\n");

	printf("You come across a shop with three items.\n\n");

	//there is a special case when the items are special, so the prefix is used to make it more natural
	const char* prefix = "";

	if (m_Step < 160)
		prefix = "the ";

	//CreateShop creates a shop, it is then assigned to the 'shop' variable
	//In hindsight this could have been done better
	Shop shop = CreateShop(m_Step);

	//print shop items
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	printf("The first item is %s%s, and costs %d money\n", prefix, shop.HealthItem->GetName(), shop.Costs[0]);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	printf("The second item is %s%s, and costs %d money\n", prefix, shop.WeaponItem->GetName(), shop.Costs[1]);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	printf("The third item is %s%s, and costs %d money\n", prefix, shop.ArmorItem->GetName(), shop.Costs[2]);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	printf("The fourth item is the %s, and costs %d money\n", shop.ScoreItemName, shop.Costs[3]);

	//subtract money from the player if they purchase anything
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

//random encounter
void Game::OnRandomEncounter()
{
	//gets a random unsigned integer from 0 - 99, didn't know why I made it an int... oh well
	int rng = Random::UInt32(0, 99);

	if (rng < 10) //10% chance
		OnEnemyEncounter();
	else if (rng < 15) //5% chance
		OnCrateEncounter();
	else if (rng == 99) //1% chance
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
		//make a shiny enemy, this also could have been done better
		enemy = CreateShinyEnemy(m_Step);
		printf("You fight a shiny enemy named %s\n", enemy.Name);
	}
	else
	{
		//make a normal enemy, also didn't do this the best way
		enemy = CreateNormalEnemy(m_Step);
		printf("You fight an enemy named %s\n", enemy.Name);
	}

	//print a few sound effects to console
	SoundEffect(3);

	//player loses the fight
	if (enemy.Health > (m_Player.GetDamage() * 3))
	{
		printf("ANd lose\n");
		printf("You take %d damage\n", enemy.Strength);

		StatusAction action = StatusAction::Health;
		//damage must be at least 5 if the player loses, otherwise, get the damage from substracting
		//the defense from damage
		int effect = -Util::Clamp(5, m_Player.GetDefense() - enemy.Strength);

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

		//pointers are used so multiple StatusEffect objects don't have to be made, arrays can be
		//iterated over easily
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

//wizard encounter
void Game::OnWizardEncounter()
{
	printf("--------------------------\n");

	int rng = Random::UInt32(0, 21);

	//heap allocation, must be deleted
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

//crate encounter!
void Game::OnCrateEncounter()
{
	printf("--------------------------\n");
	printf("You found a crate!\n");
	printf("What's inside?\n");
	Suspense(3);

	int rng = Random::UInt32(0, 6);

	//crate food
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

	//crate money
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

	//crate lottery
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

//other encounters that didn't fit into a category
void Game::OnMiscEncounter()
{
	//pit falls
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

	//orb encounters
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

	//you found a hole in the ground
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