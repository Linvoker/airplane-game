#ifndef _GAME_CONTROL_LAYER_H_
#define _GAME_CONTROL_LAYER_H_

#include "cocos2d.h"

using namespace cocos2d;

class GameControlLayer : public cocos2d::Layer {
public:
	CREATE_FUNC(GameControlLayer);
	int getScore();
private:
	GameControlLayer();
	virtual bool init() override;
	void pauseMenuCallback(Ref *);
	void updatePrintScore(Ref *);
	void updateLifeBar(Ref *);
	void gameOverHandler(Ref *);

	int score;
	Menu *menu_pause;
	MenuItemSprite *item_pause;
	Label *score_label;
	ProgressTimer *p_life_bar;
	Label *hp_label;
	ProgressTimer *p_bonus_bar;
	Sprite *bonus_bar_track;
};
#endif
