#include "GameBackgroundLayer.h"

using namespace cocos2d;

bool GameBackgroundLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	//auto winSize = Director::getInstance()->getWinSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//第一张背景图片
	game_background_sprite1 = Sprite::createWithSpriteFrameName("img_bg_3.jpg");
	this->addChild(game_background_sprite1, 0);//tag为1的精灵
	//game_background_sprite1->setAnchorPoint(Point(0, 0));//描点默认为图片中点
	game_background_sprite1->setPosition(0, 0);//setposition是sprite描点相对当前layer描点的坐标值
	//game_background_sprite1->setScale(2);

	//第二张背景图片
	game_background_sprite2 = Sprite::createWithSpriteFrameName("img_bg_3.jpg");
	this->addChild(game_background_sprite2, 0);
	//game_background_sprite2->setAnchorPoint(Point(0, 0));
	game_background_sprite2->setPosition(0, game_background_sprite2->getContentSize().height - overlap);//提前减一不会留间隙。。
	
	this->scheduleUpdate();
	return true;
}

void GameBackgroundLayer::update(float delta) {
	auto pos_y1 = game_background_sprite1->getPosition().y;
	auto pos_y2 = game_background_sprite2->getPosition().y;

	float speed = 2.0;
	if (pos_y2 <= speed && pos_y2 > 0) {//因为每次都减speed不可能准确地停留在speed那个点上，所以加一个offset
		float offset = speed - pos_y2;
		game_background_sprite2->setPositionY(pos_y2 - speed);
		game_background_sprite1->setPositionY(game_background_sprite1->getContentSize().height + offset - overlap - speed);//画个图理解一下
	}
	else if (pos_y1 <= speed && pos_y1 > 0) {
		float offset = speed - pos_y1;
		game_background_sprite1->setPositionY(pos_y1 - speed);
		game_background_sprite2->setPositionY(game_background_sprite2->getContentSize().height + offset - overlap - speed);
	}
	else {
		game_background_sprite1->setPositionY(pos_y1 - speed);
		game_background_sprite2->setPositionY(pos_y2 - speed);
	}
	return;
}