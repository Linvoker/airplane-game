#include <functional>
#include "BulletLayer.h"
#include "cocos2d.h"

using namespace cocos2d;

bool BulletLayer::init() {
	schedule(CC_SCHEDULE_SELECTOR(BulletLayer::createBullet), 0.5);

	return true;
}

void BulletLayer::createBullet(float shit) {

}