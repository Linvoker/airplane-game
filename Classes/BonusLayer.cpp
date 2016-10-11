//在bonus层做与飞机的碰撞检测，这样postnotification时可以将消息来源传递出去，然后判断是bonus类型
#include "BonusLayer.h"
#include "MyRandom.h"
#include "BonusSprite.h"
#include "HeroPlaneSprite.h"
#include "cocos2d.h"

#include <memory>
#include <cmath>

using namespace cocos2d;

bool BonusLayer::init() {
	NotificationCenter::getInstance()->addObserver(
		this,
		CC_CALLFUNCO_SELECTOR(BonusLayer::addBonusSprite),
		"producebonus",
		nullptr
		);

	scheduleUpdate();

	return true;
}

void BonusLayer::addBonusSprite(Ref *shit) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	BonusSprite * bonus_sprite = BonusSprite::createWithSpriteFrameNameNum(getRandomInt(1, 2));
	this->addChild(bonus_sprite);
	bonus_sprite->setPosition(getRandomFloat(0.0f, visibleSize.width + origin.x), 
		 visibleSize.height + origin.y + bonus_sprite->getContentSize().height / 2);
	bonus_sprite->displayAction();
}

//飞机与bonus的碰撞检测
void BonusLayer::update(float shit) {
	Vector<Node *> bonus_cur = this->getChildren();//当前bonus的结点
	if (bonus_cur.empty()) {//bonus没产生 为空就别检测了
		return;
	}

	HeroPlaneSprite *hero_plane_sprite = HeroPlaneSprite::getInstance();
	Vec2 hero_plane_pos = hero_plane_sprite->getPosition();
	Size hero_plane_size = hero_plane_sprite->getContentSize();

	for (auto bonus_sprite : bonus_cur) {
		Vec2 bonus_pos = bonus_sprite->getPosition();
		Size bonus_size = bonus_sprite->getContentSize();

		if (std::abs(bonus_pos.x - hero_plane_pos.x) * 2 <= bonus_size.width * hero_plane_sprite->getScaleX() + 
			 hero_plane_size.width * hero_plane_sprite->getScaleX() &&
				 std::abs(bonus_pos.y - hero_plane_pos.y) * 2 <= bonus_size.height * hero_plane_sprite->getScaleY() + 
					 hero_plane_size.height * hero_plane_sprite->getScaleY()) {
			if (static_cast<BonusSprite *>(bonus_sprite)->bonus_type == BonusSprite::BonusType::BULLET) {
				NotificationCenter::getInstance()->postNotification("bonusget-to-bulletlayer");
			}
			else {
				NotificationCenter::getInstance()->postNotification("bonusget-to-enemylayer");
			}
			bonus_sprite->stopAllActions();
			this->removeChild(bonus_sprite, true);
		}
	}
}