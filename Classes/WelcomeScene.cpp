#include "WelcomeScene.h"
#include "WelcomeBackgroundLayer.h"
#include "BackgroundButtonLayer.h"
using namespace cocos2d;

bool WelcomeScene::init() {
	if (!Scene::init()) {
		return false;
	}

	auto backgroud_layer = WelcomeBackgroundLayer::create();
	this->addChild(backgroud_layer, 0);

	auto background_button_layer = BackgroundButtonLayer::create();
	this->addChild(background_button_layer, 1);

	return true;
}

