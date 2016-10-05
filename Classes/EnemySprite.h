#ifndef _ENEMY_SPRITE_H_
#define  _ENEMY_SPRITE_H_

#include "cocos2d.h"

using namespace cocos2d;

class EnemySprite : public cocos2d::Sprite {
public:
	float getEnemySpeed();
	static EnemySprite *createWithSpriteFrameName(const std::string& sprite_frame_name);
	static EnemySprite* createWithSpriteFrame(SpriteFrame *sprite_frame);
protected:
	EnemySprite();
private:
	float getRandomFloat(float, float);

	float enemy_speed = 1.0f;

};
#endif