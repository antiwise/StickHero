#ifndef __BackgroundLayer_H__
#define __BackgroundLayer_H__

#include "cocos2d.h"
#include "Player.h"
#include "Stick.h"
#include "GameOverLayer.h"
#include "HeroSelectLayer.h"
class GameOverLayer;
class HeroSelectLayer;
class BackgroundLayer
	:public cocos2d::Layer
{
public:
	BackgroundLayer(){}
	~BackgroundLayer(){}
	virtual bool init();
	CREATE_FUNC(BackgroundLayer);
	//void BGIMove(float);

	void start(Ref* pSender,float time);
	void heroChangeCallBack(Ref*);
	void addStage(float time);
	void stageMove(float time);
	cocos2d::Vec2 calcStickPoint(int);
	void rotateStickAndGo();
	void stickCallBack();
	void update(float) override;
	void gameOver();
private:
	//¹÷×ÓÂä½Åµã
	cocos2d::Vec2 stickPoint;

	cocos2d::Sprite* Image_One;
	cocos2d::Sprite* Image_Two;

	cocos2d::MenuItemSprite* StartBtn;
	cocos2d::Menu* menu;

	cocos2d::MenuItemSprite* heroChangeBtn;
	cocos2d::Menu* heroChangeMenu;

	cocos2d::Sprite* GameName;
	
	cocos2d::Sprite* stage_sprite[3];
	cocos2d::Label* scoreLabel;
	cocos2d::Label* maxLabel;

	cocos2d::Vec2 playerDesPos;
	cocos2d::Vec2 playerDesPosBy;
	int nextStage;
	bool isStart;

	bool successFlag;
	bool touchable;
	int scoreCount;
	int scoreMax;
	Player* player;
	Stick* stick;
	GameOverLayer *gameOverLayer;
	HeroSelectLayer *heroSelectLayer;
};

#endif
