#ifndef __WELCOMESCENE_H__
#define __WELCOMESCENE_H__

#include "cocos2d.h"
#include "BackgroundLayer.h"
class WelcomeScene : public cocos2d::Scene
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(WelcomeScene);
	BackgroundLayer* backgroundLayer;
};

#endif // __WELCOMESCENE_H__
