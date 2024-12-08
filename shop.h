#ifndef SHOP_H
#define SHOP_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "player.h"
using namespace std;

class Shop
{
private:
    unordered_map<string, pair<int, int> > items; // 名稱 -> <價格, 攻擊力>

public:
    Shop()
    {
        items["防具"] = make_pair(80, 0);        // 防具沒有攻擊力
        items["藥水"] = make_pair(60, 0);        // 藥水沒有攻擊力
        items["武器-眼罩"] = make_pair(100, 5);  // 短劍價格 100，攻擊力 5
        items["武器-狼牙棒"] = make_pair(200, 10); // 長劍價格 200，攻擊力 10
    }

    void displayItems()
    {
        cout << "商品名稱列表:" << endl;
        for (const auto &item : items)
        {
            cout << item.first << " - " << item.second.first << " 金幣";
            if (item.second.second > 0)
                cout << " (攻擊力：" << item.second.second << ")";
            cout << endl;
        }
    }

    bool buyItem(const string &itemName, int &playerMoney, vector<string> &inventory, Player &player)
    {
        if (items.find(itemName) != items.end())
        {
            int price = items[itemName].first;
            int damage = items[itemName].second;

            if (playerMoney >= price)
            {
                playerMoney -= price;
                inventory.push_back(itemName);

                if (damage > 0) // 如果是武器，裝備
                {
                    player.equipWeapon(itemName, damage);
                    price == 100 ? player.setweaponHealth(rand() % 15 + 1) : player.setweaponHealth(rand() % 20 + 1);
                }

                cout << "成功購買 " << itemName << "！" << endl;
                cout << "剩餘餘額：" << player.getMoney() << endl;
                return true;
            }
            else
            {
                cout << "金幣不足，無法購買 " << itemName << "。" << endl;
                return false;
            }
        }
        else
        {
            cout << "該物品不存在。" << endl;
            return false;
        }
    }
};

#endif
