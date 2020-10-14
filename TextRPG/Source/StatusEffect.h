#pragma once

enum class StatusAction
{
	None = 0,
	Health,
	Strength,
	Defense
};

struct StatusEffect
{
	int Size;
	StatusAction* Actions;
	int* Effects;
}