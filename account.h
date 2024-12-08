#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class Account
{
private:
    unordered_map<string, string> users; // 帳號 -> 雜湊密碼
    const string adminUsername = "admin";
    const string adminPassword = "admin123";

    // 簡單的雜湊函數（模擬加密）
    string hashPassword(const string &password)
    {
        unsigned int hash = 0;
        for (char c : password)
        {
            hash = hash * 101 + c;
        }
        stringstream ss;
        ss << hex << setw(8) << setfill('0') << hash;
        return ss.str();
    }

    void loadUsers()
    {
        ifstream file("users.txt");
        if (file.is_open())
        {
            string username, hashedPassword;
            while (file >> username >> hashedPassword)
            {
                users[username] = hashedPassword;
            }
            file.close();
        }
    }

    void saveUsers()
    {
        ofstream file("users.txt");
        for (const auto &user : users)
        {
            file << user.first << " " << user.second << endl;
        }
        file.close();
    }

public:
    Account()
    {
        loadUsers();
    }

    ~Account()
    {
        saveUsers();
    }

    bool login(const string &username, const string &password)
    {
        string hashed = hashPassword(password);
        if (users.find(username) != users.end() && users[username] == hashed)
        {
            cout << "登入成功！歡迎，" << username << "！" << endl;
            return true;
        }
        cout << "登入失敗：帳號或密碼錯誤。" << endl;
        return false;
    }

    void resetPassword(const string &username, const string &newPassword)
    {
        users[username] = hashPassword(newPassword);
        cout << "密碼已重設成功！" << endl;
    }

    void createUser(const string &username, const string &password)
    {
        if (users.size() < 3)
        {
            if (users.find(username) != users.end())
            {
                cout << "帳號已存在，無法重複建立！" << endl;
                return;
            }
            users[username] = hashPassword(password);
            cout << "帳號建立成功！" << endl;
        }
        else
        {
            cout << "已達最大帳號數限制（3個）。" << endl;
        }
    }

    void deleteUser(const string &username)
    {
        if (users.erase(username))
        {
            cout << "帳號 " << username << " 已刪除！" << endl;
        }
        else
        {
            cout << "找不到帳號 " << username << "。" << endl;
        }
    }

    bool adminLogin(const string &password)
    {
        return password == adminPassword;
    }
};

#endif
