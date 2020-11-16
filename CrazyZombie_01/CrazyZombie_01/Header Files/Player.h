#ifndef PLAYER_H
#define PLAYER_H

#include "State.h"

class Player
{
private:
	/////////////
	//Variables//
	/////////////

	//Essentials
	float elpsTime;
	
	//Player properties
	float PlayerHp;
	float PlayerHpMax;
	float movementSpeed;
	float resistance; // range from 0 - 100, if resistance = 100 will be invulnerable if more than 100 will get hp instread of damage
	float attack_bullet_damage;
	float attack_bullet_speed;

	//Cooldown System Variables
	float attackCoolDown;
	float attackCoolDownMax;
	float vulnerableCooldown;
	float vulnerableCooldownMax;
	float resistanceCoolDown;
	float resistanceCoolDownMax;

	bool vulnerability;

	//Sprite
	sf::Sprite sprite;
	bool faceRight;
	sf::Texture	texture;
	
	//Movement & Positions
	float velocityMax;
	float deacceleration;
	float acceleration;
	sf::Vector2f velocity;
	sf::Vector2f direction;
	sf::Vector2f spawn_position;


	//Scores Variables
	float score;
	float survivedTime;
	float enemiesKilled;

	//Mouse
	sf::Vector2f mousePos;
	

	

	//Functions
	void initVariables();
	void initShape();
	void initTexture();
	void initSprite();
	
	
	
public:
	Player(float pos_x, float pos_y);
	virtual ~Player();

	

	//Accessor
	
	void getMousePosWindow(float x, float y);
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	float getPlayerHp() const ;
	float getPlayerHpMax() const ;
	float getPlayerMovementSpeed() const ;
	float getAttackCooldown() const;
	float getAttackCooldownMax()const;
	float getElpsTime() const;
	bool getVulnerability() const;
	float getScore() const;
	float getSurvivedTime() const;
	float getEnemmiesKilled() const;
	bool lowHealth() const;
	float getResistance() const;
	const sf::Vector2f& getSpawnPos() const;
	const float getAttackBulletDamage() const;
	const float getAttackBulletSpeed() const;

	//Modifiers
	void setPos(float x, float y);
	void setPlayerHp(float value);
	void setplayerHpMax(float value);
	void givePlayerHp(float value);
	void cutPlayerHp(float value);
	void setPlayerMovementSpeed(float value);
	void setVulnerability(bool value);
	void setScore(float value);
	void giveScore(float value);
	void giveEnemiesKilled(float value);
	void addResistance(float value);
	void setResistance(float value);
	void setSpawnPosition(float pos_x = 500.f, float pos_y = 500.f);
	void setAttackBulletDamage(float value);
	void setAttackBulletSpeed(float value);
	void setResistanceCoolDown(float value);

	//Functions
	
	void updateElpsTime(float& elpsTime);
	void updateFaceRight();
	void updateAttackCooldown();
	void updateResistanceCooldown();

	void useItem(int item_id, float effect_amount);
	void updateHP();
	/*regener();*/
	void updateVulnerability();
	void get_hurt(float value, float biteScore);
	const bool canAttack();
	void move(const float dir_x, const float dir_y, float& dtForSpeed);
	void movementComponent();
	void updateInput();
	void update();
	void render(sf::RenderTarget& target);

	
};



#endif 

