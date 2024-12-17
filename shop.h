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
    vector<pair<string, pair<int, int> > > items; // <名稱, <價格, 攻擊力>>

public:
    Shop()
    {
        items.push_back(make_pair("防具", make_pair(80, 0)));
        items.push_back(make_pair("藥水", make_pair(60, 0)));
        items.push_back(make_pair("武器-眼罩", make_pair(100, 5)));
        items.push_back(make_pair("武器-狼牙棒", make_pair(200, 10)));
    }

    void displayItems()
    {
        cout << "==== 商店商品列表 ====" << endl;
        for (size_t i = 0; i < items.size(); i++)
        {
            cout << i + 1 << ". " << items[i].first
                 << " - " << items[i].second.first << " 金幣";
            if (items[i].second.second > 0)
                cout << " (攻擊力：" << items[i].second.second << ")";
            cout << endl;
        }
    }

    bool buyItem(int itemIndex, int &playerMoney, vector<string> &inventory, Player &player)
    {
        if (itemIndex >= 1 && itemIndex <= items.size())
        {
            auto item = items[itemIndex - 1];
            int price = item.second.first;
            int damage = item.second.second;

            if (playerMoney >= price)
            {
                playerMoney -= price;
                inventory.push_back(item.first);

                if (damage > 0) // 如果是武器，裝備
                {
                    player.equipWeapon(item.first, damage);
                    (price == 100) ? player.setweaponHealth(rand() % 15 + 1) : player.setweaponHealth(rand() % 20 + 1);
                }

                cout << "成功購買 " << item.first << "！" << endl;
                cout << "剩餘金幣：" << playerMoney << " 金幣" << endl;
                return true;
            }
            else
            {
                cout << "金幣不足，無法購買 " << item.first << "！" << endl;
                return false;
            }
        }
        else
        {
            cout << "無效的商品編號！" << endl;
            return false;
        }
    }
};

#endif
