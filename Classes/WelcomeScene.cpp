#include "WelcomeScene.h"
using namespace cocos2d;
bool WelcomeScene::init(){
	if (!Scene::init()){
		return false;
	}
	backgroundLayer = BackgroundLayer::create();
	this->addChild(backgroundLayer, 1, 1);
	return true;
}