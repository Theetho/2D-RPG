#ifndef STATISTICS_COMPONENT_H
#define STATISTICS_COMPONENT_H

class StatisticsComponent
{
public:
	// Constructor
	StatisticsComponent();
	// Destructor
	virtual ~StatisticsComponent();

	// Internal static struct
	struct HealthPoints
	{
		// Value of HP added every level
		const long _increment = 15;
		long m_CurrentHP;
		// Player gains HP every level (increment/level)
		long m_LevelHP;
		// HP gained with characteristics
		long m_StatisticsHP;
		// HP gained with stuff
		long m_EquipmentHP;

		// Constructor
		inline HealthPoints(long current_HP = 150, long level_HP = 150, long statistics_HP = 0, long equipment_HP = 0) :
		m_CurrentHP(current_HP),
		m_LevelHP(level_HP),
		m_StatisticsHP(statistics_HP),
		m_EquipmentHP(equipment_HP) {}
	};
	struct Experience
	{
		// Value of the increase of exp every level
		const float _increment = 1.405;
		int m_Level;
		long long m_Current;
		long long m_Next;

		// Constructor
		Experience(int level = 1, long long current = 0, long long next = 150) :
		m_Level(level),
		m_Current(current),
		m_Next(next) {}
	};
	struct Mana
	{
		// Works the same way as HP
		const int _increment = 50;
		long m_CurrentMana;
		long m_LevelMana;
		long m_StatisticsMana;
		long m_EquipmentMana;

		// Constructor
		inline Mana(long current_mana = 150, long level_mana = 150, long statistics_mana = 0, long equipment_mana = 0) :
		m_CurrentMana(current_mana),
		m_LevelMana(level_mana),
		m_StatisticsMana(statistics_mana),
		m_EquipmentMana(equipment_mana)
		{}
	};

	// Functions
	void AddExp(long long amount);
	void RemoveExp(long long amount);
	void AddHp(long amount);
	void RemoveHp(long amount);
	void AddMana(long amount);
	void RemoveMana(long amount);

	// Getters
	inline long long GetExpForLevel(int level) { return level > 0 ? (level <= 50 ? m_ExpPerLevel[level] : m_ExpPerLevel[50]) : m_ExpPerLevel[0]; }
	inline const long &GetCurrentHP() const { return m_HealthPoints.m_CurrentHP; }
	inline const long &GetMaxHP() const { return m_HealthPoints.m_LevelHP + m_HealthPoints.m_StatisticsHP + m_HealthPoints.m_EquipmentHP; }
	inline const long &GetCurrentMana() const { return m_Mana.m_CurrentMana; }
	inline const long &GetMaxMana() const { return m_Mana.m_LevelMana + m_Mana.m_StatisticsMana + m_Mana.m_EquipmentMana; }
	inline const int& GetLevel() const { return m_Experience.m_Level; }
	inline const long long& GetCurrentLevelExp() const { return m_Experience.m_Current; }
	inline const long long& GetNextLevelExp() const { return m_Experience.m_Next; }

	// Setter
	void SetLevel(int level);
private:
	HealthPoints m_HealthPoints;
	Experience m_Experience;
	Mana m_Mana;
	std::array<long long, 50> m_ExpPerLevel;	// Level from 0 to 50

	void InitExpPerLevel();
};

#endif // !STATISTICS_COMPONENT_H

