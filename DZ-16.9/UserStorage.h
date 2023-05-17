#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include "User.h"
#include "SHA1.h"

//Контейнер заменен на обёртку для хеш-таблицы из библиотеки стандартных шаблонов (вместо вектора)
class UserStorage   //Всё для чего нужен этот контейнер - переводить имена пользователей в их ID
{                   //чтобы потом по ID обращаься к ячейкам двумерного массива для доступа к ЛС, ну и хранить список всех юзеров и добавлять их туда
public:
    UserStorage();
    ~UserStorage();
    bool IsLoginFree(const std::string& name); //возвращает логическое значение о том, что логин свободен
    void AddUser(const std::string& name, const std::string& password);   //Добавляет пользователя при регистрации, УДАЛЕНИЕ ПОКА НЕ РЕАЛИЗОВАНО
    int GetIDbyName(const std::string& name);   //Ищет пользователя по имени и возвращает его ID. Если такого юзера нет
    //То возвращает -1
    int GetUsersNumber() const;       //возвращает количество пользователей
    void PrintUserList();       //вывести на экран имена всех пользователей, ТОЛЬКО ДЛЯ ДЕБАГА
    std::shared_ptr<User> getUser(const int ID);      //выдать указатель на пользователя по его ID
    std::shared_ptr<User> getUser(const std::string& name);    //перегрузка для выдаче по имени для метода выше
    bool isPasswordCorrect(const std::string& name, const std::string& password);
    void setStatusByName(const std::string& name, const bool status);
private:
    //std::vector<User*> m_storage;
    std::unordered_map<std::string, std::shared_ptr<User> > m_storage;   //массив заменен на хеш-таблицу, в качестве ключа используется имя, значение - указатель на юзера
};
