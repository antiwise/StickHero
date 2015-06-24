#include "GameOverLayer.h"
#include "WelcomeScene.h"
USING_NS_CC;
bool GameOverLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visible = Director::getInstance()->getVisibleSize();
	MenuItemSprite* restartBtn = MenuItemSprite::create(Sprite::create("image/uires_5.png"), Sprite::create("image/uires_5.png"), NULL, this, menu_selector(GameOverLayer::restart));
	restartBtn->setPosition(visible.width / 2 + 200, visible.height / 2 + 8);
	Menu* restartMenu = Menu::create(restartBtn, NULL);
	restartMenu->setPosition(0, 0);
	this->addChild(restartMenu);

	MenuItemSprite* homeBtn = MenuItemSprite::create(Sprite::create("image/uires_8.png"), Sprite::create("image/uires_8.png"), NULL, this, menu_selector(GameOverLayer::home));
	homeBtn->setPosition(visible.width / 2 - 200, visible.height / 2 + 8);
	Menu* homeMenu = Menu::create(homeBtn, NULL);
	homeMenu->setPosition(0, 0);
	this->addChild(homeMenu);
	return true;
}

void GameOverLayer::restart(Ref *ref)
{
	WelcomeScene* scene = WelcomeScene::create();
	scene->backgroundLayer->start(nullptr,0);
	TransitionFade *trans = TransitionFade::create(0.5f, scene);
	Director::getInstance()->replaceScene(trans);
}

void GameOverLayer::home(Ref *ref)
{
	WelcomeScene* scene = WelcomeScene::create();
	TransitionFade *trans = TransitionFade::create(0.5f, scene);
	Director::getInstance()->replaceScene(trans);
}