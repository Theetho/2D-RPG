#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

class MovementComponent
{
public:
	// Constructors
	MovementComponent(float max_velocity, float acceleration, float deceleration);
	MovementComponent(const MovementComponent &other);
	// Destructor
	virtual ~MovementComponent();

	// Function
	void Move(const float & dt, const float dir_x, const float dir_y);
	void Update(const float & dt, sf::Sprite& sprite);

	// Operator
	MovementComponent operator=(const MovementComponent &other);

	// Getters
	inline const sf::Vector2f &GetVelocity() const { return m_Velocity; }
	inline const float & GetMaxVelocity() const { return m_MaxVelocity; }

	// Setters
	inline void SetMaxVelocity(float max_velocity) { m_MaxVelocity = max_velocity; }
	inline void SetVelocity(sf::Vector2f velocity) { m_Velocity = velocity; }
	inline void SetVelocity(float x, float y) { m_Velocity.x = x; m_Velocity.y = y; }
	inline void SetVelocityX(float x) { m_Velocity.x = x; }
	inline void SetVelocityY(float y) { m_Velocity.y = y; }

private:
	// Maximum "speed"
	float m_MaxVelocity;

	float m_Acceleration;
	float m_Deceleration;
	
	// Current "speed"
	sf::Vector2f m_Velocity;
};

#endif //!MOVEMENT_COMPONENT_H

