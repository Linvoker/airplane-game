#ifndef _HERO_PLANE_SPRITE_H_
#define _HERO_PLANE_SPRITE_H_

#include <string>
#include "cocos2d.h"

using namespace cocos2d;

class HeroPlaneSprite : public cocos2d::Sprite {
public:
	static HeroPlaneSprite* getInstance();//因为飞机只有一架所以用单例模式
	void decreaseHpValBy(int damage);
	int getHpVal();
protected:
	HeroPlaneSprite();
private:
	static HeroPlaneSprite *createWithSpriteFrameName(const std::string &sprite_frame_name);//别让外部直接调用
	static HeroPlaneSprite *createWithSpriteFrame(SpriteFrame *sprite_frame);
	void heroPlaneExploded();
	void gameOver();

	int hp_val;
	//static HeroPlaneSprite *hero_plane_spite;
};

#endif
