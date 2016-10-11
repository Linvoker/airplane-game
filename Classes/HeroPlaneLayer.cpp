//飞机层只做飞机与敌机的碰撞检测，键盘检测
#include "HeroPlaneLayer.h"
#include "HeroPlaneSprite.h"
#include "GameScene.h"
#include "EnemySprite.h"
using namespace cocos2d;

bool HeroPlaneLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	//观察飞机的状态
	NotificationCenter::getInstance()->addObserver(
		this,
		CC_CALLFUNCO_SELECTOR(HeroPlaneLayer::unscheduleAll),
		"gameover",
		nullptr
		);
	NotificationCenter::getInstance()->addObserver(//飞机死一条命，进入复活开始状态，敌机碰撞不到
		this,
		CC_CALLFUNCO_SELECTOR(HeroPlaneLayer::unscheduleDetect),
		"herodead",
		nullptr
		);
	NotificationCenter::getInstance()->addObserver(//飞机死一条命，进入复活结束状态，敌机碰撞检测继续
		this,
		CC_CALLFUNCO_SELECTOR(HeroPlaneLayer::scheduleDetect),
		"heroreboot",
		nullptr
		);
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//初始化飞机位置
	hero_plane_sprite = HeroPlaneSprite::getInstance();
	this->addChild(hero_plane_sprite);
	hero_plane_sprite->setPosition(visibleSize.width / 2 + origin.x, origin.y);

	//加入监听事件
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [this](EventKeyboard::KeyCode key_code, Event *) {
		switch (key_code) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			keyboard_status[2] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			keyboard_status[3] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			keyboard_status[0] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			keyboard_status[1] = 1;
			break;
		default:
			break;
		}
	};
	listener->onKeyReleased = [this](EventKeyboard::KeyCode key_code, Event *) {
		switch (key_code) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			keyboard_status[2] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			keyboard_status[3] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			keyboard_status[0] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			keyboard_status[1] = 0;
			break;
		default:
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();//键盘事件检测
	schedule(CC_SCHEDULE_SELECTOR(HeroPlaneLayer::detectCollision), 0);//碰撞检测，0表示每帧执行
	return true;
}
//键盘检测
void HeroPlaneLayer::update(float delta) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//将飞机的范围限制在可视区域内
	if (hero_plane_sprite->getPositionX() > visibleSize.width + origin.x) {//飞机层的anchor(描点)在屏幕左下方，
		hero_plane_sprite->setPositionX(visibleSize.width + origin.x);
	}
	else if (hero_plane_sprite->getPositionX() < origin.x) {
		hero_plane_sprite->setPositionX(origin.x);
	}
	//将飞机的范围限制在可视区域内
	if (hero_plane_sprite->getPositionY() > visibleSize.height + origin.y) {
		hero_plane_sprite->setPositionY(visibleSize.height + origin.y);
	}
	else if (hero_plane_sprite->getPositionY() < origin.y) {
		hero_plane_sprite->setPositionY(origin.y);
	}
	
	for (int i = 0; i < keyboard_status.size(); i++) {
		if (keyboard_status[i] == 1) {
			movePlaneByKeyboard(i);
			//break;
		}
	}
	
}

void HeroPlaneLayer::movePlaneByKeyboard(int i) {

	float offsetx = 0;
	float offsety = 0;
	switch (i) {
	case 0: 
		offsety = 5;
		break;
	case 1:
		offsety = -5;
		break;
	case 2:
		offsetx = -5;
		break;
	case 3:
		offsetx = 5;
		break;
	default :
		break;
	}
	auto *p_move = MoveTo::create(0.02f, Point(hero_plane_sprite->getPositionX() + offsetx, hero_plane_sprite->getPositionY() + offsety));
	hero_plane_sprite->runAction(p_move);//其实不会等runAction执行完毕再退出，而是先return再慢慢一帧帧执行
}
//敌机与飞机碰撞检测
void HeroPlaneLayer::detectCollision(float shit) {
	Vec2 hero_pos = this->hero_plane_sprite->getPosition();//飞机位置与飞机大小
	Size hero_size = this->hero_plane_sprite->getContentSize();

	//飞机与敌机的碰撞检测
	Vector<Node *> enemy_children = static_cast<GameScene *>(this->getParent())->getEnemyLayer()->getChildren();//这只是一份拷贝，不是引用，不具有实时性
	for (auto enemy_child : enemy_children) {//每帧正在爆炸的敌机也会被列入，因为还没执行removeChild()
		if (static_cast<EnemySprite *>(enemy_child)->isExploding()) {
			continue;//如果该敌机正在爆炸，遍历下一个敌机
		}
		Size enemy_size = enemy_child->getContentSize();
		Vec2 enemy_pos = enemy_child->getPosition();

		//敌机与飞机碰撞
		if (std::abs(enemy_pos.x - hero_pos.x) < (enemy_size.width * enemy_child->getScaleX() + hero_size.width * hero_plane_sprite->getScaleX()) / 2 &&
			 std::abs(enemy_pos.y - hero_pos.y) < (enemy_size.height * enemy_child->getScaleY() + hero_size.width * hero_plane_sprite->getScaleY()) / 2) {
			this->hero_plane_sprite->decreaseHpValBy(static_cast<EnemySprite *>(enemy_child)->getDamageVal());//调用这个之后就不会再进入detectCollision()了。
			static_cast<EnemySprite *>(enemy_child)->killEnemy();//敌机与飞机碰撞一定要被摧毁，否则下一帧，该敌机又与飞机碰撞，这样飞机看起来就只有一条命
			break;//同一帧内与一个敌机碰撞了，就不要再与另一个敌机碰撞。
		}
	}
}

void HeroPlaneLayer::unscheduleAll(Ref *shit) {
	this->unscheduleAllCallbacks();
}

void HeroPlaneLayer::unscheduleDetect(Ref *shit) {
	this->unschedule(CC_SCHEDULE_SELECTOR(HeroPlaneLayer::detectCollision));
}

void HeroPlaneLayer::scheduleDetect(Ref *shit) {
	this->schedule(CC_SCHEDULE_SELECTOR(HeroPlaneLayer::detectCollision), 0);//每帧都执行
}