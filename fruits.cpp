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
    char name;
};

fruits = std::vector <Fruit>
{
    Fruit Apple(1, 0, 0, 0, 0, 'A'),
    Fruit Plum(-1, 0, 0, 0, 0, 'P'),
    Fruit Grape(0, 1, 0, 0, 0, 'G'),
    Fruit Banana(0, -1, 0, 0, 0, 'B'),
    Fruit Melon(0, 0, 1, 0, 0, 'M'),
    Fruit Peach(0, 0, -1, 0, 0, 'P'),
    Fruit Coconut(0, 0, 0, 1, 0, 'C'),
    Fruit Durian(0, 0, 0, 0, 1, 'D')
}

Fruit random_fruit() {
    std::srand(time(0));
    return fruits[rand() % 8];
}