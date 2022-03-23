#include <iostream>
#include "SFML/graphics.hpp"
#include "SFML/system.hpp"
#include "SFML/window.hpp"

using namespace std;

//classes start
class gamePlayer {
public:
    float playerX;
    float playerY;
    int PlayerSpeed;
    string playerName;
    bool playerUp;
    bool playerLeft;
    bool playerRight;

    gamePlayer()
    {
        cout << "Player Constructor" << "\n";
        this->playerX = 400.0f;
        this->playerY = 680.0f;
        this->PlayerSpeed = 5;
        this->playerUp = false;
        this->playerLeft = false;
        this->playerRight = false;
    }


    ~gamePlayer()
    {
        cout << "Player Destructor" << "\n";
    }

    ////getter
    //const float getPlayerX()
    //{
    //    return this->playerX; 
    //}
    ////setter
    //void setPlayerX(const float playerX)
    //{
    //    this->playerX = playerX;
    //}
};

gamePlayer player;

class gameGravity {
private:
    float velocityX;
    float velocityY;
    float accelerationX;
    float accelerationY;
    float inGameGravity;

public:
 

    gameGravity()
    {
        cout << "gameGravity Constructor" << "\n";
        this->velocityX = 0;
        this->velocityY = 0;
        this->accelerationX = 0;
        this->accelerationY = 0;
        this->inGameGravity = 1;

    }


    void gameGravityFun()
    {

        if (player.playerY < 680)
        {
            velocityY += inGameGravity;
        }
        else if (player.playerY > 680)
        {
            player.playerY = 680;
        }

        velocityX += accelerationX;
        velocityY += accelerationY;

        player.playerX += velocityX;
        player.playerY += velocityY;
    }

    void jump()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            velocityY = -10;
        }
    }
    ~gameGravity()
    {
        cout << "gameGravity Destructor" << "\n";
    } 

};

class spritesAndTextures {
public:
    //textures
    sf::Texture playerTex;
    sf::Texture floorTex;
    //sprites
    sf::Sprite player;
    sf::Sprite floor;

};
//classes end

    int main()
    {
        sf::RenderWindow window(sf::VideoMode(800, 800), "Game");

        window.setVerticalSyncEnabled(true);
        window.setKeyRepeatEnabled(false);

        gameGravity gravity;

  /*      gameGravity::gameGravityFun();*/
        //gravity.gameGravityFun();
        //gravity.jump();

        spritesAndTextures sat;
        sat.playerTex.loadFromFile("images/player.png");
        sat.floorTex.loadFromFile("images/floor.jpg");
        sat.player.setTexture(sat.playerTex);
        sat.floor.setTexture(sat.floorTex);
        sat.playerTex.setSmooth(true);
        sat.floorTex.setSmooth(true);
        sat.player.scale(2, 2);
        sat.floor.scale(4, 2);
        sat.floor.setPosition(1.0f, 775.0f);


        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                //If key is pressed
                if (event.type == sf::Event::KeyPressed)
                {
                    switch (event.key.code)
                    {
                    case sf::Keyboard::W:player.playerUp = true; break;
                    case sf::Keyboard::A:player.playerLeft = true; break;
                    case sf::Keyboard::D:player.playerRight = true; break;
                    default: break;
                    }
                }

                if (event.type == sf::Event::KeyReleased)
                {
                    switch (event.key.code)
                    {
                    case sf::Keyboard::W:player.playerUp = false; break;
                    case sf::Keyboard::A:player.playerLeft = false; break;
                    case sf::Keyboard::D:player.playerRight = false; break;
                    default: break;
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    sat.player.setScale(-2, 2);
                }
                else
                {
                    sat.player.setScale(2, 2);
                }



                //if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                //{
                //    gravity.velocityY = -10;
                //}


            }


            //Update player
            if (player.playerLeft) player.playerX -= player.PlayerSpeed;
            if (player.playerRight) player.playerX += player.PlayerSpeed;
            if (player.playerUp) player.playerY -= player.PlayerSpeed;

            //Screen boundaries
            if (player.playerX < 0) player.playerX = 0;
            if (player.playerX > (int)window.getSize().x) player.playerX = window.getSize().x;
            if (player.playerY < 0) player.playerY = 0;
            if (player.playerY > (int)window.getSize().y) player.playerY = window.getSize().y;




            //Clear window and draw new
            window.clear();
            sat.player.setPosition(player.playerX, player.playerY);
            window.draw(sat.player);
            window.draw(sat.floor);
            window.display();

        }
             return 0;
    }
