#ifndef _BONUS_SPRITE_H_
#define _BONUS_SPRITE_H_

#include <string>
#include "cocos2d.h"

using namespace cocos2d;

class BonusSprite : public cocos2d::Sprite {
public:
	static BonusSprite *createWithSpriteFrameNameNum(int num);
	static BonusSprite *createWithSpriteFrameNum(SpriteFrame*sprite_frame, int num);
	void displayAction();

	enum BonusType {
		BULLET,
		BIGBOMB,
	} bonus_type;
private:
	BonusSprite(int num);

	float bonus_speed;
};
#endif
