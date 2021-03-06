#ifndef _HERO_PLANE_LAYER_H_
#define _HERO_PLANE_LAYER_H_

#include <vector>
#include "cocos2d.h"
#include "HeroPlaneSprite.h"

using namespace cocos2d;
//using namespace std;
class HeroPlaneLayer : public cocos2d::Layer {
public:
	CREATE_FUNC(HeroPlaneLayer);
	//HeroPlaneSprite *getHeroPlaneSprite();
private:
	virtual bool init() override;
	virtual void update(float delta) override;
	void movePlaneByKeyboard(int i);
	void unscheduleAll(Ref *);
	void detectCollision(float);
	void unscheduleDetect(Ref *);
	void scheduleDetect(Ref *);

	HeroPlaneSprite *hero_plane_sprite;//飞机的指针，movePlaneByKeyboard函数要用，不想用getchildren()
	std::vector<int> keyboard_status = {0, 0, 0, 0};//上下左右，为零时表示松开
};
#endif 
