#include <iostream>
#include <vector>
#include <conio.h>   // _kbhit(), _getch()
#include <windows.h> // Sleep()
#include <ctime>     // time()
#include <cstdlib>   // rand(), srand()

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 20;

bool gameOver;
int x, y;
int fruitX, fruitY;
int score;
char direction;

vector<pair<int, int>> snake;

// Initialize game state
void setup() {
    gameOver = false;
    direction = ' ';
    score = 0;

    x = WIDTH / 2;
    y = HEIGHT / 2;

    srand(static_cast<unsigned>(time(nullptr)));
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;

    snake.clear();
    snake.push_back({ x, y });
}

// Draw game field
void draw() {
    system("cls");

    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                cout << "#";

            if (i == y && j == x) {
                cout << "O"; // Snake head
            }
            else if (i == fruitY && j == fruitX) {
                cout << "F"; // Fruit
            }
            else {
                bool printTail = false;
                for (auto segment : snake) {
                    if (segment.first == j && segment.second == i) {
                        cout << "o"; // Snake body
                        printTail = true;
                        break;
                    }
                }
                if (!printTail)
                    cout << " ";
            }

            if (j == WIDTH - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;
}

// Handle keyboard input
void input() {
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
        case 'a': direction = 'L'; break;
        case 'd': direction = 'R'; break;
        case 'w': direction = 'U'; break;
        case 's': direction = 'D'; break;
        case 'x': gameOver = true; break;
        default: break;
        }
    }
}

// Game logic
void logic() {
    pair<int, int> prev = snake[0];
    pair<int, int> prev2;

    snake[0] = { x, y };

    for (size_t i = 1; i < snake.size(); i++) {
        prev2 = snake[i];
        snake[i] = prev;
        prev = prev2;
    }

    switch (direction) {
    case 'L': x--; break;
    case 'R': x++; break;
    case 'U': y--; break;
    case 'D': y++; break;
    default: break;
    }

    // Wall wrap
    if (x >= WIDTH) x = 0;
    else if (x < 0) x = WIDTH - 1;

    if (y >= HEIGHT) y = 0;
    else if (y < 0) y = HEIGHT - 1;

    // Eating fruit
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        snake.push_back(snake.back());
    }

    // Collision with body
    for (size_t i = 1; i < snake.size(); i++) {
        if (snake[i].first == x && snake[i].second == y) {
            gameOver = true;
            break;
        }
    }
}

int main() {
    setup();

    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(100);
    }

    system("cls");
    cout << "Game Over!" << endl;
    cout << "Final Score: " << score << endl;

    return 0;
}
