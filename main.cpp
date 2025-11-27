#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 10;
const int FRUIT_LIFETIME = 50;

struct Fruit
{
    int add_len;
    int speed;
    int weight;
    int invent_head_to_tail;
    char name;
    int x;
    int y;
    int lifetime;

    Fruit(int len, int spd, int wgt, int inv_head, char n, int x, int y)
        : add_len(len), speed(spd), weight(wgt), invent_head_to_tail(inv_head), 
          name(n), x(x), y(y), lifetime(FRUIT_LIFETIME) {}
};

vector<Fruit> fruits =
{
    Fruit(1, 0, 0, 0, 'A', 0, 0),
    Fruit(-1, 0, 0, 0, 'P', 0, 0),
    Fruit(0, 1, 0, 0, 'G', 0, 0),
    Fruit(0, -1, 0, 0, 'B', 0, 0),
    Fruit(0, 0, 1, 0, 'M', 0, 0),
    Fruit(0, 0, -1, 0, 'E', 0, 0),
    Fruit(0, 0, 0, 1, 'D', 0, 0)
};

vector<pair<int, int>> snake;
Fruit food = Fruit(0, 0, 0, 0, 'A', 0, 0);
int score = 0;
int speed_game = 0;
int speed_snake = 1;
bool play = true;

bool inverted_head_tail = false;
int effect_timer = 0;
const int EFFECT_DURATION = 20;

int dir_x = 1, dir_y = 0;

Fruit random_fruit() {
    Fruit new_fruit = fruits[rand() % fruits.size()];
    new_fruit.lifetime = FRUIT_LIFETIME;
    return new_fruit;
}

void apply_fruit_effects(const Fruit& fruit) {
    if (fruit.add_len != 0) {
        if (fruit.add_len > 0) {
            for (int i = 0; i < fruit.add_len; i++) {
                snake.push_back(snake.back());
            }
        } else {
            for (int i = 0; i < -fruit.add_len && snake.size() > 1; i++) {
                snake.pop_back();
            }
        }
    }
    
    if (fruit.weight != 0) {
        if (fruit.weight > 0) {
            for (int i = 0; i < 2; i++) {
                snake.push_back(snake.back());
            }
        } else {
            if (snake.size() > 1) {
                snake.pop_back();
            }
        }
    }
    
    if (fruit.speed != 0) {
        speed_snake += fruit.speed;
        if (speed_snake < 1) speed_snake = 1;
        if (speed_snake > 5) speed_snake = 5;
    }
    
    if (fruit.invent_head_to_tail != 0) {
        inverted_head_tail = true;
        effect_timer = EFFECT_DURATION;
    }
}

void setup() {
    cout << "Set Speed, 1 - max, 5 - min" << endl;
    cin >> speed_game;

    if (speed_game < 1) speed_game = 1;
    if (speed_game > 5) speed_game = 5;

    initscr();
    curs_set(0);
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    timeout((6 - speed_game) * 10);

    snake.push_back(make_pair(HEIGHT / 2, WIDTH / 2));
    
    srand(time(0));
    food = random_fruit();
    food.x = rand() % HEIGHT;
    food.y = rand() % WIDTH;
}

bool is_position_free(int y, int x) {
    for (size_t i = 0; i < snake.size(); i++) {
        if (snake[i].first == y && snake[i].second == x) {
            return false;
        }
    }
    return true;
}

void draw() {
    clear();

    for (int i = 0; i < WIDTH + 2; i++) {
        mvprintw(0, i, "-");
        mvprintw(HEIGHT + 1, i, "-");
    }
    for (int i = 1; i <= HEIGHT; i++) {
        mvprintw(i, 0, "|");
        mvprintw(i, WIDTH + 1, "|");
    }

    for (size_t i = 0; i < snake.size(); i++) {
        bool is_head = inverted_head_tail ? (i == snake.size() - 1) : (i == 0);
        if (is_head) {
            mvprintw(snake[i].first + 1, snake[i].second + 1, "O");
        } else {
            mvprintw(snake[i].first + 1, snake[i].second + 1, "o");
        }
    }

    if (food.lifetime > 0) {
        mvprintw(food.x + 1, food.y + 1, "%c", food.name);
    }

    mvprintw(HEIGHT + 2, 0, "Score: %d. Length: %zu. Speed: %d", score, snake.size(), speed_snake);
    mvprintw(HEIGHT + 3, 0, "Fruit lifetime: %d", food.lifetime);
    
    if (inverted_head_tail) {
        mvprintw(HEIGHT + 4, 0, "Effect: INVERTED HEAD/TAIL been actived! (%d moves left)", effect_timer);
    }
    
    mvprintw(HEIGHT + 5, 0, "Use Arrows/WASD. Press 'q' to quit.");

    refresh();
}

void input() {
    int ch = getch();
    
    switch (ch) {
        case KEY_LEFT:
        case 'a':
            if (dir_x != 1) { dir_x = -1; dir_y = 0; }
            break;
        case KEY_RIGHT:
        case 'd':
            if (dir_x != -1) { dir_x = 1; dir_y = 0; }
            break;
        case KEY_UP:
        case 'w':
            if (dir_y != 1) { dir_x = 0; dir_y = -1; }
            break;
        case KEY_DOWN:
        case 's':
            if (dir_y != -1) { dir_x = 0; dir_y = 1; }
            break;
        case 'q':
            endwin();
            play = false;
            break;
    }
}

bool game() {
    input();

    if (effect_timer > 0) {
        effect_timer--;
        if (effect_timer == 0) {
            inverted_head_tail = false;
        }
    }

    if (food.lifetime > 0) {
        food.lifetime--;
    }

    int head_y, head_x;
    if (inverted_head_tail) {
        head_y = snake.back().first;
        head_x = snake.back().second;
    } else {
        head_y = snake[0].first;
        head_x = snake[0].second;
    }

    int new_y = head_y + dir_y;
    int new_x = head_x + dir_x;

    if (new_x < 0 || new_x >= WIDTH || new_y < 0 || new_y >= HEIGHT) {
        return false;
    }

    for (size_t i = 0; i < snake.size(); i++) {
        if (new_y == snake[i].first && new_x == snake[i].second) {
            return false;
        }
    }

    bool ate_food = false;
    if (food.lifetime > 0 && new_y == food.x && new_x == food.y) {
        ate_food = true;
        score += 10;
        apply_fruit_effects(food);
        
        do {
            food = random_fruit();
            food.x = rand() % HEIGHT;
            food.y = rand() % WIDTH;
        } while (!is_position_free(food.x, food.y));
    } else if (food.lifetime <= 0) {
        do {
            food = random_fruit();
            food.x = rand() % HEIGHT;
            food.y = rand() % WIDTH;
        } while (!is_position_free(food.x, food.y));
    }

    if (inverted_head_tail) {
        snake.push_back(make_pair(new_y, new_x));
        if (!ate_food) {
            snake.erase(snake.begin());
        }
    } else {
        snake.insert(snake.begin(), make_pair(new_y, new_x));
        if (!ate_food) {
            snake.pop_back();
        }
    }

    return true;
}

int main() {
    setup();
    srand(time(0));
    while (game() && play) {
        draw();
        usleep((6 - speed_snake) * 50000);
    }

    endwin();
    cout << "GAME OVER! Final Score: " << score << endl;
    return 0;
}