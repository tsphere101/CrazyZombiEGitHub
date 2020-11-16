// Crazy Zombie.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "Game.h"
#include <time.h>

int main()
{
    std::cout << "Hello From me, the SFML. Crazy Zombie is starting..\n";
    
    srand(time(NULL));

    Game game;
    //sf::RenderWindow window(sf::VideoMode(1920,1080), "Crazy Zombie", sf::Style::Fullscreen | sf::Style::Close);
    //sf::Event ev; // captureing the happening event
    //   
    while (game.running())
    {
		//Event polling
        game.update();

        game.render();

		
        //draw the game


 


    }




    return 0;
}
