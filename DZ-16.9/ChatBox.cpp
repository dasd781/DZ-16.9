#include "ChatBox.h"

ChatBox::ChatBox()
{
    std::cout << "Chat box " << this << " created\n";
}

ChatBox::~ChatBox()
{
    std::cout << "Chat box " << this << " deleted\n";
}

void ChatBox::sendMsg(std::string msg)
{
    m_messages.push_back(msg);
}

void ChatBox::showChatAll() const
{
    if (m_messages.size() == 0) { std::cout << "No messages here...\n"; return; }
    for (size_t i = 0; i < m_messages.size(); ++i)
    {
        std::cout << m_messages[i] << "\n";
    }
}

void ChatBox::showChatLast() const
{
    if (m_messages.size() == 0) return;
    std::cout << m_messages[m_messages.size() - 1] << "\n";
}
