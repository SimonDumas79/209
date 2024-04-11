#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>


using namespace sf;
using namespace std;

const int ROWS = 20;
const int COLS = 20;
const int BLOCK_SIZE = 50; // Size of each block in pixels
char maze[ROWS][COLS] = {
    // Maze initialization remains the same
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', 'P', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#'},
    {'#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#'},
    {'#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', '#', ' ', '#', 'X', '#'},
    {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', '#', 'X', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', '#', ' ', '#'},
    {'#', ' ', '#', '#', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', '#'},
    {'#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', ' ', '#', ' ', '#', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', '#', '#'},
    {'#', ' ', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', '#', ' ', '#', ' ', '#', '#'},
    {'#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#'},
    {'#', ' ', ' ', 'X', ' ', '#', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
    {'#', 'E', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

struct Block {
    int x;
    int y;
};

bool visited[ROWS][COLS];
int path[ROWS][COLS];
Block endBlock;
Block sourceBlock;

int playerX = 1;
int playerY = 1;
bool isGameOver = false;


// Function to draw the maze
void drawMaze(sf::RenderWindow& window) {

    //draw maze
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            RectangleShape newRect(Vector2f(static_cast<float>(BLOCK_SIZE), static_cast<float>(BLOCK_SIZE)));
            if (maze[i][j] == '#')
            {
                newRect.setFillColor(Color::Black);
            }
            else if (maze[i][j] == ' ')
            {
                newRect.setFillColor(Color::White);
            }
            else if (maze[i][j] == '*')
            {
                newRect.setFillColor(Color::Cyan);
            }
            else if (maze[i][j] == 'X')
            {
                newRect.setFillColor(Color::Red);
            }
            else if (maze[i][j] == 'P')
            {
                newRect.setFillColor(Color::White);
            }
            else if (maze[i][j] == 'E')
            {
                newRect.setFillColor(Color::Blue);
            }

            newRect.setPosition(static_cast<float>(i * BLOCK_SIZE), static_cast<float>(j * BLOCK_SIZE));
            window.draw(newRect);

        }
    }

    CircleShape playerHead(static_cast<float>(BLOCK_SIZE / 4.0f));
    playerHead.setFillColor(Color::Yellow);
    playerHead.setPosition(playerX * BLOCK_SIZE + playerHead.getRadius(), playerY * BLOCK_SIZE);
    window.draw(playerHead);


    RectangleShape playerBody(Vector2f(static_cast<float>(BLOCK_SIZE / 4.0f), static_cast<float>(BLOCK_SIZE / 2.0f)));
    playerBody.setFillColor(Color::Green);
    playerBody.setPosition(playerX * BLOCK_SIZE + static_cast<float>(BLOCK_SIZE / 2.0f) - playerBody.getSize().x / 2.0f, playerY * BLOCK_SIZE + playerBody.getSize().y);
    window.draw(playerBody);
}

// Updated movePlayer function with SFML logic here
bool movePlayer(char input) {

    int newPlayerX = playerX;
    int newPlayerY = playerY;

    //w
    if (input == 'w')
    {
        newPlayerY--;
    }
    //a
    else if (input == 'a')
    {
        newPlayerX--;
    }
    //s
    else if (input == 's')
    {
        newPlayerY++;
    }
    //d
    else
    {
        newPlayerX++;
    }

    //if the new spot is empty, set the old player spot to be empty and the new player spot to be a P
    if (maze[newPlayerX][newPlayerY] == ' ' || maze[newPlayerX][newPlayerY] == '*')
    {
        maze[playerX][playerY] = ' ';
        playerX = newPlayerX;
        playerY = newPlayerY;
        maze[playerX][playerY] = 'P';
    }
    else if (maze[newPlayerX][newPlayerY] == '#')
    {
        return true;
    }
    else if (maze[newPlayerX][newPlayerY] == 'X')
    {
        isGameOver = true;
        std::cout << "You encountered an enemy and lost!\n";
    }
    else if (maze[newPlayerX][newPlayerY] == 'E')
    {
        isGameOver = true;
        std::cout << "You reached the end and won!\n";
    }

    return true;
}



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

int main() {
    sf::RenderWindow window(sf::VideoMode(COLS * BLOCK_SIZE, ROWS * BLOCK_SIZE), "Maze Game");
    window.setFramerateLimit(60);

    //find end
    endBlock.x = -1;
    endBlock.y = -1;
    sourceBlock.x = -1;
    sourceBlock.y = -1;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (maze[i][j] == 'P')
            {
                sourceBlock.x = i;
                sourceBlock.y = j;
            }
            if (maze[i][j] == 'E')
            {
                endBlock.x = i;
                endBlock.y = j;
            }
            if (endBlock.x != -1 && sourceBlock.x != -1)
            {
                i = ROWS;
                j = COLS;
                DFS(sourceBlock, endBlock);
                printPath(endBlock);
            }
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && !isGameOver) {
                // Handle player movement
                if (event.key.code == sf::Keyboard::W) movePlayer('w');
                else if (event.key.code == sf::Keyboard::S) movePlayer('s');
                else if (event.key.code == sf::Keyboard::A) movePlayer('a');
                else if (event.key.code == sf::Keyboard::D) movePlayer('d');
            }
        }

        window.clear();
        drawMaze(window);
        window.display();

        if (isGameOver) {
            // Handle game over state
            // For simplicity, we'll just close the window
            window.close();
        }
    }

    system("pause");

    return 0;
}
