#ifndef FRUITS_H
#define FRUITS_H

#include <vector>
#include <utility>

struct Fruit
{
    int add_len;
    int speed;
    int weight;
    int invert_control;
    int invent_head_to_tail;
    char name;

    Fruit(int len, int spd, int wgt, int inv_ctrl, int inv_head, char n);
};

extern std::vector<Fruit> fruits;
Fruit random_fruit();


#endif
