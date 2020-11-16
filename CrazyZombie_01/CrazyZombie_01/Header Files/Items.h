#ifndef ITEMS_H
#define ITEMS_H

#include "State.h"

class Items
{
private:
	
	//Object & Resouce 
	sf::RectangleShape sprite;
	sf::Texture sprite_texture;
	std::string sprite_dir;
	
	//Font & text
	sf::Font font_superSpace;
	sf::Text item_name_text;


	// Item id & Name
	int item_id;
	std::string item_name;
	
	// Properties
	float heal;
	float resistance;
	float speed_boost;
	
	//Spawning and Pickeup effect
	sf::Vector2f pos;

	//weapons
	//add hp bar

	


	//Initiations
	void initVariables();
	void initSprite();




public:
	Items(int item_id , int second_parameter, float pos_x = 0, float pos_y = 0);
	virtual ~Items();

	//Functions
	void item_spawned(); // makeing effects or something
	void item_picked_up(); // dispaly what player picked up
	
	//add_hpBar();

	//Accessor
	float getHealValue() const;
	float getResistanceValue() const;
	float getSpeed_BoostValue() const;
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int getItemID() const;
	const float getItemEffect() const;
	
	//Modifiers
	





	//updaters & renderers




	void update();
	void render(sf::RenderTarget& target);


};
#endif // !ITEMS_H
