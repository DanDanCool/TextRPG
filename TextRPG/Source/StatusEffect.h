#pragma once

enum class StatusAction
{
	None = 0,
	Health,
	Strength,
	Defense,
	Money
};

struct StatusEffect
{
	int Size;
	StatusAction* Actions;
	int* Effects;
};