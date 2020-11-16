#ifndef ENEMY_H
#define ENEMY_H

#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

class Enemy
{
private:
	
	sf::Sprite sprite;
	std::string name;
	int type;
	float hp;
	float hpMax;
	float damage;
	float points;
	float movementSpeed;
	float biteScore;
	float resistance; // range from 0 - 100 in percentage, if resistance = 100, it will invulnerable;
	bool faceRight;
	
	//Gui & Text
	sf::Font font_superSpace;
	sf::Text hp_text;
	sf::Text name_text;
	sf::Color name_color;

	sf::Texture texture;
	sf::Texture texture_type_1;
	sf::Texture texture_type_2;
	
	//Initiations (there functs should be inside if Enemy() Constructor)
	void initSprite();
	void initTexture(int type = 0);
	void initVariables();
	void initFont();
	void initGui();
	void initHpText(); // (init in initGui() )
	void initNameText(); // (init in initGui() )


public:

	//Enemy(float pos_x, float pos_y);
	Enemy(int type, float pos_x, float pos_y);
	virtual ~Enemy();
	
	void move( float player_pos_x, float player_pos_y , float&dtForSpeed);

	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	int getType() const;
	float enemyHealth();
	float enemyDamage();
	float enemyPoint() const ;
	float enemyBiteScore() const;
	bool lowHealth() const;  

	
	//Modifiers
	void enemiesInjured(float bulletDamage);

	// Updaters
	void updateFaceRight();
	void updateGui(); // Update Gui
	void updateHpText(); // (updating in updateGui() )
	void updateNameText(); // (updating in updateGui() )
	

	//Renderers


	void update();
	void render(sf::RenderTarget& target);



};

#endif