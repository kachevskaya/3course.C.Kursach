#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <vector>


using namespace sf;
int topgrid[24][24];
int grid[24][24];
int count;
void number() {
    count = 0;
    for (int i = 1; i <= 22; i++) {
        for (int j = 1; j <= 22; j++) {
            topgrid[i][j] = 22;

            if (rand() % 5 == 0) {grid[i][j] = 9;}

            else {grid[i][j] = 0;}

        }
    }

    for (int i = 1; i <= 22; i++) {
        for (int j = 1; j <= 22; j++) {
            int n = 0;

            if (grid[i][j] == 9)
                continue;
            if (grid[i + 1][j] == 9)
                n++;
            if (grid[i][j + 1] == 9)
                n++;
            if (grid[i - 1][j] == 9)
                n++;
            if (grid[i][j - 1] == 9)
                n++;
            if (grid[i + 1][j + 1] == 9)
                n++;
            if (grid[i - 1][j - 1] == 9)
                n++;
            if (grid[i - 1][j + 1] == 9)
                n++;
            if (grid[i + 1][j - 1] == 9)
                n++;

            grid[i][j] = n;
        }
    }
}
int main()
{   int w = 32;
    srand(time(0));
    RenderWindow window(VideoMode(800, 800), "Minesweeper");
    Texture t;
    Texture btnr;
    btnr.loadFromFile("C:\\Users\\kache\\CLionProjects\\untitled2\\reset.jpg");
    t.loadFromFile("C:\\Users\\kache\\CLionProjects\\untitled2\\tiles.png");
    btnr.setSmooth(true);
    Sprite tiles(t);
    Sprite button(btnr);
    button.setScale(0.1,0.1);
    button.setPosition(740,60);
    number();

    while (window.isOpen()) {
        int menuNum = 0;
        window.clear(Color::White);
        Vector2i pos = Mouse::getPosition(window);
        int x = pos.x / w;
        int y = pos.y / w;

        if (IntRect(740, 60, 52, 52).contains(Mouse::getPosition(window))) { menuNum = 1; }

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed){window.close();}
            if (event.type == Event::MouseButtonPressed) {
                if (event.key.code == Mouse::Left) {
                    topgrid[x][y] = grid[x][y];
                    count++;
                    if (topgrid[x][y] == 9 && count == 1){ number();}
                }
            }
            if (event.key.code == Mouse::Right){topgrid[x][y] = 11;}
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::T)) ||(event.key.code == Mouse::Left && menuNum == 1)) {number();}
        }
        for (int i = 1; i <= 22; i++) {
            for (int j = 1; j <= 22; j++) {
                if (topgrid[x][y] == 9){topgrid[i][j] = grid[i][j];}
                tiles.setTextureRect(IntRect(topgrid[i][j] * w, 0, w, w));
                tiles.setPosition(i * w, j * w);
                window.draw(tiles);
            }
        }
        window.draw(button);
        window.display();
    }
    return 0;
}