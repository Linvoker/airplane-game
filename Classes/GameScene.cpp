#include "GameScene.h"
#include "GameBackgroundLayer.h"
#include "HeroPlaneLayer.h"
#include "BulletLayer.h"
using namespace cocos2d;

bool GameScene::init() {
	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//先创建无限滚动的地图层，再创建飞机层，子弹层，敌机层
	this->game_background_layer = GameBackgroundLayer::create();
	this->addChild(game_background_layer, 0);
	//背景层以屏幕正中央为描点
	this->game_background_layer->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	this->hero_plane_layer = HeroPlaneLayer::create();
	this->addChild(hero_plane_layer, 1);
	//飞机层以屏幕左下方为描点
	this->hero_plane_layer->setPosition(origin.x, origin.y);

	this->bullet_layer = BulletLayer::create();
	this->addChild(bullet_layer, 1);
	//子弹层以屏幕左下方为描点
	this->bullet_layer->setPosition(origin.x, origin.y);

	//敌机层
	this->enemy_layer = EnemyLayer::create();
	this->addChild(enemy_layer, 1);
	this->enemy_layer->setPosition(origin.x, origin.y);

	return true;
}

GameBackgroundLayer *GameScene::getGameBackgroundLayer() {
	return this->game_background_layer;
}
HeroPlaneLayer *GameScene::getHeroPlaneLayer() {
	return this->hero_plane_layer;
}
BulletLayer *GameScene::getBulletLayer() {
	return this->bullet_layer;
}