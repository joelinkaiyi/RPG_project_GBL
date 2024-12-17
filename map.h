#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "shop.h"
#include "player.h"
#include "monster.h"
using namespace std;

class Map
{
private:
    vector<vector<char> > mapGrid;
    vector<Monster> monsters;
    unordered_map<char, string> locationInfo;
    unordered_map<string, pair<int, int> > locationCoords;
    vector<pair<int, int> > shopLocations; // 儲存所有商店地點
    int row, col;
    int playerX, playerY;
    Player &player;
    Shop shop;
    int monstersDefeated = 0;
    const int refreshWhenAllDefeat;

public:
    Map(int r, int c, Player &p) : row(r), col(c), playerX(r / 2), playerY(c / 2), refreshWhenAllDefeat(r / 2), player(p)
    {
        // 初始化地圖和商店位置
        mapGrid.resize(row, vector<char>(col, '.'));
        mapGrid[playerX][playerY] = '@';
        srand(time(0));

        // 設置城鎮和市集
        mapGrid[1][1] = 'T';
        mapGrid[2][3] = 'M';

        // 添加商店位置到列表
        shopLocations.push_back(std::make_pair(1, 1));
        shopLocations.push_back(std::make_pair(2, 3));

        locationInfo['T'] = "城鎮（有商店）";
        locationInfo['M'] = "市集（有商店）";
        locationCoords["城鎮"] = make_pair(1, 1);
        locationCoords["市集"] = make_pair(2, 3);
    }

    void displayMap()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                cout << mapGrid[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    bool hasMonsterAt(int x, int y)
    {
        for (const Monster &monster : monsters)
        {
            if (monster.x == x && monster.y == y)
            {
                return true;
            }
        }
        return false;
    }

    void movePlayer(char direction)
    {
        // 還原當前角色位置符號
        if (isShopLocation(playerX, playerY))
        {
            mapGrid[playerX][playerY] = (playerX == 1 && playerY == 1 ? 'T' : 'M');
        }
        else if (hasMonsterAt(playerX, playerY))
        {
            mapGrid[playerX][playerY] = 'i'; // 如果當前位置有怪物，恢復怪物標誌
        }
        else
        {
            mapGrid[playerX][playerY] = '.'; // 否則恢復為背景符號
        }

        // 更新角色位置
        switch (direction)
        {
        case 'w':
            if (playerX > 0)
                playerX--;
            break;
        case 'a':
            if (playerY > 0)
                playerY--;
            break;
        case 's':
            if (playerX < row - 1)
                playerX++;
            break;
        case 'd':
            if (playerY < col - 1)
                playerY++;
            break;
        default:
            cout << "無效指令！" << endl;
            return;
        }

        // 設置新角色位置
        mapGrid[playerX][playerY] = '@';
    }

    pair<int, int> getPlayerPosition() const
    {
        return make_pair(playerX, playerY);
    }

    bool isShopLocation(int x, int y)
    {
        for (size_t i = 0; i < shopLocations.size(); i++)
        {
            if (shopLocations[i].first == x && shopLocations[i].second == y)
                return true;
        }
        return false;
    }
    void movePlayerInstand(const string &locationName)
    {
        if (locationCoords.find(locationName) != locationCoords.end())
        {
            mapGrid[playerX][playerY] = '.';
            playerX = locationCoords[locationName].first;
            playerY = locationCoords[locationName].second;
            mapGrid[playerX][playerY] = '@';
            cout << "已傳送至 " << locationName << endl;
        }
        else
        {
            cout << "地點 " << locationName << " 不存在。有效地點有：";
            for (const auto &location : locationCoords)
            {
                cout << location.first << " ";
            }
            cout << endl;
        }
    }

    void enterShop()
    {
        if (isShopLocation(playerX, playerY))
        {
            cout << "歡迎來到商店！" << endl;

            shop.displayItems(); // 顯示商品列表

            while (true)
            {
                cout << "請輸入要購買的商品編號 (輸入 0 離開商店)：";
                int itemIndex;
                cin >> itemIndex;

                if (itemIndex == 0)
                {
                    cout << "離開商店，歡迎下次光臨！" << endl;
                    break;
                }

                if (!shop.buyItem(itemIndex, player.getMoney(), player.getInventory(), player))
                {
                    cout << "購買失敗，請重新選擇！" << endl;
                }
                player.displayMoney(); // 顯示剩餘金幣
            }
        }
        else
        {
            cout << "這裡沒有商店。" << endl;
        }
    }

    void generateMonsters(int count)
    {
        vector<string> monsterNames;
        monsterNames.push_back("女冒險者");
        monsterNames.push_back("女精靈");
        monsterNames.push_back("背叛者哥不林");
        for (int i = 0; i < count; i++)
        {
            int x = rand() % row;
            int y = rand() % col;
            int strength = rand() % 25 + 1; // 強度範圍 Lv.1 ~ Lv.25
            string name = monsterNames[rand() % monsterNames.size()];

            Monster monster(name, x, y, strength);
            monsters.push_back(monster);
            mapGrid[x][y] = 'i'; // 用 'i' 標記怪物
        }
        cout << "生成了 " << count << " 隻怪物。" << endl;
    }
    void removeMonster(const Monster &monster)
    {
        // 遍歷 monsters 找到符合條件的怪物並移除
        for (size_t i = 0; i < monsters.size(); ++i)
        {
            if (monsters[i].x == monster.x && monsters[i].y == monster.y)
            {
                monsters.erase(monsters.begin() + i);

                // 更新地圖格子
                if (isShopLocation(monster.x, monster.y))
                {
                    mapGrid[monster.x][monster.y] = (monster.x == 1 && monster.y == 1 ? 'T' : 'M');
                }
                else
                {
                    mapGrid[monster.x][monster.y] = '.';
                }
                return; // 找到並移除後退出函式
            }
        }

        // 如果沒有找到符合條件的怪物
        cout << "錯誤：未找到要移除的怪物。" << endl;
    }

    void fightMonster(Monster &monster)
    {
        while (monster.strength > 0 && player.getPlayerHealth() > 0)
        {
            cout << "怪物：" << monster.name << "（剩餘強度：" << monster.strength << "）" << endl;
            cout << "選擇攻擊方式：1. 普通攻擊 2. 技能攻擊 3. 使用武器 4. 恢復體力" << endl;

            string choice;
            cin >> choice;
            int damage = 0;

            if (choice == "1")
            {
                damage = rand() % 5 + 1;
                cout << "你對 " << monster.name << " 造成了 " << damage << " 點傷害。" << endl;
            }
            else if (choice == "2")
            {
                string skillName = player.selectSkill();
                if (!skillName.empty())
                {
                    player.useSkill(skillName);
                    int skillDamage = player.getSkillDamage(skillName);
                    if (skillDamage > 0)
                    {
                        monster.strength -= skillDamage;
                    }
                }
            }
            else if (choice == "3")
            {
                if (player.getWeaponDamage() > 0)
                {
                    damage = player.getWeaponDamage();
                    cout << "你使用武器 " << player.getEquippedWeapon() << " 對 " << monster.name << " 造成了 " << damage << " 點傷害！" << endl;
                    player.reduceWeaponHealth();
                }
                else
                {
                    cout << "你未裝備武器，無法使用武器攻擊。" << endl;
                    continue;
                }
            }
            else if (choice == "4")
            {
                player.recover();
                continue;
            }
            else
            {
                cout << "無效的選擇，請重新選擇。" << endl;
                continue;
            }

            monster.strength -= damage;

            if (monster.strength <= 0)
            {
                cout << "怪物 " << monster.name << " 已被擊敗！" << endl;
                monstersDefeated++;
                // 寵物獲取機率（例如：20%）
                if (rand() % 100 < 20)
                {
                    player.addPet(monster.name, monster.strength / 2);
                }
                int expGained = rand() % 50 + 10;
                int moneyEarned = rand() % 20 + 5;
                cout << "恭喜你成功防止自己被騙出洞穴！獲得經驗值 " << expGained << " 和金幣 " << moneyEarned << endl;
                player.gainExperience(expGained);
                player.earnMoney(moneyEarned);
                player.activePetGainExp(expGained); // 寵物獲得經驗
                // 使用移除邏輯

                removeMonster(monster);

                break;
            }

            // 怪物反擊
            int monsterDamage = rand() % 4 + 1;
            player.setPlayerHealth(-monsterDamage);
            cout << monster.name << " 使出反擊，造成了 " << monsterDamage << " 點的心靈創傷。你剩餘體力：" << player.getPlayerHealth() << endl;

            if (player.getPlayerHealth() <= 0)
            {
                cout << "你已無法繼續戰鬥。" << endl;
                break;
            }
        }

        if (monstersDefeated == refreshWhenAllDefeat)
        {
            refreshMonsters();
        }
    }

    // 刷新怪物資訊
    void refreshMonsters()
    {
        cout << "刷新怪物..." << endl;
        monsters.clear();
        generateMonsters(row / 2); // 重新生成(row/2)隻怪物
        usleep(1000);
        cout << "怪物刷新完成。" << endl;
        monstersDefeated = 0;
    }
    void checkMonster()
    {
        cout << "怪物所在位置" << endl;
        for (auto monster : monsters)
        {
            cout << "- " << "(" << monster.x << "," << monster.y << ")" << endl;
        }
    }
    vector<Monster *> getMonstersAtPlayerLocation(int playerX, int playerY)
    {
        vector<Monster *> monstersAtLocation;

        for (Monster &monster : monsters)
        {
            if (monster.x == playerX && monster.y == playerY)
            {
                monstersAtLocation.push_back(&monster);
            }
        }

        return monstersAtLocation;
    }
};
