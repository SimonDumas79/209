#include <iostream>
#include <queue>

using namespace std;

const int ROWS = 10;
const int COLS = 10;
char maze[ROWS][COLS] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', '#', ' ', 'X', '#'}, // Enemy at (1,8)
    {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', '#'},
    {'#', ' ', '#', 'P', ' ', ' ', ' ', ' ', ' ', '#'}, // Player start position
    {'#', ' ', '#', '#', '#', ' ', '#', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', '#', '#', '#', ' ', '#', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', '#', '#', ' ', '#', '#', '#', '#'},
    {'#', 'E', '#', '#', '#', '#', '#', '#', '#', '#'} // Exit
};

bool visited[ROWS][COLS];
int path[ROWS][COLS];

int playerX = 3;
int playerY = 3;
bool isGameOver = false;

void printMaze() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}

struct Block {
    int x;
    int y;
};

bool DFS(Block source, Block destination) {
    // Initialize visited array and path
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            visited[i][j] = false;
            path[i][j] = -1;
        }
    }

    queue<Block> queue;
    queue.push(source);
    visited[source.x][source.y] = true;

    while (!queue.empty()) {
        Block current = queue.front();
        queue.pop();

        if (current.x == destination.x && current.y == destination.y) {
            return true; // Destination reached
        }

        int offsetX[4] = { -1, 1, 0, 0 };
        int offsetY[4] = { 0, 0, -1, 1 };

        for (int i = 0; i < 4; i++) {
            Block nextBlock;
            nextBlock.x = current.x + offsetX[i];
            nextBlock.y = current.y + offsetY[i];
            if ((maze[nextBlock.x][nextBlock.y] == ' ' || maze[nextBlock.x][nextBlock.y] == 'E')
                && !visited[nextBlock.x][nextBlock.y]) {
                queue.push(nextBlock);
                visited[nextBlock.x][nextBlock.y] = true;
                path[nextBlock.x][nextBlock.y] = i;
            }
        }
    }
    return false; // Destination not reached
}

void printPath(Block destination) {
    if (maze[destination.x][destination.y] == ' ')
        maze[destination.x][destination.y] = '*';

    if (path[destination.x][destination.y] == -1) {
        cout << destination.x << " " << destination.y << endl; // Print the source node
    }
    else {
        int offsetX[4] = { -1, 1, 0, 0 };
        int offsetY[4] = { 0, 0, -1, 1 };
        Block lastBlock;
        lastBlock.x = destination.x - offsetX[path[destination.x][destination.y]];
        lastBlock.y = destination.y - offsetY[path[destination.x][destination.y]];

        printPath(lastBlock); // Recursive call to print the path
        cout << destination.x << " " << destination.y << endl;
    }
}


bool movePlayer(char input) {
    int newX = playerX, newY = playerY;
    switch (input) {
    case 'w': newX--; break;
    case 's': newX++; break;
    case 'a': newY--; break;
    case 'd': newY++; break;
    }

    // Check for walls and the bounds of the maze
    if (newX < 0 || newX >= ROWS || newY < 0 || newY >= COLS || maze[newX][newY] == '#') {
        return false; // Can't move
    }

    // Check for the enemy
    if (maze[newX][newY] == 'X') {
        printf("You've encountered an enemy and lost. Try again!\n");
        isGameOver = true;
        return true;
    }

    // Check for the exit
    if (maze[newX][newY] == 'E') {
        printf("Congratulations, you've escaped the maze!\n");
        isGameOver = true;
        return true;
    }

    // Update player's position
    maze[playerX][playerY] = ' ';
    playerX = newX;
    playerY = newY;
    maze[playerX][playerY] = 'P';
    return true;
}

int main() {
    char input;

    Block source, destination;
    source.x = playerX;
    source.y = playerY;
    destination.x = 9;
    destination.y = 1;

    if (DFS(source, destination)) {
        cout << "Path found: ";
        printPath(destination);
    }


    while (!isGameOver) {
        printMaze();
        printf("Move (WASD): ");
        scanf_s(" %c", &input); // Space before %c to ignore 'enter'

        if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
            movePlayer(input);
        }
    }

    system("Pause");

    return 0;
}