#pragma once

#include "SHA1.h"

class User
{
public:
    User(const std::string& login, const std::string& password) : m_login(login)
    {
        ID = ID_count;
        ++ID_count;
        std::string password_tmp = password;        
        uint salt = static_cast<uint>(ID);
        password_tmp += std::to_string(salt);       
        m_hpassword = sha1_str(password_tmp);       
        sha1_add_salt(m_hpassword, salt);           
        m_status = false;
        std::cout << "USER constructor " << this << " called\n";
    };
    virtual ~User()
    {
        //delete[] m_hpassword;                 
        std::cout << "USER destructor " << this << " called\n";
    }  
    std::string GetName() const { return m_login; };    
    std::vector<uint> GetPassword() const { return m_hpassword; };                   
    bool isPasswordCorrect(const std::string& password) const
    {
        std::string password_tmp = password;
        uint salt = sha1_pick_salt(m_hpassword);
        password_tmp += std::to_string(salt);
        std::vector<uint> hash_to_check = sha1_str(password_tmp);         //std::vector<uint> hash_to_check = sha1_str(password);
        bool compare = two_hashes_compare(m_hpassword, hash_to_check, hash_size);
        //delete[] hash_to_check;
        return compare;
    };
    void SetPassword(const std::string& password)                    
    {
        //delete[] m_hpassword;             
        m_hpassword = sha1_str(password);
    };
    int GetID() const { return ID; };                             
    bool GetStatus() const { return m_status; };                  
    void SetStatus(bool status) { m_status = status; };     
private:
    std::string m_login;        
    //uint* m_hpassword;     
    std::vector<uint> m_hpassword;    
    static int ID_count;        
    int ID;                     
    bool m_status;              
};
