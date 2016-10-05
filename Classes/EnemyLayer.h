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
	float getRandomFloat(float, float);

	float produce_interval = 1.0f;
};
#endif
