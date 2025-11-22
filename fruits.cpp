#include <ctime> 
#include <vector>

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
};

fruits = std::vector <Fruit>
{
    Fruit Apple(1, 0, 0, 0, 0),
    Fruit Plum(-1, 0, 0, 0, 0),
    Fruit Grape(0, 1, 0, 0, 0),
    Fruit Banana(0, -1, 0, 0, 0),
    Fruit Melon(0, 0, 1, 0, 0),
    Fruit Peach(0, 0, -1, 0, 0),
    Fruit Coconut(0, 0, 0, 1, 0),
    Fruit Durian(0, 0, 0, 0, 1)
}

Fruit random_fruit() {
    std::srand(time(0));
    return fruits[rand() % 8];
}