#ifndef _ENEMY_LAYER_H_
#define _ENEMY_LAYER_H_

#include "cocos2d.h"
using namespace cocos2d;

class EnemyLayer : public cocos2d::Layer {
public:
	CREATE_FUNC(EnemyLayer);
private:
	virtual bool init() override;
	void addEnemyPlane(float);
	virtual void update(float) override;
	void unscheduleAll(Ref*);
	void killAllEnemyBonus(Ref *);

	float produce_interval = 0.5f;
};
#endif
