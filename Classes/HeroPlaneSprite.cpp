#include "HeroPlaneSprite.h"
#include "HeroPlaneLayer.h"
using namespace cocos2d;

static HeroPlaneSprite *hero_plane_sprite = nullptr;

HeroPlaneSprite* HeroPlaneSprite::getInstance() {
	if (!hero_plane_sprite)
	{
		hero_plane_sprite = createWithSpriteFrameName("myPlane.png");
		CCASSERT(hero_plane_sprite, "FATAL: Not enough memory");
	}

	return hero_plane_sprite;
}

int HeroPlaneSprite::getHpVal() {
	return this->hp_val;
}

void HeroPlaneSprite::decreaseHpValBy(int damage) {
	if (this->hp_val <= 0) {
		return;
	}
	this->hp_val -= damage;
	if (this->hp_val <= 0) {
		gameOver();//gameover动画
	}
	else {
		heroPlaneExploded();//爆炸动画+复活动画
	}
	return;
}

HeroPlaneSprite::HeroPlaneSprite() : hp_val(1000) {

}

HeroPlaneSprite *HeroPlaneSprite::createWithSpriteFrameName(const std::string &sprite_frame_name) {

	SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(sprite_frame_name);

	return createWithSpriteFrame(frame);
}

HeroPlaneSprite* HeroPlaneSprite::createWithSpriteFrame(SpriteFrame *sprite_frame)
{
	HeroPlaneSprite *sprite = new (std::nothrow) HeroPlaneSprite();
	if (sprite && sprite_frame && sprite->initWithSpriteFrame(sprite_frame))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void HeroPlaneSprite::heroPlaneExploded() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	CallFunc *p_call1 = CallFunc::create([&]() {NotificationCenter::getInstance()->postNotification("herodead"); });
	Animate *p_animate = Animate::create(AnimationCache::getInstance()->getAnimation("enemy_exploded"));//爆炸动画时，仍然可以键盘监听，但不能做撞击检测了
	CallFunc *p_call2 = CallFunc::create([this,visibleSize, origin]() {//重置sprite图片
		this->initWithSpriteFrameName("myPlane.png"); 
		this->setPosition(visibleSize.width / 2 + origin.x, origin.y); //回到原地
	});
	Blink *p_blink = Blink::create(3.0f, 40);//眨眼动画，这个时候处于无敌状态，敌机撞不到，因为上面post了"herodead"
	//3秒之后进入heroroboot状态，即正常运行
	CallFunc *p_call3 = CallFunc::create([&]() {NotificationCenter::getInstance()->postNotification("heroreboot"); });
	Sequence *p_sequence = Sequence::create(p_call1, p_animate, p_call2, p_blink, p_call3, nullptr);
	this->runAction(p_sequence);
}

void HeroPlaneSprite::gameOver() {
	CallFunc *p_call = CallFunc::create([&]() {NotificationCenter::getInstance()->postNotification("gameover"); });
	Animate *p_animate = Animate::create(AnimationCache::getInstance()->getAnimation("enemy_exploded"));
	Sequence *p_sequence = Sequence::create(p_animate, p_call, nullptr);
	this->runAction(p_sequence);
}
