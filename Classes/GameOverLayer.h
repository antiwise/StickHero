#ifndef __GameOverLayer_H__
#define __GameOverLayer_H__

#include "cocos2d.h"
#include "BackgroundLayer.h"
class BackgroundLayer;
class GameOverLayer
	:public cocos2d::Layer
{
public:
	CREATE_FUNC(GameOverLayer);
	virtual bool init();
	void restart(Ref*);
	void home(Ref*);
private:
	BackgroundLayer *backgroundLayer;
};

#endif