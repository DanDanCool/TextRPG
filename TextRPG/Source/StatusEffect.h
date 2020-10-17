#pragma once

/*
 * Enumerators are a special type of integer. There are two ways to define an enumerator in
 * C++, with enum, and enum class.
 * enum class is prefered because enumerators defined with enum can be implicitly casted to an
 * integer, which is almost always a bug.
 */

enum class StatusAction
{
	None = 0,
	Health,
	Strength,
	Defense,
	Money
};

/*
 * Structs are the same thing as classes, except by default, everything is set to public. Structs
 * are typically used for simple data structures.
 * 
 * StatusEffect has three member variables, they can be freely accessed and modified because of its
 * public access modifier.
 * Size is the amount of StatusActions and Effects there are.
 * Actions is a pointer to the start of an array
 * Effects is also a pointer to the start of an array.
 * 
 * StatusEffect objects are used to modify the player.
 */

struct StatusEffect
{
	int Size;
	StatusAction* Actions;
	int* Effects;
};