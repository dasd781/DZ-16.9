#include "UserStorage.h"

UserStorage::UserStorage()
{
    std::cout << "User storage " << this << " created\n";
}

UserStorage::~UserStorage()
{
    std::cout << "User storage " << this << " deleted\n";
}

bool UserStorage::IsLoginFree(const std::string& name)
{
    for (std::unordered_map<std::string, std::shared_ptr<User> >::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
    {
        if (it->first == name) return false;    
    }
    return true;
}

void UserStorage::AddUser(const std::string& name, const std::string& password)
{
    if (IsLoginFree(name))  
    {
        m_storage.insert(std::make_pair(name, std::make_shared<User>(User(name, password))));
    }
    else
    {
        std::cout << "\nAlready exists!\n";
        return;
    }
}

int UserStorage::GetIDbyName(const std::string& name)
{
    std::unordered_map<std::string, std::shared_ptr<User> >::iterator it = m_storage.find(name);
    if (it != m_storage.end()) return it->second->GetID();
    else return -1;
}

int UserStorage::GetUsersNumber() const { return m_storage.size(); }

void UserStorage::PrintUserList()
{
    for (std::unordered_map<std::string, std::shared_ptr<User> >::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
    {
        std::cout << it->first << " Online: " << it->second->GetStatus() << "\n";
    }
}

std::shared_ptr<User> UserStorage::getUser(int ID)
{
    for (std::unordered_map<std::string, std::shared_ptr<User> >::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
    {
        if (it->second->GetID() == ID) return it->second;
    }
    return nullptr;
}

std::shared_ptr<User> UserStorage::getUser(const std::string& name)
{
    std::unordered_map<std::string, std::shared_ptr<User> >::iterator it = m_storage.find(name);
    if (it != m_storage.end()) return it->second;
    else return nullptr;
}

bool UserStorage::isPasswordCorrect(const std::string& name, const std::string& password)
{
    std::unordered_map<std::string, std::shared_ptr<User> >::iterator it = m_storage.find(name);
    if (it == m_storage.end()) return false; 
    else if (it->second->isPasswordCorrect(password) == true) return true;   
    else return false;
}

void UserStorage::setStatusByName(const std::string& name, const bool status)
{
    std::unordered_map<std::string, std::shared_ptr<User> >::iterator it = m_storage.find(name);
    if (it == m_storage.end()) return;
    else it->second->SetStatus(status);
}