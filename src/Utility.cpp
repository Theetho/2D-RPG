#include "stdafx.h"

// File that is used to create files automatically, for an example, look a "res/data/exp_per_level.value";



#include "StatisticsComponent.h"

void CreateEXPValueFile(); // Add this line in the file where you call the function

void CreateEXPValueFile()
{
	std::ofstream file("res/data/exp_per_level.value", std::ios::out | std::ios::trunc);

	StatisticsComponent stats;

	for (unsigned i = 0; i < 50; ++i)
	{
		file << stats.GetLevel() << " " << stats.GetCurrentLevelExp() << '\n';
		stats.AddExp(stats.GetNextLevelExp() - stats.GetCurrentLevelExp());
	}
}

