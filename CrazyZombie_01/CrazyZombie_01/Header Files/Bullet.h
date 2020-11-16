#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <iostream>


class Bullet
{
	
private:
	sf::Sprite shape;
	sf::Texture* texture;

	sf::Vector2f direction;
	
	sf::Vector2f mousePosition;

	float distanceFromPlayerToMouse;

	//Bullet
	float movementSpeed;
	float bulletDamage;


public: 
	Bullet();
	Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed, float bulletDamage);
	virtual ~Bullet();

	//Accessor
	const sf::FloatRect getBounds() const;
	float getBulletDamage();

	//Functions


	void update(float& dtForSpeed);
	void render(sf::RenderTarget* target);


};

#endif