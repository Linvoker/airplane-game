#include "EnemySprite.h"
#include <random>
using namespace cocos2d;

float EnemySprite::getEnemySpeed() {
	return this->enemy_speed;
}

EnemySprite *EnemySprite::createWithSpriteFrameName(const std::string& sprite_frame_name) {
	SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(sprite_frame_name);
	return createWithSpriteFrame(frame);
}

EnemySprite* EnemySprite::createWithSpriteFrame(SpriteFrame *sprite_frame) {
	EnemySprite *enemy_sprite = new (std::nothrow) EnemySprite();
	if (enemy_sprite && sprite_frame && enemy_sprite->initWithSpriteFrame(sprite_frame))
	{
		enemy_sprite->autorelease();
		return enemy_sprite;
	}
	CC_SAFE_DELETE(enemy_sprite);
	return nullptr;
}

EnemySprite::EnemySprite() {
	enemy_speed = getRandomFloat(2.0f, 4.0f);
}

float EnemySprite::getRandomFloat(float x, float y) {
	static std::default_random_engine e;
	static std::uniform_real_distribution<> dis(x, y);
	return dis(e);
}