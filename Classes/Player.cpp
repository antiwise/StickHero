#include "Player.h"
bool Player::init()
{
	flip = true;
	playerIndex = UserDefault::getInstance()->getIntegerForKey("playerIndex", 1);
	_player = Sprite::create(StringUtils::format("image/anim%d/stay1.png",playerIndex));
	_player->setAnchorPoint(Vec2(0.5, 0));
	Vec2 size = _player->getContentSize();
	Vector<SpriteFrame*> frameVector;
	for (int i = 1; i <= 5; i++)
	{
		std::string pngName = StringUtils::format("image/anim%d/stay%d.png", playerIndex, i).c_str();
		frameVector.pushBack(SpriteFrame::create(pngName, Rect(0, 0, size.x, size.y)));
	}
	stayAnimation = Animation::createWithSpriteFrames(frameVector, 0.1);
	stayAnimation->setRestoreOriginalFrame(false);
	stayAnimation->setLoops(10000);
	stayAnimate = Animate::create(stayAnimation);

	
	frameVector.clear();
	for (int i = 1; i <= 5; i++)
	{
		std::string pngName = StringUtils::format("image/anim%d/walk%d.png", playerIndex, i).c_str();
		frameVector.pushBack(SpriteFrame::create(pngName, Rect(0, 0, size.x, size.y)));
	}
	walkAnimation = Animation::createWithSpriteFrames(frameVector, 0.1);
	walkAnimation->setRestoreOriginalFrame(false);
	walkAnimation->setLoops(10000);
	walkAnimate = Animate::create(walkAnimation);

	frameVector.clear();
	for (int i = 1; i <= 5; i++)
	{
		std::string pngName = StringUtils::format("image/anim%d/kick%d.png", playerIndex, i).c_str();
		frameVector.pushBack(SpriteFrame::create(pngName, Rect(0, 0, size.x, size.y)));
	}
	kickAnimation = Animation::createWithSpriteFrames(frameVector, 0.2);
	kickAnimation->setRestoreOriginalFrame(false);
	kickAnimation->setLoops(1);
	kickAnimate = Animate::create(kickAnimation);

	walkAnimate->retain();
	stayAnimate->retain();
	kickAnimate->retain();
	this->addChild(_player);

	return true;
}


void Player::stay()
{
	_player->runAction(stayAnimate);
	log("stayAnimate");
}

void Player::stop()
{
	_player->stopAllActions();
	log("stopAllActions");
}

void Player::walk()
{
	_player->runAction(walkAnimate);
	log("walkAnimate");
}

void Player::kick(){
	_player->runAction(kickAnimate);
	log("kickAnimate");
}