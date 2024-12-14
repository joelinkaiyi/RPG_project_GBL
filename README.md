# 哥布林猴的一生 (Developed By Joey Lin)
![image](https://github.com/joelinkaiyi/RPG_project_GBL/blob/main/%E5%93%A5%E5%B8%83%E6%9E%97.jpg）
## 專案簡介
一款基於 C++ 開發的哥布林扮演(或者不是扮演)遊戲。玩家可以探索地圖、戰鬥以防止被騙出洞穴、完成工作賺取金幣，以及管理角色的資源。遊戲整合地圖系統、商店系統、戰鬥系統和工作系統，提供豐富的遊戲體驗。

---

## 功能特色
- **角色管理**：玩家可以創建最多三個角色，並選擇或刪除角色進行遊戲。
- **地圖探索**：玩家可以在自訂大小的地圖中移動，探索不同地點如城鎮與市集。
- **商店系統**：進入商店購買道具增強能力。
- **工作系統**：完成工作賺取金幣，需注意體力消耗。
- **怪物戰鬥**：隨機生成怪物，玩家可以選擇普通攻擊或技能攻擊進行戰鬥。
- **快速傳送**：玩家可以瞬間移動到特定地點。
- **資源管理**：透過金幣、體力及背包物品的管理來平衡遊戲進程。

---

## 文件結構
- **main.cpp**：主程式，控制遊戲整體流程。
- **map.h**：地圖管理，包含玩家移動、傳送及怪物生成功能。
- **player.h**：玩家模組，管理金幣、體力及背包。
- **monster.h**：怪物類別，定義怪物屬性如名稱、位置及強度。
- **shop.h**：商店系統，支援物品購買功能。
- **company.h**：工作系統，玩家透過完成工作賺取金幣。

---

## 快速開始

1. **編譯專案**
   使用以下指令編譯程式碼：
   ```bash
   g++ main.cpp -o RPGGame
2. **執行遊戲主程式**

    ```bash
    ./main
   
