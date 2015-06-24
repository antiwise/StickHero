#ifndef __Player_H__
#define __Player_H__

#include <cocos2d.h>
USING_NS_CC;

class Player : public Node
{
public:
	~Player(){ walkAnimate->release(); kickAnimate->release(); stayAnimate->release(); }
	virtual bool init();
	void walk();
	void stay();
	void stop();
	void kick();
	CREATE_FUNC(Player);
	cocos2d::Sprite* getSprite(){ return _player; }
	void setSprite(cocos2d::Sprite*);
	bool isFlip(){ return flip; }
	void setFlip(bool flip){ this->flip = flip; };
	Animate* Player::getWalkAnimate(){ return walkAnimate; }
	Animate* Player::getKickAnimate(){ return kickAnimate; }
	Animate* Player::getStayAnimate(){ return stayAnimate; }
private:
	cocos2d::Sprite* _player;
	cocos2d::Animation* walkAnimation;
	cocos2d::Animation* stayAnimation;
	cocos2d::Animation* kickAnimation;
	cocos2d::Animate* walkAnimate;
	cocos2d::Animate* stayAnimate;
	cocos2d::Animate* kickAnimate;
	int playerIndex;
	bool flip;
};

#endif