#include "BonusSprite.h"
#include "BonusLayer.h"
#include "cocos2d.h"

using namespace cocos2d;
BonusSprite *BonusSprite::createWithSpriteFrameNameNum(int num) {
	SpriteFrame *frame;
	if (num == 1) {
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("bulletUpgrade.png");
	}
	else {
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("bigBombGet.png");
	}
	return createWithSpriteFrameNum(frame, num);
}
BonusSprite *BonusSprite::createWithSpriteFrameNum(SpriteFrame*sprite_frame, int num) {
	BonusSprite *bonus_sprite = new (std::nothrow) BonusSprite(num);
	if (bonus_sprite && sprite_frame && bonus_sprite->initWithSpriteFrame(sprite_frame))
	{
		bonus_sprite->autorelease();
		return bonus_sprite;
	}
	CC_SAFE_DELETE(bonus_sprite);
	return nullptr;
}

BonusSprite::BonusSprite(int num) {
	bonus_speed = 3.5f;
	switch (num) {
	case 1:
		bonus_type = BULLET;
		break;
	case 2:
		bonus_type = BIGBOMB;
		break;
	}
}

void BonusSprite::displayAction() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	MoveBy *p_move = MoveBy::create(this->bonus_speed, Point(0, -visibleSize.height - origin.y - this->getContentSize().height));
	CallFunc *p_call = CallFunc::create([this]() {static_cast<BonusLayer *>(this->getParent())->removeChild(this, true); });//true别忘了，否则就内存泄漏了
	Sequence *p_sequence = Sequence::create(p_move, p_call, nullptr);
	this->runAction(p_sequence);
}


