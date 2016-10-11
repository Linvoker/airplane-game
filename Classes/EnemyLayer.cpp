//敌机层只有敌机和子弹的碰撞检测和产生敌机
#include "EnemyLayer.h"
#include "EnemySprite.h"
#include "GameScene.h"
#include "MyRandom.h"
#include "HeroPlaneSprite.h"
#include <cmath>
using namespace cocos2d;

bool EnemyLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	//只有游戏结束才会停止产生敌机、敌机与子弹碰撞检测,所以只需要观察一个状态即可
	NotificationCenter::getInstance()->addObserver(
		this, 
		CC_CALLFUNCO_SELECTOR(EnemyLayer::unscheduleAll),
		"gameover",
		nullptr
		);

	NotificationCenter::getInstance()->addObserver(
		this,
		CC_CALLFUNCO_SELECTOR(EnemyLayer::killAllEnemyBonus),
		"bonusget-to-enemylayer",
		nullptr);

	schedule(CC_SCHEDULE_SELECTOR(EnemyLayer::addEnemyPlane), produce_interval);//定时器，间隔produce_interval时间产生敌机
	scheduleUpdate();//定时器，每帧做子弹和敌机的碰撞检测，
	return true;
}

//定时器，间隔produce_interval时间产生敌机
void EnemyLayer::addEnemyPlane(float shit) {
	Size winSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	EnemySprite *enemy_sprite = EnemySprite::createWithSpriteFrameNameNum(getRandomInt(1, 3));//通过随机序号来创建不同的敌机类型
	this->addChild(enemy_sprite);
	enemy_sprite->setPosition(getRandomFloat(0.0f, winSize.width + origin.x), winSize.height + origin.y + enemy_sprite->getContentSize().height / 2);
	enemy_sprite->setScale(0.5f);

	enemy_sprite->displayAction();
	
}

//定时器，每帧做子弹和敌机的碰撞检测，
void EnemyLayer::update(float shit) {
	//取出bullet_layer，避免后面重复解引用
	BulletLayer *bullet_layer = static_cast<GameScene *>(this->getParent())->getBulletLayer();
	
	Size bullet_size = bullet_layer->getBulletSize();//static_cast可以表现多态也可以不表现多态（无需函数）
	int bullet_damage = bullet_layer->getDamageVal();

	Vector<Node *> enemy_children = this->getChildren();//这只是一份拷贝，不是引用，不具有实时性
	//子弹和敌机碰撞检测
	for (auto enemy_child : enemy_children) {//每帧正在爆炸的敌机也会被列入，因为还没执行removeChild()
		if (static_cast<EnemySprite *>(enemy_child)->isExploding()) {
			continue;//如果该敌机正在爆炸，遍历下一个敌机
		}

		Size enemy_size = enemy_child->getContentSize();
		Vec2 enemy_pos = enemy_child->getPosition();

		//每次遍历子弹时更新bullet_children的值，因为每遍历一家敌机，有些子弹可能已经被销毁了
		Vector<Node *> bullet_children = bullet_layer->getChildren();//这只是一份拷贝，不是引用，不具有实时性
		for (auto bullet_child : bullet_children) {
			Vec2 bullet_pos = bullet_child->getPosition();
			if (std::abs(enemy_pos.x - bullet_pos.x) < (enemy_size.width * enemy_child->getScaleX() + bullet_size.width) / 2 &&
				 std::abs(enemy_pos.y - bullet_pos.y) < (enemy_size.height * enemy_child->getScaleY() + bullet_size.height) / 2) {
				//只要子弹和敌机的距离很小，子弹就一定销毁
				bullet_layer->removeChild(bullet_child, true);//直接destroyBullet,子弹不用演示销毁动画
																									 
				static_cast<EnemySprite *>(enemy_child)->decreaseHpValBy(bullet_damage);//敌机未必会执行爆炸动画并销毁，但一定会降低血量
				if (static_cast<EnemySprite *>(enemy_child)->isExploding()) {
					break;//如果该敌机正在执行爆炸，则跳出子弹的循环，因为后续子弹不可能再击中该爆炸动画的敌机了
				}
			}
		}
		
	}
}
void EnemyLayer::unscheduleAll(Ref* shit) {
	this->unscheduleAllCallbacks();
}

void EnemyLayer::killAllEnemyBonus(Ref *shit) {
	for (auto enemy_child : this->getChildren()) {
		static_cast<EnemySprite *>(enemy_child)->killEnemy();
	}
}