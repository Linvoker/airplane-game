#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "GameBackgroundLayer.h"
#include "HeroPlaneLayer.h"
#include "BulletLayer.h"
#include "EnemyLayer.h"
#include "GameControlLayer.h"
#include "BonusLayer.h"

using namespace cocos2d;

class GameScene : public cocos2d::Scene {
public:
	CREATE_FUNC(GameScene);

	GameBackgroundLayer *getGameBackgroundLayer();
	HeroPlaneLayer *getHeroPlaneLayer();
	BulletLayer *getBulletLayer();
	EnemyLayer *getEnemyLayer();
	GameControlLayer *getGameControlLayer();
	BonusLayer *getBonusLayer();

private:
	virtual bool init() override;

	GameBackgroundLayer *game_background_layer;
	HeroPlaneLayer *hero_plane_layer;
	BulletLayer *bullet_layer;
	EnemyLayer *enemy_layer;
	GameControlLayer *game_control_layer;
	BonusLayer *bonus_layer;
};
#endif
