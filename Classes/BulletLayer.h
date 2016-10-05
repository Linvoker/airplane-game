#ifndef _BULLET_LAYER_H_
#define  _BULLET_LAYER_H_

#include <list>
#include "cocos2d.h"

using namespace cocos2d;

class BulletLayer : public cocos2d::Layer {
public:
	CREATE_FUNC(BulletLayer);

private:
	virtual bool init() override;
	void createBullet(float);

	std::list<Sprite *> bullet_table;//用std::list维护一个子弹列表，因为只需要插入、删除和遍历操作
	
};
#endif
