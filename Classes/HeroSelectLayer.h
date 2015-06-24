#ifndef __HeroSelectLayer_H__
#define __HeroSelectLayer_H__

#include "cocos2d.h"
#include "GameOverLayer.h"
class HeroSelectLayer
	:public cocos2d::Layer
{
public:
	CREATE_FUNC(HeroSelectLayer);
	virtual bool init();
	void select(Ref*);
	cocos2d::Sprite* getListBg(){ return listbg; }
private:
	cocos2d::Sprite* listbg;
	std::vector<cocos2d::Sprite*> heros;
};

#endif