#include <ctime>
#include <vector>
#include <stdlib.h>
/*
apple(classic fruit) -> +1 len shake
plum -> -1 len shake
grape -> +1 speed
banana -> -1 speed
melon -> +1 weight
peach -> -1 weight
coconut -> invert сontrol
durian -> invert head to tail
*/

struct Fruit
{
    int add_len;
    int speed;
    int weight;
    int invert_control;
    int invent_head_to_tail;
    char name;
    std::pair<int, int> coord;

    // Create construct
    Fruit(int len, int spd, int wgt, int inv_ctrl, int inv_head, char n, std::pair<int, int> crd)
        : add_len(len), speed(spd), weight(wgt), invert_control(inv_ctrl),
          invent_head_to_tail(inv_head), name(n), coord(crd) {}

};

std::vector <Fruit> fruits =
{
    Fruit(1, 0, 0, 0, 0, 'A', std::make_pair(0, 0)),
    Fruit(-1, 0, 0, 0, 0, 'P', std::make_pair(0, 0)),
    Fruit(0, 1, 0, 0, 0, 'G', std::make_pair(0, 0)),
    Fruit(0, -1, 0, 0, 0, 'B',std::make_pair(0, 0)),
    Fruit(0, 0, 1, 0, 0, 'M', std::make_pair(0, 0)),
    Fruit(0, 0, -1, 0, 0, 'E', std::make_pair(0, 0)),
    Fruit(0, 0, 0, 1, 0, 'C', std::make_pair(0, 0)),
    Fruit(0, 0, 0, 0, 1, 'D', std::make_pair(0, 0))
};

Fruit random_fruit() {
    std::srand(time(0));
    return fruits[rand() % 8];
}
