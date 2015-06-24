#include "Stick.h"

bool Stick::init(){
	_stick = Sprite::create("image/stick1.png");
	_stick->setAnchorPoint(Vec2(0.5, 0));
	_stick->setPosition(-_stick->getContentSize().width / 2, -_stick->getContentSize().height);
	this->addChild(_stick);
	return true;
}
void Stick::addStick(Vec2 StickPoint)
{
	resetStick();
	_stick->setPosition(StickPoint);
	this->schedule(schedule_selector(Stick::stickLength));
}

void Stick::stickLength(float)
{
	_stick->setScaleY(_stick->getScaleY() + 5);
}
void Stick::stopStick()
{
	length = _stick->getContentSize().height*_stick->getScaleY();
	this->unschedule(schedule_selector(Stick::stickLength));
}

void Stick::resetStick()
{
	_stick->setRotation(0);
	_stick->setScaleY(0);
}