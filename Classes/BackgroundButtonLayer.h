#ifndef _BACKGROUND_BUTTON_LAYER_H_
#define _BACKGROUND_BUTTON_LAYER_H_

#include "cocos2d.h"
using namespace cocos2d;
class BackgroundButtonLayer : public cocos2d::Layer {
public:
	CREATE_FUNC(BackgroundButtonLayer);
private: 
	virtual bool init() override;
	void menuCloseCallback();
};
#endif
