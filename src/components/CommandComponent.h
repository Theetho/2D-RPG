#ifndef COMMAND_COMPONENT_H
#define COMMAND_COMPONENT_H

class ChatBoxGUI;

class CommandComponent
{
public:
	CommandComponent(ChatBoxGUI& chat_box);
	~CommandComponent();

	void HandleCommand();
private:
	ChatBoxGUI &m_ChatBox;
	std::list<sf::Text> m_text;

	void InitSlashHelp();
};

#endif // !COMMAND_COMPONENT_H
