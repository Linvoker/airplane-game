#include "EnemySprite.h"
#include "EnemyLayer.h"
#include "MyRandom.h"
#include "GameScene.h"

#include <cstdio>
#include <string>
using namespace cocos2d;

float EnemySprite::getEnemySpeed() {
	return this->enemy_speed;
}

int EnemySprite::getEnemyScore() {
	return this->shooted_score;
}

EnemySprite *EnemySprite::createWithSpriteFrameNameNum(int num) {
	char par_str[15];
	std::sprintf(par_str, "enemy%d.png", num);
	SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(par_str);
	return createWithSpriteFrameNum(frame, num);
}

EnemySprite* EnemySprite::createWithSpriteFrameNum(SpriteFrame *sprite_frame, int num) {
	EnemySprite *enemy_sprite = new (std::nothrow) EnemySprite(num);
	if (enemy_sprite && sprite_frame && enemy_sprite->initWithSpriteFrame(sprite_frame))
	{
		enemy_sprite->autorelease();
		return enemy_sprite;
	}
	CC_SAFE_DELETE(enemy_sprite);
	return nullptr;
}

void EnemySprite::displayAction() {
	Size winSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	switch (enemy_type) {
		//case里不能声明变量，只能外加大括号实现或者全部在switch外声明，后者看起来很乱
	case LEVEL1 ://如果是敌机1则执行以下动作
	{
		MoveBy *p_move = MoveBy::create(this->enemy_speed, Point(0, -winSize.height - origin.y - this->getContentSize().height));
		CallFunc *p_callfunc = CallFunc::create([this]() {static_cast<EnemyLayer *>(this->getParent())->removeChild(this, true); });
		Sequence *p_sequence = Sequence::create(p_move, p_callfunc, nullptr);
		this->runAction(p_sequence);
	}
		break;
	case LEVEL2://如果是敌机2则执行以下动作
	{
		MoveBy *p_move = MoveBy::create(this->enemy_speed, Point(0, (-winSize.height / 2)));
		MoveTo *p_move1 = MoveTo::create(this->enemy_speed, Point(getRandomFloat(0.0f, winSize.width + origin.x), origin.y - this->getContentSize().height / 2));
		CallFunc *p_callfunc = CallFunc::create([this]() {static_cast<EnemyLayer *>(this->getParent())->removeChild(this, true); });
		Sequence *p_sequence = Sequence::create(p_move, p_move1, p_callfunc, nullptr);
		this->runAction(p_sequence);
	}
		break;
	case LEVEL3 ://如果是敌机3则执行以下动作
	{
		//用了贝塞尔曲线
		ccBezierConfig config;
		config.endPosition = Point(this->_position.x, origin.y - this->getContentSize().height);
		config.controlPoint_2 = Point(origin.x, origin.y);
		config.controlPoint_1 = Point(winSize.width + origin.x, winSize.height + origin.y);
		BezierTo *p_bezier = BezierTo::create(enemy_speed, config);
		
		CallFunc *p_callfunc = CallFunc::create([this]() {static_cast<EnemyLayer *>(this->getParent())->removeChild(this, true); });
		Sequence *p_sequence = Sequence::create(p_bezier, p_callfunc, nullptr);
		this->runAction(p_sequence);
	}
		break;
	}
}

void EnemySprite::decreaseHpValBy(int num) {
	if (hp_val <= 0) {//如果敌机HP已经为负值，则返回，如果没有这一句可能会重复执行removeChild()而导致两次释放内存
		return;
	}
	hp_val -= num;
	if (hp_val <= 0) {
		enemyExploded();
	}
}

void EnemySprite::killEnemy() {
	this->hp_val = 0;
	enemyExploded();
}

bool EnemySprite::isExploding() {
	return this->hp_val <= 0;
}

void EnemySprite::enemyExploded() {//执行爆炸动画的同时也在继续displayAction()
	Animate *p_animate = Animate::create(AnimationCache::getInstance()->getAnimation("enemy_exploded"));//爆炸动画
	//通知控制层更新分数并更新显示，传递消息发送的源头this给控制层，为了获取该sprite的shooted_score
	CallFunc *p_call1 = CallFunc::create([&]() {NotificationCenter::getInstance()->postNotification("enemyexploded", this); });
	CallFunc *p_call2 = CallFunc::create([this]() {static_cast<EnemyLayer *>(this->getParent())->removeChild(this, true); });//最后销毁敌机
	Sequence *p_sequence = Sequence::create(p_animate, p_call1, p_call2, nullptr);
	this->runAction(p_sequence);
}

int EnemySprite::getDamageVal() {
	return this->damage_val;
}

EnemySprite::EnemySprite(int num) {
	switch (num) {
	case 1 :
		enemy_type = LEVEL1;
		enemy_speed = 3.0f;
		hp_val = 800;
		shooted_score = 30;
		damage_val = 200;
		break;
	case 2 :
		enemy_type = LEVEL2;
		enemy_speed = 1.6f;
		hp_val = 500;
		shooted_score = 25;
		damage_val = 200;
		break;
	case 3 :
		enemy_type = LEVEL3;
		enemy_speed = 3.0f;
		hp_val = 400;
		shooted_score = 15;
		damage_val = 100;
		break;
	}
}
