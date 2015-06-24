#ifndef __Stick_H__
#define __Stick_H__

#include <cocos2d.h>
USING_NS_CC;

class Stick : public Node
{
public:
	virtual bool init();
	CREATE_FUNC(Stick);
	int getLength(){ return length; }
	void setLength(int length){ this->length = length; }
	void addStick(cocos2d::Vec2);
	void stickLength(float);
	void stopStick();
	void resetStick();
	cocos2d::Sprite* getSprite(){ return _stick; }
private:
	cocos2d::Sprite* _stick;
	int length;
};

#endif