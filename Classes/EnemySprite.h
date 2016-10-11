#ifndef _ENEMY_SPRITE_H_
#define  _ENEMY_SPRITE_H_

#include "cocos2d.h"

using namespace cocos2d;

class EnemySprite : public cocos2d::Sprite {
public:
	float getEnemySpeed();
	int getEnemyScore();
	static EnemySprite *createWithSpriteFrameNameNum(int num);
	static EnemySprite* createWithSpriteFrameNum(SpriteFrame *sprite_frame, int num);
	void displayAction();
	void decreaseHpValBy(int);
	void killEnemy();
	bool isExploding();
	void enemyExploded();
	int getDamageVal();
protected:
	EnemySprite(int num);
private:

	enum EnemyType {
		LEVEL1,
		LEVEL2,
		LEVEL3,
	} enemy_type;
	float enemy_speed;
	int hp_val;
	int shooted_score;
	int damage_val;
};
#endif