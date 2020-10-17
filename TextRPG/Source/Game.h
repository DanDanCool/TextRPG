//This preprocessor statement tells the compiler to not include this if it's already been included
//This is known as a header guard, over header guard techniques exist
#pragma once

#include "Player.h"

/*
 * The code below defines a 'class' named 'Game.' A class is a collection of functions and variables,
 * a function defined in a class is called a 'method.' An instance of a class is called an 'object.'
 * Each object's methods and variables are its own, objects do not share methods and variables.
 * 
 * *Note: There is a keyword called 'static,' variables and methods marked as static are 'shared' by
 *        objects, although technically it belongs to the class.
 * 
 * An object's methods and variables can be accessed through dot notation, or arrows notation if the 
 * object is referenced by a pointer.
 * 
 * *Note: Static methods and variables can be accessed through the same ways, but can additionally be
 *        with ClassName::Variable or ClassName::Function()
 */

/*
 * The keyword 'public' and 'private' are access modifiers, they control how the object may be used and
 * modified. By default, everything in a class is private.
 * 
 * This class is written in a 'reader oriented' style, this is more friendly for readers
 * -public functions go first
 * -private functions are second
 * -member variables are last
 * 
 * This is more of a personal style, you don't need to use it yourself.
 */

class Game
{
public:
	
	/*
	 * These statements are a special kind of method known as constructors and destructors. These are
	 * called whenever the object is created or destroyed. The constructor is called BEFORE the object
	 * is passed back to the caller, and the destructor is called BEFORE the object is destroyed.
	 * You should probably initialize any member variables in the constructor and release any memory
	 * you allocated in the destructor.
	 */

	Game();
	~Game();

	//Main loop of the program.
	void Run();

private:
	//methods called in the Run method, these were split up to make code more readable

	//called at the beginning of 'Run'
	void Start();

	//called at the end of 'Run'
	void End();

	//main-main loop
	void OnUpdate();

	//reset everything
	void Reset();

	//print player statistics
	void PrintPlayerVitals();

	//couldn't think of a better name... handles player interaction with the inventory
	void PlayerInventory();

	//handles movement input
	bool OnMovement();

	//handles what happens when the player goes into debt
	void OnPlayerDebt();

	//handles what happens when the player goes shopping
	void OnShopEncounter();

	//random encounters... self-explanatory... hopefully...
	void OnRandomEncounter();
	void OnEnemyEncounter();
	void OnWizardEncounter();
	void OnCrateEncounter();
	void OnMiscEncounter();

private:
	//player member variable
	Player m_Player;

	//controls looping behavior, bool or boolean values can only be true or false
	bool m_bRun = true;

	//player locations
	int m_PlayerX = 0;
	int m_PlayerY = 0;

	//score
	int m_Score = 0;

	//incremented every move, lots of stuff dependant on this
	int m_Step = 0;

	//player can go into debt, special events happen at certain points
	int m_Debt = 0;
};