#ifndef TRANSITION_COMPONENT_H
#define TRANSITION_COMPONENT_H

class TransitionComponent
{
public:
	// Constructors
	TransitionComponent(unsigned int width, unsigned int height);
	TransitionComponent(sf::Vector2u size);
	// Destructor
	virtual ~TransitionComponent();

	// Functions
	void Update();
	void Render(sf::RenderTarget& target);

	// Getters
	inline const TransitionStatus &GetStatus() const { return m_Status; }
	inline const sf::Color &GetColor() const { return m_Color; }

private:
	sf::RectangleShape m_TransitionScreen;
	sf::Color m_Color;
	TransitionStatus m_Status;
};

#endif // !TRANSITION_COMPONENT_H

