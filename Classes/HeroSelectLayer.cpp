#include "HeroSelectLayer.h"
USING_NS_CC;
#define HERONUMBER 4
bool HeroSelectLayer::init(){
	if (!Layer::init()){
		return false;
	}
	Size visible = Director::getInstance()->getVisibleSize();
	listbg = Sprite::create("image/listbg.png");
	listbg->setPosition(visible.width / 2, visible.height / 2);
	this->addChild(listbg, 0);

	for (int index = 1; index <= HERONUMBER; index++){
		std::string pngName = StringUtils::format("image/hero%d.png", index).c_str();
		Sprite* hero = Sprite::create(pngName);
		heros.push_back(hero);
	}
	Vec2 leftup = Vec2(0, listbg->getContentSize().height);
	Vec2 rightup = Vec2(listbg->getContentSize().width,  listbg->getContentSize().height);
	Vec2 leftbottom = Vec2(0, 0);
	Vec2 rightbottom = Vec2(listbg->getContentSize().width, 0);
	Vec2 center(listbg->getContentSize().width / 2, listbg->getContentSize().height/2);
	int size = heros.size();
	for (int i = 0; i < size; i++){
		Sprite* hero = heros[i];
		hero->setScale(3);
		listbg->addChild(hero);
	}
	heros[0]->setPosition((leftup + center) / 2);
	heros[1]->setPosition((rightup + center) / 2);
	heros[2]->setPosition((leftbottom + center) / 2);
	heros[3]->setPosition((rightbottom + center) / 2);
	EventListenerTouchOneByOne* touch_listener = EventListenerTouchOneByOne::create();
	touch_listener->setSwallowTouches(true);
	touch_listener->onTouchBegan = [=](Touch* pTouch, Event* pEvent){
		Vec2 point = pTouch->getLocation();
		if (!listbg->getBoundingBox().containsPoint(point)){
			this->getParent()->removeChild(this);
			return false;
		}
		point = listbg->convertToNodeSpace(point);
		for (int i = 0; i < size; i++){
			Sprite* hero = heros[i];
			Rect box = hero->getBoundingBox();
			if (box.containsPoint(point)){
				UserDefault::getInstance()->setIntegerForKey("playerIndex",i+1);
				GameOverLayer* gameOverLayer = GameOverLayer::create();
				gameOverLayer->home(nullptr);
			}
		}
		return true;
	};
	touch_listener->onTouchMoved = [](Touch* pTouch, Event* pEvent){log("%f,%f",pTouch->getLocation().x,pTouch->getLocation().y); };
	touch_listener->onTouchEnded = [=](Touch* pTouch, Event* pEvent){ };
	touch_listener->onTouchCancelled = [](Touch* pTouch, Event* pEvent){};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touch_listener, this);
	

	return true;
}