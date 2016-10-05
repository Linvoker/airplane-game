#include "EnemyLayer.h"
#include "EnemySprite.h"
#include <random>
using namespace cocos2d;

bool EnemyLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	//produce_interval = 1.0f;
	schedule(CC_SCHEDULE_SELECTOR(EnemyLayer::addEnemyPlane), produce_interval);

	return true;
}

void EnemyLayer::addEnemyPlane(float shit) {
	Size winSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	EnemySprite *enemy_sprite = EnemySprite::createWithSpriteFrameName("enemy1.png");
	this->addChild(enemy_sprite);
	enemy_sprite->setPosition(getRandomFloat(0.0f, winSize.width + origin.x), winSize.height + origin.y + enemy_sprite->getContentSize().height / 2);
	//enemy_sprite->setScale(0.5f);

	MoveBy *p_move = MoveBy::create(enemy_sprite->getEnemySpeed(), Point(0, -winSize.height - origin.y - enemy_sprite->getContentSize().height));
	CallFunc *p_callfunc = CallFunc::create([this, enemy_sprite]() {this->removeChild(enemy_sprite, true); });
	Sequence *p_sequence = Sequence::create(p_move, p_callfunc, nullptr);
	enemy_sprite->runAction(p_sequence);

}

float EnemyLayer::getRandomFloat(float x, float y) {
	static std::default_random_engine e1;
	static std::uniform_real_distribution<> dis1(x, y);
	return dis1(e1);
}