#ifndef _WELCOME_SCENE_H_
#define _WELCOME_SCENE_H_

#include "cocos2d.h"

class WelcomeScene : public cocos2d::Scene {
public:
	//static cocos2d::Scene *create();
	CREATE_FUNC(WelcomeScene);
private:
	virtual bool init() override;
};

#endif