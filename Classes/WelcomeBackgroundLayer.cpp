#include "WelcomeBackgroundLayer.h"
//#include "SimpleAudioEngine.h"

using namespace cocos2d;

bool WelcomeBackgroundLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//从缓存中取出一张名为"img_bg_welcome.jpg"的背景图片
	//缓存在AppDelegate::applicationDidFinishLaunching()里已经建立
	//SpriteFrame *background_frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("img_bg_1.png");
	Sprite *background_sprite = Sprite::createWithSpriteFrameName("img_bg_welcome.jpg");//创建一个背景精灵用来显示背景图片
	
	//background_sprite->setParent(this);
	this->addChild(background_sprite, 0);
	
	background_sprite->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	return true;

}

