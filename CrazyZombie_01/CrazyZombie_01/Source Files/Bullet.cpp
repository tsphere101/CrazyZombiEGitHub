#include "Bullet.h"



Bullet::Bullet()
{
}

Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed, float bulletDamage)
{
	this->shape.setTexture(*texture);

	this->distanceFromPlayerToMouse = sqrt((pos_x - dir_x) * (pos_x - dir_x) + (pos_y - dir_y) * (pos_y - dir_y));

	this->shape.setPosition(pos_x-10.f, pos_y-25.f);
	this->direction.x = ( dir_x - pos_x) / (float)distanceFromPlayerToMouse;
	this->direction.y = ( dir_y -pos_y) / (float)distanceFromPlayerToMouse;
	this->shape.setScale(sf::Vector2f(0.3f, 0.3f));
	this->movementSpeed = movement_speed;
	this->bulletDamage = bulletDamage;
}

Bullet::~Bullet()
{
}


const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

float Bullet::getBulletDamage()
{
	return this->bulletDamage;
}


void Bullet::update(float& dtForSpeed)
{
	//Movement
	
	this->shape.move(this->movementSpeed* dtForSpeed * this->direction );
	
	
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
