#include "Player.h"



void Player::initVariables()
{
	
	this->movementSpeed = 2.f;
	this->acceleration = 4.f;
	this->deacceleration = 4.f;
	this->velocityMax = 100.f;
	this->velocity.x = 0;
	this->velocity.y = 0;
	this->PlayerHpMax = 20;
	this->PlayerHp = this->PlayerHpMax;
	this->resistance = 0;
	this->attack_bullet_damage = 4;
	this->attack_bullet_speed = 5;
	this->attackCoolDownMax = 0.2f;
	this->attackCoolDown = this->elpsTime;
	this->resistanceCoolDownMax = 5.f; // Resistance cooldown
	this->resistanceCoolDown = this->elpsTime;
	this->vulnerableCooldownMax = 1.f;
	this->vulnerableCooldown = this->vulnerableCooldownMax;
	this->vulnerability = true;
	this->score = 0;
	this->enemiesKilled = 0;
}

void Player::initShape()
{
	
}

void Player::initTexture()
{
	//Load a texture frome file
	if (!this->texture.loadFromFile("textures/Chompea.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE:: Cound not load texture file\n";
	}
}

void Player::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setPosition(500.f, 500.f);
	this->sprite.setTexture(this->texture);
	this->sprite.setOrigin(0.f, 0.f);
	//Resize
	this->sprite.scale(0.05f, 0.05f);
	this->faceRight = true;
}




void Player::updateFaceRight()
{
	if (this->mousePos.x - this->sprite.getPosition().x > 0) faceRight = true;
	else faceRight = false;

	if (faceRight)
	{
		this->sprite.setScale(abs(this->sprite.getScale().x), this->sprite.getScale().y);
		this->sprite.setOrigin(0.f , 0.f);
	}
	else
	{
		this->sprite.setScale(-abs(this->sprite.getScale().x), this->sprite.getScale().y);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / abs(this->sprite.getScale().x), 0.f);
	}
}




void Player::updateAttackCooldown()
{
	this->attackCoolDown = this->elpsTime;
}

void Player::updateResistanceCooldown()
{
	// if you want to trigger the cooldown, set the cooldown to elps time
	if ((this->elpsTime - this->resistanceCoolDown) > this->resistanceCoolDownMax)
	// if cool down ends
	{
		this->setResistance(0);
		
	}
}

void Player::useItem(int item_id, float effect_amount)
{
	switch (item_id)
	{
	case 0: 
	{
		this->givePlayerHp(effect_amount);
		break;
	}
	case 1:
	{
		this->givePlayerHp(effect_amount);
		break;
	}
	case 2:
	{
		this->setResistance(effect_amount);
		break;
	}
	default:
		break;
	}
}

void Player::updateHP()
{
	//Checking if player has overload hp
	if (this->PlayerHp > this->PlayerHpMax)
	{
		this->PlayerHp = this->PlayerHpMax;
	}

	if (this->PlayerHp < 0)
	{
		this->PlayerHp = 0;
	}

}

void Player::updateVulnerability()
{
	if (this->elpsTime - this->vulnerableCooldown > this->vulnerableCooldownMax)
	{
		this->vulnerability = true;
	}
	else this->vulnerability = false; // Unable to be attacked
	
}

void Player::get_hurt(float value, float biteScore)
{
	if (this->vulnerability) 
	{
		//this->PlayerHp -= value;
		this->cutPlayerHp(value);
		this->giveScore(-biteScore);
		this->vulnerability = false;
		this->vulnerableCooldown = this->elpsTime;
	}
}

const bool Player::canAttack()
{
	if (this->elpsTime - this->attackCoolDown >= this->attackCoolDownMax)
	{
		this->attackCoolDown = this->elpsTime;
		return true;
	}
	else return false;
}

void Player::move(const float dir_x, const float dir_y, float& dtForSpeed)
{
	//Acceleration
	
	if (dir_x > 0) //RIGHT
	{
		this->velocity.x += this->acceleration * dir_x;
		if (this->velocity.x > velocityMax)
			this->velocity.x = velocityMax;
	}
	if (dir_x < 0) //LEFT
	{
		this->velocity.x += this->acceleration * dir_x;
		if (this->velocity.x < -abs(this->velocityMax))
			this->velocity.x = -abs(this->velocityMax);
	}
	if (dir_y < 0) // UP
	{
		this->velocity.y += this->acceleration * dir_y;
		if (this->velocity.y < -abs(this->velocityMax))
			this->velocity.y = -abs(this->velocityMax);
	}
	if (dir_y > 0) //DOWN
	{
		this->velocity.y += this->acceleration * dir_y;
		if (this->velocity.y > this->velocityMax)
			this->velocity.y = this->velocityMax;
	}

	this->sprite.move(this->movementSpeed * dir_x * dtForSpeed, this->movementSpeed * dir_y * dtForSpeed);
	

}

void Player::movementComponent()
{
	//Deacceleration
	if (this->velocity.x > 0.f) // RIGHT
	{
		this->velocity.x -= this->deacceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}

	 if (this->velocity.x < 0.f) //LEFT
	{
		this->velocity.x += this->deacceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0;
	}

	if (this->velocity.y < 0) //UP
	{
		this->velocity.y += this->deacceleration;
		if (this->velocity.y > 0)
			this->velocity.y = 0;
	}
	 if (this->velocity.y > 0) //DOWN
	{
		this->velocity.y -= this->deacceleration;
		if (this->velocity.y < 0)
			this->velocity.y = 0;
	}
}

Player::Player(float pos_x, float pos_y)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->setSpawnPosition(pos_x, pos_y);
}
Player::~Player()
{
	this->initTexture();
	this->initSprite();
}

void Player::updateElpsTime(float& value)
{
	this->elpsTime = value;
}



void Player::getMousePosWindow(float x, float y)
{
	this->mousePos.x = x;
	this->mousePos.y = y;
}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

float Player::getPlayerHp() const
{
	return this->PlayerHp;
}

float Player::getPlayerHpMax() const 
{
	return this->PlayerHpMax;
}

float Player::getPlayerMovementSpeed() const
{
	return this->movementSpeed;
}

float Player::getAttackCooldown() const
{
	return this->attackCoolDown;
}

float Player::getAttackCooldownMax() const
{
	return this->attackCoolDownMax;
}

float Player::getElpsTime() const
{
	return this->elpsTime;
}

bool Player::getVulnerability() const
{
	return this->vulnerability;
}

float Player::getScore() const
{
	return this->score;
}

float Player::getSurvivedTime() const
{
	return this->elpsTime;
}

float Player::getEnemmiesKilled() const
{
	return this->enemiesKilled;
}

bool Player::lowHealth() const
{
	//Check if player health is low or not

	if (this->PlayerHp / this->PlayerHpMax < 0.5f) // if player health is lower than 50% will return true
	{
		return true;
	}
	else  // the player's health isn't low
		return false;
}

float Player::getResistance() const
{
	return this->resistance;
}

const sf::Vector2f& Player::getSpawnPos() const
{
	return this->spawn_position;
}

const float Player::getAttackBulletDamage() const
{
	return this->attack_bullet_damage;
}

const float Player::getAttackBulletSpeed() const
{
	return this->attack_bullet_speed;
}

void Player::setPos(float x, float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setPlayerHp(float value)
{
	this->PlayerHp = value;
}

void Player::setplayerHpMax(float value)
{
	this->PlayerHpMax = value;
}

void Player::givePlayerHp(float value)
{
	this->PlayerHp += value;
}

void Player::cutPlayerHp(float value)
{
	this->PlayerHp -= value - (value * (this->resistance / 100.f));
}

void Player::setPlayerMovementSpeed(float value)
{
	this->movementSpeed = value;
}

void Player::setVulnerability(bool value)
{
	this->vulnerability = value;
}

void Player::setScore(float value)
{
	this->score = value;
}

void Player::giveScore(float value)
{
	this->score += value;
}

void Player::giveEnemiesKilled(float value)
{
	this->enemiesKilled += value;
}

void Player::addResistance(float value)
{
	this->resistance += value;
}

void Player::setResistance(float value)
{
	this->resistance = value;
}

void Player::setSpawnPosition(float pos_x, float pos_y)
{
	this->spawn_position.x = pos_x;
	this->spawn_position.y = pos_y;
}

void Player::setAttackBulletDamage(float value)
{
	this->attack_bullet_damage = value;
}

void Player::setAttackBulletSpeed(float value)
{
	this->attack_bullet_speed = value;
}

void Player::setResistanceCoolDown(float value)
{
	this->resistanceCoolDown = value;
}

void Player::updateInput()
{

	
}

void Player::update()
{
	
	this->updateInput();
	this->updateFaceRight();
	this->movementComponent();
	this->updateVulnerability();
	this->updateResistanceCooldown();
	this->updateHP();
	



}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	sf::CircleShape circ;
	circ.setFillColor(sf::Color::Red);
	circ.setRadius(3.f);
	circ.setPosition(this->sprite.getPosition());

	target.draw(circ);
}