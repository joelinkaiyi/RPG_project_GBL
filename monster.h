#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <unistd.h>
using namespace std;

class Monster
{
private:
    static vector<Monster> monsters;
    static int monstersDefeated;

public:
    string name;
    int x, y;
    int strength;

    Monster() {}
    Monster(string n, int xPos, int yPos, int str)
        : name(n), x(xPos), y(yPos), strength(str) {}
};
#endif
