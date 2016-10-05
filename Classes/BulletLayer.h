#ifndef _BULLET_LAYER_H_
#define  _BULLET_LAYER_H_

#include <string>
#include "cocos2d.h"

using namespace cocos2d;

class BulletLayer : public cocos2d::Layer {
public:
	CREATE_FUNC(BulletLayer);
	void setBulletType(const std::string &sprite_frame_name);
	Size getBulletSize();
	float getDamageVal();
private:
	virtual bool init() override;
	void createBullet(float);

	std::string bullet_name;
	Size bullet_size;
	float bullet_speed;//越小越快
	float shoot_interval;
	float damage_val;
	//std::list<Sprite *> bullet_table;//用std::list维护一个子弹列表，因为只需要插入、删除和遍历操作。还是用自带的Vector<Node*>_children好了
	
};
#endif

