#ifndef _BONUS_LAYER_H_
#define _BONUS_LAYER_H_

#include "cocos2d.h"

using namespace cocos2d;

class BonusLayer : public cocos2d::Layer {
public:
	CREATE_FUNC(BonusLayer);
private:
	virtual bool init() override;
	void addBonusSprite(Ref *);
	virtual void update(float) override;
};
#endif
