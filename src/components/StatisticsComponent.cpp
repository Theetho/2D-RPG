#include "stdafx.h"
#include "Macros.h"
#include "StatisticsComponent.h"

// Constructor
StatisticsComponent::StatisticsComponent()
{
	InitExpPerLevel();
}
// Destructor
StatisticsComponent::~StatisticsComponent()
{}

void StatisticsComponent::AddExp(long long amount)
{
	m_Experience.m_Current += amount;
	while (m_Experience.m_Current >= m_Experience.m_Next)
	{
		if (m_Experience.m_Level < 50)
		{
			m_Experience.m_Level += 1;
			m_Experience.m_Next *= m_Experience._increment;
			m_HealthPoints.m_LevelHP += m_HealthPoints._increment;
			m_HealthPoints.m_CurrentHP = GetMaxHP();
			m_Mana.m_LevelMana += m_Mana._increment;
			m_Mana.m_CurrentMana = GetMaxMana();
		}
		else // Level max
		{
			m_Experience.m_Current = m_Experience.m_Next;
			break;
		}
	}
}

void StatisticsComponent::RemoveExp(long long amount)
{
	m_Experience.m_Current -= amount;
	long long previousNext = GetExpForLevel(m_Experience.m_Level - 1);
	while (m_Experience.m_Current < previousNext)
	{
		if (m_Experience.m_Level > 1)
		{
			m_Experience.m_Level -= 1;
			m_Experience.m_Next = previousNext;
			m_HealthPoints.m_LevelHP -= m_HealthPoints._increment;
			m_HealthPoints.m_CurrentHP = GetMaxHP();
			m_Mana.m_LevelMana -= m_Mana._increment;
			m_Mana.m_CurrentMana = GetMaxMana();
			previousNext = GetExpForLevel(m_Experience.m_Level - 1);
		}
		else // Level min
		{
			if (m_Experience.m_Current < 0)
				m_Experience.m_Current = 0;
			break;
		}
	}
}

void StatisticsComponent::AddHp(long amount)
{
	m_HealthPoints.m_CurrentHP = std::min(m_HealthPoints.m_CurrentHP + amount, GetMaxHP());
}

void StatisticsComponent::RemoveHp(long amount)
{
	m_HealthPoints.m_CurrentHP = std::max(m_HealthPoints.m_CurrentHP - amount, static_cast<long>(0));
}

void StatisticsComponent::AddMana(long amount)
{
	m_Mana.m_CurrentMana = std::min(m_Mana.m_CurrentMana + amount, GetMaxMana());
}

void StatisticsComponent::RemoveMana(long amount)
{
	m_Mana.m_CurrentMana = std::max(m_Mana.m_CurrentMana - amount, static_cast<long>(0));
}

void StatisticsComponent::SetLevel(int level)
{
	if (level > 0 && level <= 50)
	{
		m_Experience.m_Level = level;
		m_Experience.m_Current = m_ExpPerLevel[level];
		m_Experience.m_Next = m_ExpPerLevel[level + 1];
		m_HealthPoints.m_LevelHP = 150 + (m_HealthPoints._increment * (level - 1));
		m_HealthPoints.m_CurrentHP = GetMaxHP();
		m_Mana.m_LevelMana = 150 + (m_Mana._increment * (level - 1));
		m_Mana.m_CurrentMana = GetMaxMana();
	}
}

void StatisticsComponent::InitExpPerLevel()
{
	std::ifstream file("res/data/exp_per_level.value");

	if (file.is_open())
	{
		int index = 0;
		long long amount = 0;
		while (file >> index >> amount)
		{
			m_ExpPerLevel[index] = amount;
		}
	}
}
