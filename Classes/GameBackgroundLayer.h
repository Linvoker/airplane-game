#ifndef _GAME_BACKGROUND_LAYER_H_
#define _GAME_BACKGROUND_LAYER_H_

#include "cocos2d.h"

using namespace cocos2d;

class GameBackgroundLayer : public cocos2d::Layer {
public:
	CREATE_FUNC(GameBackgroundLayer);
private:
	virtual bool init() override;
	virtual void update(float delta) override;

	//两张背景图片交替滚动
	Sprite *game_background_sprite1;//addchild之后其实可以不用额外保留这两张背景图片，用getchildbytag()就行
	Sprite *game_background_sprite2;//但getchildbytag()的时间复杂度是O(n)简单遍历Vector，时间太慢不方便

	float overlap = 1.0;//两张背景图重叠的分辨率，完全不重叠时两张图之间会有间隙。
};
#endif
