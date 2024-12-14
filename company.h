#ifndef COMPANY_H
#define COMPANY_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include "player.h"
using namespace std;

class Company
{
private:
    unordered_map<string, pair<int, int> > works; // 工作名稱 -> <金幣, 體力消耗>

public:
    Company()
    {
        // 初始化工作名稱和報酬/體力消耗
        works["廉價勞力"] = make_pair(20, 2);
        works["洞穴守護者"] = make_pair(60, 6);
        works["女冒險者的舔狗"] = make_pair(120, 12);
    }

    // 顯示可用工作列表
    void displayWorks()
    {
        cout << "工作列表:" << endl;
        for (const auto &work : works)
        {
            cout << "- " << work.first
                 << " : " << work.second.first << " 金幣"
                 << " (體力消耗 " << work.second.second << ")" << endl;
        }
    }

    // 玩家選擇工作並獲得報酬
    bool getWork(string workName, int &playerMoney, Player &p)
    {
        if (works.find(workName) != works.end())
        {
            int workReward = works[workName].first;   // 金幣報酬
            int staminaCost = works[workName].second; // 體力消耗

            if (p.getPlayerHealth() >= staminaCost)
            {
                p.setPlayerHealth(-(staminaCost)); // 扣除體力
                playerMoney += workReward;         // 增加金幣
                cout << "完成工作：" << workName << "！" << endl;
                cout << "獲得 " << workReward << " 金幣，剩餘體力：" << p.getPlayerHealth() << endl;

                // 完成高級工作，獲得屬性點數
                if (workName == "老闆的牛馬")
                {
                    p.gainAttributePoints(2); // 獲得 2 屬性點數
                    cout << "你努力工作，額外獲得 2 屬性點數！" << endl;
                }

                return true;
            }
            else
            {
                cout << "體力不足，無法完成工作：" << workName << "。" << endl;
                return false;
            }
        }
        else
        {
            cout << "無效的工作名稱：" << workName << "。" << endl;
            return false;
        }
    }
};

#endif
