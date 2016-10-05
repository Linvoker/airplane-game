#include "BackgroundButtonLayer.h"
#include "GameScene.h"
using namespace cocos2d;

bool BackgroundButtonLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//创建一个精灵来保存menu的图片用来初始化menuItem
	//Sprite *menu_sprite_default = Sprite::createWithSpriteFrameName("startGameButton.png");
	//Sprite *menu_sprite_selected = Sprite::createWithSpriteFrameName("selectStartButton.png");

	MenuItemSprite *menu_item = 
		MenuItemSprite::create(Sprite::createWithSpriteFrameName("startGameButton.png"), 
			 Sprite::createWithSpriteFrameName("selectStartButton.png"),
				 CC_CALLBACK_0(BackgroundButtonLayer::menuCloseCallback, this));
	Menu *menu_button = Menu::createWithItem(menu_item);

	this->addChild(menu_button, 0);

	menu_button->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 3 + origin.y);
	
	return true;
}
void BackgroundButtonLayer::menuCloseCallback() {
	auto game_scene = GameScene::create();
	Director::getInstance()->replaceScene(game_scene);
	return;
}