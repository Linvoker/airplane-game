#include "GameControlLayer.h"
#include "EnemySprite.h"
#include "HeroPlaneSprite.h"
#include <string>

using namespace cocos2d;

int GameControlLayer::getScore() {
	return this->score;
}

GameControlLayer::GameControlLayer() : score(0) {
}

bool GameControlLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//初始化一个暂停/继续的MenuItemSprite和它的Menu
	this->item_pause = MenuItemSprite::create(Sprite::createWithSpriteFrameName("pause.png"),
		Sprite::createWithSpriteFrameName("play.png"), CC_CALLBACK_1(GameControlLayer::pauseMenuCallback, this));
	this->item_pause->setScale(0.25f);
	
	this->menu_pause = Menu::createWithItem(item_pause);
	this->addChild(menu_pause, 1);
	this->menu_pause->setPosition(visibleSize.width + origin.x - item_pause->getContentSize().width * item_pause->getScaleX() / 2, 
		 origin.y + item_pause->getContentSize().height *item_pause->getScaleY() / 2);//右下角
	
	//初始化一个显示分数的label
	this->score_label = Label::createWithTTF("0", "fonts/plantc.ttf", 30);
	this->addChild(this->score_label, 1);
	this->score_label->setAnchorPoint(Vec2(0.0f, 0.0f));//描点设置成左下角的点，这样分数长度的改变也不会影响位置
	this->score_label->setPosition(origin.x, origin.y);
	this->score_label->enableShadow();
	
	//敌机炸毁分数被改变的消息通知，用来调用更新分数和分数显示的函数
	NotificationCenter::getInstance()->addObserver(
		this,
		CC_CALLFUNCO_SELECTOR(GameControlLayer::updatePrintScore),
		"enemyexploded",
		nullptr
		);
	
	//初始化一个显示血量百分比的血条progressTimer
	this->p_life_bar = ProgressTimer::create(Sprite::createWithSpriteFrameName("planeHP.png"));
	this->p_life_bar->setType(ProgressTimer::Type::BAR);
	this->p_life_bar->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->p_life_bar->setPosition(origin.x, visibleSize.height + origin.y);
	this->p_life_bar->setScale(visibleSize.width / this->p_life_bar->getContentSize().width);
	this->p_life_bar->setMidpoint(Vec2(0, 0));
	this->p_life_bar->setBarChangeRate(Vec2(1, 0));//这两步是从左往右的意思
	this->p_life_bar->setPercentage(100);//设置满血
	this->addChild(p_life_bar, 0);

	//飞机临时死亡血条更新
	NotificationCenter::getInstance()->addObserver(
		this,
		CC_CALLFUNCO_SELECTOR(GameControlLayer::updateLifeBar),
		"herodead",
		nullptr
		);
	//游戏结束血条降为零,bonus_bar停止运动
	NotificationCenter::getInstance()->addObserver(
		this,
		CC_CALLFUNCO_SELECTOR(GameControlLayer::gameOverHandler),
		"gameover",
		nullptr
		);

	//初始化一个显示血量的label
	this->hp_label = Label::createWithTTF("1000", "fonts/plantc.ttf", 20);
	this->addChild(this->hp_label, 1);
	this->hp_label->setAnchorPoint(Vec2(0.0f, 1.0f));//描点设置成左上角
	this->hp_label->setPosition(origin.x, origin.y + visibleSize.height);
	this->hp_label->enableShadow();
	

	//初始化bonus的计时器以及progressTimer
	//bonus_bar背景
	this->bonus_bar_track = Sprite::createWithSpriteFrameName("sliderTrack.png");
	this->bonus_bar_track->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->bonus_bar_track->setPosition(origin.x, visibleSize.height + origin.y - p_life_bar->getContentSize().height * p_life_bar->getScaleY() + 1);
	this->addChild(bonus_bar_track, 0);
	//progressTimer
	this->p_bonus_bar = ProgressTimer::create(Sprite::createWithSpriteFrameName("sliderProgress.png"));
	this->p_bonus_bar->setType(ProgressTimer::Type::BAR);
	this->p_bonus_bar->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->p_bonus_bar->setPosition(origin.x, visibleSize.height + origin.y - p_life_bar->getContentSize().height * p_life_bar->getScaleY() + 1);
	this->p_bonus_bar->setScale(1);
	this->p_bonus_bar->setMidpoint(Vec2(0, 0));
	this->p_bonus_bar->setBarChangeRate(Vec2(1, 0));//这两步是从左往右的意思
	this->p_bonus_bar->setPercentage(0);
	this->addChild(p_bonus_bar, 0);

	Sequence *p_sequence = Sequence::create(
		ProgressTo::create(4.0f, 100), 
		CallFunc::create
		([&, this]() 
		{
			this->p_bonus_bar->setPercentage(0);//将bar置回零
			NotificationCenter::getInstance()->postNotification("producebonus");
		}), 
		nullptr);
	RepeatForever *bonus_bar_action = RepeatForever::create(p_sequence);
	this->p_bonus_bar->runAction(bonus_bar_action);
	//scheduleUpdate();

	return true;
}

void GameControlLayer::pauseMenuCallback(Ref *shit) {
	if (!Director::getInstance()->isPaused()) {
		this->item_pause->setNormalImage(Sprite::createWithSpriteFrameName("play.png"));//这些内存会自动释放的
		this->item_pause->setSelectedImage(Sprite::createWithSpriteFrameName("pause.png"));
		Director::getInstance()->pause();
	} else {
		Director::getInstance()->resume();
		this->item_pause->setNormalImage(Sprite::createWithSpriteFrameName("pause.png"));
		this->item_pause->setSelectedImage(Sprite::createWithSpriteFrameName("play.png"));
	}
}

void GameControlLayer::updatePrintScore(Ref *enemy_sprite) {//参数是这个消息的发起对象
	this->score += static_cast<EnemySprite *>(enemy_sprite)->getEnemyScore();
	this->score_label->setString(std::to_string(this->score));
}

void GameControlLayer::updateLifeBar(Ref *shit) {//能进入这里必然是飞机临时死亡
	int hp = HeroPlaneSprite::getInstance()->getHpVal();
	ProgressTo *p_progress = ProgressTo::create(2.0f, hp / 1000.0f * 100);
	this->p_life_bar->runAction(p_progress);//更新血条
	this->hp_label->setString(std::to_string(hp));//更新分数label
}

void GameControlLayer::gameOverHandler(Ref *shit) {//游戏结束
	ProgressTo *p_progress = ProgressTo::create(2.0f, 0);
	this->p_life_bar->runAction(p_progress);//更新血条
	this->hp_label->setString(std::to_string(0));//更新分数label
	this->p_bonus_bar->stopAllActions();//bonus_bar停止运动
}
