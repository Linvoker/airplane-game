#ifndef _WELCOME_BACKGROUND_LAYER_H_
#define _WELCOME_BACKGROUND_LAYER_H_

#include "cocos2d.h"
class WelcomeBackgroundLayer : public cocos2d::Layer {
public:
	CREATE_FUNC(WelcomeBackgroundLayer);
private:
	virtual bool init() override;
};

#endif
