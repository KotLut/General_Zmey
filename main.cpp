#include <ncurses.h>  // include
#include <unistd.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "fruits.h"

using namespace std; // std


// start constant

const int WIDTH = 20;
const int HEIGHT = 10;
int dir_x = 1, dir_y = 0;
vector<pair<int, int>> snake;
pair<int, int> food;
int score = 0;

int speed_game = 200;
int speed_snake = 1;
bool play = true;
// add time
int game_time = 0;

void setup() { // global setup

    cout << "Set Speed, 1 - max, 5 - min" << endl;
    cin >> speed_game;

    if (speed_game < 1) speed_game = 1;
    if (speed_game > 5) speed_game = 5;


    initscr();          // update and clear
    curs_set(0);
    noecho();
    cbreak();
    keypad(stdscr, TRUE);  // arrows
    timeout((6 - speed_game) * 10);    // speed

    // spawn snake and food
    snake.push_back(make_pair(HEIGHT / 2, WIDTH / 2));
    srand(time(0));
    food = make_pair(rand() % HEIGHT, rand() % WIDTH);
}

// paint
void draw() {
    clear();

    // draw  board
    for (int i = 0; i < WIDTH + 2; i++) {
        mvprintw(0, i, "-");
        mvprintw(HEIGHT + 1, i, "-");
    }
    for (int i = 1; i <= HEIGHT; i++) {
        mvprintw(i, 0, "|");
        mvprintw(i, WIDTH + 1, "|");
    }

    // draw snake
    for (int i = 0; i < snake.size(); i++) {
        if (i == 0){
                mvprintw(snake[i].first + 1, snake[i].second + 1, "O");
        }
        else {
                mvprintw(snake[i].first + 1, snake[i].second + 1, "o");
        }
    }

    // place food
    mvprintw(food.first + 1, food.second + 1, "F");

    // score
    mvprintw(HEIGHT + 2, 0, "Score: %d. Use Arrows/WASD. Press 'q' to quit.", score);

    refresh(); // apply
}

// input
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
            endwin(); // quit
            play = false;
            break;
    }
}

// game
bool game() {
    input();
    // update
    game_time++;

    // head
    int new_y = snake[0].first + dir_y;
    int new_x = snake[0].second + dir_x;

    // boom dead via board
    if (new_x < 0 || new_x >= WIDTH || new_y < 0 || new_y >= HEIGHT) {
        return false;
    }

    // boom dead via body
    for (size_t i = 1; i < snake.size(); i++) {
        if (new_y == snake[i].first && new_x == snake[i].second) {
            return false;
        }
    }

    // add new head
    snake.insert(snake.begin(), make_pair(new_y, new_x));

    // add new food
    if (game_time == 20) {
        game_time = 0;
        food = make_pair(rand() % HEIGHT, rand() % WIDTH);
    }
    if (new_y == food.first && new_x == food.second) {
        score += 10;
        game_time = 0;
        food = make_pair(rand() % HEIGHT, rand() % WIDTH);
    } else {
        snake.pop_back();
    }

    return true;
}


int main() {
    setup();
    while (game() && play) {
        draw();
        usleep((speed_game + speed_snake) * 100000);
    }

    endwin(); // return result
    cout << "GAME OVER! Final Score: " << score << endl;
    return 0;
}

