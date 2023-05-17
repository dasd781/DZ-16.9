#pragma once
#include <iostream>
#include <vector>
#include <string>

class ChatBox
{
public:
    ChatBox();
    ~ChatBox();
    void sendMsg(std::string msg);  
    void showChatAll() const;             
    void showChatLast() const;            
private:
    std::vector<std::string> m_messages;   
};
