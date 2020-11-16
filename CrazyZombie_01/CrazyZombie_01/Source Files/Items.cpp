#include "Items.h"

void Items::initVariables()
{
	
}

void Items::initSprite()
{
	if (!this->sprite_texture.loadFromFile(this->sprite_dir))
	{
		std::cout << "ITEMS::INITSPRITE:: Could not load texture" << std::endl;
	}
	this->sprite.setTexture(&sprite_texture);
	this->sprite.setSize(sf::Vector2f(30.f, 30.f));
	this->sprite.setPosition(pos);

}

Items::Items(int id, int second_parameter, float pos_x , float pos_y)
{
	switch (id)
	{

	case 0:
	{
		//VOID
		this->item_id = 0;
		this->item_name = "VOID";
		this->heal = 50;
		this->resistance = 0;
		this->speed_boost = 0;
		this->sprite_dir = "textures/item_void.png";
		break;
	}

	case 1:
	{
		//Heal
		this->item_id = 1;
		this->item_name = "Heal";
		this->resistance = 0;
		this->speed_boost = 0;
		switch (second_parameter)
		{
		case 0:
		{
			// Items(1,0);
			this->heal = 2;
			this->sprite_dir = "textures/item_heal_0.png";
			break;
		}
		case 1:
		{
			this->heal = 5;
			this->sprite_dir = "textures/item_heal_1.png";
			break;
		}
		case 2:
		{
			this->heal = 20;
			this->sprite_dir = "textures/item_heal_2.png";
			break;
		}
		default:
			break;
		}
		
		break;
	}

	case 2:
	{
		//Resistance
		this->item_id = 2;
		this->item_name = "Resistance";
		this->heal = 0;
		this->resistance = 20.f; // 30% resistance
		this->speed_boost = 0;
		this->sprite_dir = "textures/item_void.png";
		break;
	}

	case 3:
	{
		//Speed Boost
		break;
	}

	default:
		break;
	}
	this->pos.x = pos_x;
	this->pos.y = pos_y;
	this->initSprite();
	this->item_spawned();
}



Items::~Items()
{
}

void Items::item_spawned()
{
}

void Items::item_picked_up()
{
}

float Items::getHealValue() const
{
	return this->heal;
}

float Items::getResistanceValue() const
{
	return this->resistance;
}

float Items::getSpeed_BoostValue() const
{
	return this->speed_boost;
}

const sf::Vector2f& Items::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Items::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int Items::getItemID() const
{
	return this->item_id;
}

const float Items::getItemEffect() const
{
	switch (this->item_id)
	{
	case 0:
	{
		return this->heal; // return VOID effect, testing for HP;
		break;
	}
	case 1:
	{
		return this->heal;
		break;
	}
	case 2:
	{
		return this->resistance;
		break;
	}
	default:
		break;
	}
}

void Items::update()
{
}

void Items::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

