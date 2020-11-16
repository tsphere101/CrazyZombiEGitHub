#include "Enemy.h"

void Enemy::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.setOrigin(50.f, 60.f);
	//Resize
	this->sprite.scale(0.25f, 0.25f);
	this->faceRight = true;

}

void Enemy::initTexture(int type)
{
	switch (type)
	{
	case 0:
	{
		if (!this->texture.loadFromFile("textures/Zombie.png"))
		{
			std::cout << "ERROR::PLAYER::INITTEXTURE:: Cound not load texture file\n";
		}
		break;
	}
	case 1:
		if (!this->texture.loadFromFile(/*texture_type_1*/"textures/Zombie.png"))
		{
			std::cout << "ERROR::PLAYER::INITTEXTURE:: Cound not load texture file\n";
		}
		break;
	case 2:
		if (!this->texture.loadFromFile(/*texture_type_2*/"textures/Zombie.png"))
		{
			std::cout << "ERROR::PLAYER::INITTEXTURE:: Cound not load texture file\n";
		}
		break;
	default:
		break;
	}
}

void Enemy::initVariables()
{
	this->name = "Zombie";
	this->type = 0;
	this->hpMax = 20;
	this->hp = this->hpMax;
	this->damage = 3;
	this->biteScore = 2;
	this->points = 5;
	this->movementSpeed = (float)(1.0 + (rand() %10 ) / 10.0);
}

void Enemy::initFont()
{
	if (!this->font_superSpace.loadFromFile("fonts/Superspace.ttf"))
	{
		std::cout << "ENEMY::INITFONT:: Could not load file : Fonts/superSpace.tff" << std::endl;
	}
}

void Enemy::initGui()
{
	this->initHpText();
	this->initNameText();
}

void Enemy::initHpText()
{
	this->hp_text.setFont(font_superSpace);
	this->hp_text.setString("NONE");
	this->hp_text.setCharacterSize(24);
	this->hp_text.setFillColor(sf::Color::Magenta);
	//this->hp_text.setPosition(100.f, 200.f);
}

void Enemy::initNameText()
{
	this->name_text.setFont(font_superSpace);
	this->name_text.setString("NONE");
	this->name_text.setCharacterSize(24);
	this->name_text.setFillColor(name_color);
	//this->hp_text.setPosition(100.f, 200.f);
}
/*
Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->sprite.setPosition(pos_x, pos_y);
	this->initFont();
	this->initGui();
	
}
*/
Enemy::Enemy(int type, float pos_x, float pos_y)
{
	this->initFont();
	this->initGui();
	switch (type)
	{
	case 0:
	{
		this->type = 0;
		this->name = "Zombie";
		this->hpMax = 20;
		this->hp = this->hpMax;
		this->resistance = 0;
		this->damage = 3;
		this->biteScore = 2;
		this->points = 4;
		this->movementSpeed = (float)(1.0 + (rand() % 10) / 10.0);
		this->initTexture(0); // Choose Texture
		this->name_color = sf::Color::Red;
		break;
	}
	case 1:
	{
		this->type = 1;
		this->name = "Fast Runner";
		this->hpMax = 15;
		this->hp = this->hpMax;
		this->resistance = 0;
		this->damage = 2;
		this->biteScore = 2;
		this->points = 7;
		this->movementSpeed = (float)(4.0 + (rand() % 3) / 10.0);
		this->initTexture(0); // Choose Texture
		this->name_color = sf::Color(0,255,255); // Aqua blue
		break;
	}
	case 2:
	{
		this->type = 2;
		this->name = "Tank Zombie";
		this->hpMax = 250;
		this->hp = this->hpMax;
		this->resistance = 20;
		this->damage = 8;
		this->biteScore = 4;
		this->points = 18;
		this->movementSpeed = (float)(0.5 + (rand() % 3) / 10.0);
		this->initTexture(0); // Choose Texture
		this->name_color = sf::Color(255, 215, 0); // Yellow Gold
		break;
	}

	default:
		break;
	}
	this->initSprite();
	this->sprite.setPosition(pos_x, pos_y);

}

Enemy::~Enemy()
{

}

const sf::FloatRect Enemy::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

int Enemy::getType() const
{
	return this->type;
}

void Enemy::move( float player_pos_x, float player_pos_y ,float& dtForSpeed)
{
	float pos_x = this->sprite.getPosition().x;
	float pos_y = this->sprite.getPosition().y;

	float Distance = sqrt( (player_pos_x - pos_x) * (player_pos_x - pos_x) + (player_pos_y - pos_y) * (player_pos_y - pos_y) );


	float dir_x = (player_pos_x - pos_x) / Distance;
	float dir_y = (player_pos_y - pos_y) / Distance;

	if (dir_x > 0) this->faceRight = true;
	else this->faceRight = false;

	sprite.move(dir_x*this->movementSpeed * dtForSpeed, dir_y * this->movementSpeed * dtForSpeed);
}

void Enemy::updateFaceRight()
{
	if (this->faceRight)
	{
		this->sprite.setScale(abs(this->sprite.getScale().x), this->sprite.getScale().y);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else
	{
		this->sprite.setScale(-abs(this->sprite.getScale().x), this->sprite.getScale().y);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / abs(this->sprite.getScale().x), 0.f);

	}

}

void Enemy::updateGui()
{
	this->updateHpText();
	this->updateNameText();
}

void Enemy::updateHpText()
{
	if (this->lowHealth()) //if enemimes hp is low
	{
		this->hp_text.setFillColor(sf::Color::Red);
	}
	else this->hp_text.setFillColor(sf::Color::Magenta);

	float centre_of_width_pos = this->getBounds().left + 20.f;
	float below_pos = this->getBounds().top + this->getBounds().height + 15.f;
	this->hp_text.setPosition(centre_of_width_pos, below_pos);
	std::stringstream _text;
	_text << "HP : " << this->hp;

	this->hp_text.setString(_text.str());

}

void Enemy::updateNameText()
{
	this->name_text.setFillColor(name_color);
	this->name_text.setPosition(this->getBounds().left + 20.f, this->getBounds().top -15);
	std::stringstream _text;
	_text << this->name;
	this->name_text.setString(_text.str());
}

const sf::Vector2f& Enemy::getPos() const
{
	return this->sprite.getPosition();
}

float Enemy::enemyHealth()
{
	return this->hp;
}

float Enemy::enemyDamage()
{
	return this->damage;
}

float Enemy::enemyPoint() const
{
	return this->points;
}

float Enemy::enemyBiteScore() const
{
	return this->biteScore;
}

bool Enemy::lowHealth() const
{
	//Check if enemy health is low
	if ((this->hp / this->hpMax) < 0.5f) // if hp is lower than 50%
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::enemiesInjured(float bulletDamage)
{
	this->hp -= bulletDamage - (bulletDamage* (this->resistance / 100.f)) ;
}



void Enemy::update()
{
	this->updateFaceRight();
	this->updateGui();
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	target.draw(this->hp_text);
	target.draw(this->name_text);
}
