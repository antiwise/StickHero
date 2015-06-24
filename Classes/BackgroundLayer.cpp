#include "BackgroundLayer.h"
#include "GameOverLayer.h"

USING_NS_CC;
bool BackgroundLayer::init(){
	if (!Layer::init()){
		return false;
	}
	Size visible = Director::getInstance()->getVisibleSize();
	int RandomNumber = CCRANDOM_0_1() * 1000;
	int BGI_Number = RandomNumber % 5;
	switch (BGI_Number) {
	case 0:
		Image_One = Sprite::create("image/bg/bg1.jpg");
		Image_Two = Sprite::create("image/bg/bg1.jpg");
		break;
	case 1:
		Image_One = Sprite::create("image/bg/bg2.jpg");
		Image_Two = Sprite::create("image/bg/bg2.jpg");
		break;
	case 2:
		Image_One = Sprite::create("image/bg/bg3.jpg");
		Image_Two = Sprite::create("image/bg/bg3.jpg");
		break;
	case 3:
		Image_One = Sprite::create("image/bg/bg4.jpg");
		Image_Two = Sprite::create("image/bg/bg4.jpg");
		break;
	case 4:
		Image_One = Sprite::create("image/bg/bg5.jpg");
		Image_Two = Sprite::create("image/bg/bg5.jpg");
		break;
	default:
		break;
	}
	Image_One->setPosition(visible.width / 2, visible.height / 2);
	Image_Two->setPosition(visible.width / 2 + Image_Two->getContentSize().width,
		visible.height / 2);
	this->addChild(Image_One, 1);
	this->addChild(Image_Two, 1);

	GameName = Sprite::create("image/uires_1.png");
	GameName->setPosition(visible.width / 2, visible.height / 5 * 4);
	this->addChild(GameName, 2);

	StartBtn = MenuItemSprite::create(Sprite::create("image/uires_2.png"),
		Sprite::create("image/uires_2.png"), (CC_CALLBACK_1(BackgroundLayer::start,this,2)));
	StartBtn->setPosition(visible.width / 2, visible.height / 2 + 8);
	MoveTo* StartBtnMoveDown = MoveTo::create(2, Vec2(visible.width / 2, visible.height / 2 - 8));
	MoveTo* StartBtnMoveUp = MoveTo::create(2, Vec2(visible.width / 2, visible.height / 2 + 5));
	Sequence* StartMoveSeq = Sequence::create(StartBtnMoveDown, StartBtnMoveUp, NULL);
	RepeatForever* StartMoveRepeat = RepeatForever::create(StartMoveSeq);
	StartBtn->runAction(StartMoveRepeat);
	menu = Menu::create(StartBtn, NULL);
	menu->setPosition(0, 0);
	this->addChild(menu, 2);

	nextStage = 0;
	for (int i = 0; i < 3; i++)
	{
		stage_sprite[i] = Sprite::create("image/stage1.png");
	}
	stage_sprite[0]->setScaleX(30);
	for (int i = 1; i < 3; i++)
	{
		//高度全部露出来
		stage_sprite[i]->setPosition(Vec2(visible.width + stage_sprite[i]->getScaleX()*stage_sprite[i]->getContentSize().width / 2, stage_sprite[i]->getContentSize().height / 2));
	}
	//放在屏幕中间，高度露出3/4
	stage_sprite[0]->setPosition(Vec2(visible.width / 2, stage_sprite[0]->getContentSize().height / 4));
	for (int i = 0; i < 3; i++)
	{
		this->addChild(stage_sprite[i], 3);
	}

	EventListenerTouchOneByOne* touch_listener = EventListenerTouchOneByOne::create();
	touch_listener->onTouchBegan = [=](Touch* pTouch, Event* pEvent)
	{
		if (isStart)
		{
			if (touchable)
			{
				stick->addStick(stickPoint);
				touchable = false;
				return true;
			}
			else{
				int NowStage = nextStage == 0 ? 2 : (nextStage - 1);
				int LastStage = NowStage == 0 ? 2 : (NowStage - 1);
				Sprite* temp = player->getSprite();
				if (temp->getPositionX() - temp->getContentSize().width / 2 >= stage_sprite[LastStage]->getPositionX() + 
					stage_sprite[LastStage]->getScaleX()*stage_sprite[LastStage]->getContentSize().width / 2){
					if (!player->isFlip()){
						player->getSprite()->setFlippedY(false);
						MoveBy *moveBy = MoveBy::create(0.f, Vec2(0, player->getSprite()->getContentSize().height));
						player->setFlip(true);
						player->getSprite()->runAction(moveBy);
					}
					else{
						player->getSprite()->setFlippedY(true);
						MoveBy *moveBy = MoveBy::create(0.f, Vec2(0, -player->getSprite()->getContentSize().height));
						player->setFlip(false);
						player->getSprite()->runAction(moveBy);
					}
				}
			}
		}
		return false;
	};
	touch_listener->onTouchMoved = [](Touch* pTouch, Event* pEvent){};
	touch_listener->onTouchEnded = [=](Touch* pTouch, Event* pEvent){ stick->stopStick(); rotateStickAndGo(); };
	touch_listener->onTouchCancelled = [](Touch* pTouch, Event* pEvent){};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touch_listener, this);

	isStart = false;

	player = Player::create();
	player->setPosition(Vec2(0, 0));
	player->getSprite()->setPosition(Vec2(visible.width / 2, stage_sprite[0]->getContentSize().height / 4 * 3));
	this->addChild(player, 10);
	player->getSprite()->stopAllActions();
	player->stay();
	//初始化棍子
	stick = Stick::create();
	stick->setPosition(Vec2(0, 0));
	this->addChild(stick, 5);

	heroChangeBtn = MenuItemSprite::create(Sprite::create("image/herochange.png"),
		Sprite::create("image/herochange.png"), (CC_CALLBACK_1(BackgroundLayer::heroChangeCallBack, this)));
	heroChangeBtn->setPosition(visible.width - heroChangeBtn->getContentSize().width/2 - 100, 100);
	heroChangeMenu = Menu::create(heroChangeBtn, NULL);
	heroChangeMenu->setPosition(0, 0);
	this->addChild(heroChangeMenu, 2);

	return true;
}

void BackgroundLayer::heroChangeCallBack(Ref*){
	heroSelectLayer = HeroSelectLayer::create();
	this->addChild(heroSelectLayer, 5);
}

void BackgroundLayer::start(Ref* pSender,float time)
{

	Size visible = Director::getInstance()->getVisibleSize();
	touchable = true;
	this->removeChild(menu);
	this->removeChild(GameName);
	this->removeChild(heroChangeMenu);
	//当前分数
	scoreCount = 0;
	scoreLabel = Label::create("Score:0", "fonts/Marker Felt.ttf", 100);
	scoreLabel->setPosition(Vec2(visible.width / 2, visible.height - 100));
	this->addChild(scoreLabel,10);
	//最高分
	scoreMax = UserDefault::getInstance()->getIntegerForKey("scoreMax", 0);
	maxLabel = Label::create("Max:0", "fonts/Marker Felt.ttf", 50);
	maxLabel->setString(StringUtils::format("Max:%d", scoreMax));
	maxLabel->setPosition(Vec2(visible.width - maxLabel->getContentSize().width / 2 - 20, visible.height - maxLabel->getContentSize().height / 2 - 20));
	this->addChild(maxLabel, 10);
	//棒子位置
	stickPoint = calcStickPoint(nextStage);
	MoveTo* stageMove = MoveTo::create(time, Vec2(stage_sprite[nextStage]->getScaleX()*stage_sprite[nextStage]->getContentSize().width / 2,
		stage_sprite[nextStage]->getContentSize().height / 2));
	stage_sprite[nextStage]->runAction(stageMove);

	nextStage = (nextStage + 1) % 3;

	//英雄位置
	Vec2 heroPoint = stickPoint;
	heroPoint.x -= 50;
	player->getSprite()->runAction(MoveTo::create(time, heroPoint));
	this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([=](){isStart = true; }), NULL));
	addStage(time);
}

void BackgroundLayer::addStage(float time)
{
	stickPoint = calcStickPoint(nextStage == 0 ? 2 : nextStage - 1);
	Size visible = Director::getInstance()->getVisibleSize();
	stage_sprite[nextStage]->setScaleX(10 + CCRANDOM_0_1() * 40);
	stage_sprite[nextStage]->setPosition(Vec2(visible.width + stage_sprite[nextStage]->getScaleX()*stage_sprite[nextStage]->getContentSize().width / 2, stage_sprite[nextStage]->getContentSize().height / 2));
	MoveTo* stageMove = MoveTo::create(time, Vec2(visible.width / 2 + CCRANDOM_0_1()*visible.width / 3, stage_sprite[nextStage]->getContentSize().height / 2));
	stage_sprite[nextStage]->runAction(stageMove);
	nextStage = (nextStage + 1) % 3;
}

void BackgroundLayer::stageMove(float time)
{
	int NowStage = nextStage == 0 ? 2 : nextStage - 1;
	int LastStage = NowStage == 0 ? 2 : (NowStage - 1);
	//nowstage移到最左边
	MoveTo* NowstageMove = MoveTo::create(time,
		Vec2(stage_sprite[NowStage]->getScaleX()*stage_sprite[NowStage]->getContentSize().width / 2, stage_sprite[0]->getContentSize().height / 2));
	stage_sprite[NowStage]->runAction(NowstageMove);
	//laststage移除屏幕
	MoveTo* LaststageMove = MoveTo::create(time, Vec2(-stage_sprite[LastStage]->getContentSize().width * stage_sprite[LastStage]->getScaleX() / 2, stage_sprite[0]->getContentSize().height / 2));
	stage_sprite[LastStage]->runAction(LaststageMove);

	player->getSprite()->runAction(MoveTo::create(time, Vec2(stage_sprite[NowStage]->getScaleX()*stage_sprite[NowStage]->getContentSize().width - 50, stage_sprite[NowStage]->getContentSize().height)));
	stick->resetStick();
	addStage(time);
}

Vec2 BackgroundLayer::calcStickPoint(int index){
	int x = stage_sprite[index]->getScaleX()*stage_sprite[index]->getContentSize().width;
	int y = stage_sprite[index]->getContentSize().height;
	return Vec2(x, y);
}

void BackgroundLayer::rotateStickAndGo(){
	int NowStage = nextStage == 0 ? 2 : (nextStage - 1);
	int LastStage = NowStage == 0 ? 2 : (NowStage - 1);
	float DestLengthMin = abs(stage_sprite[LastStage]->getPositionX() - stage_sprite[NowStage]->getPositionX())
		- stage_sprite[LastStage]->getContentSize().width*stage_sprite[LastStage]->getScaleX() / 2
		- stage_sprite[NowStage]->getContentSize().width*stage_sprite[NowStage]->getScaleX() / 2;
	float DestLengthMax = DestLengthMin + stage_sprite[NowStage]->getContentSize().width*stage_sprite[NowStage]->getScaleX();

	RotateTo* rotate90 = RotateTo::create(0.5, 90); //旋转90度
	auto kick = TargetedAction::create(player->getSprite(), player->getKickAnimate());
	//player移动目标位置
	if (stick->getLength() < DestLengthMin || stick->getLength() > DestLengthMax)
	{
		successFlag = false;
		playerDesPos = Vec2(
			stage_sprite[LastStage]->getPositionX()
			+ stage_sprite[LastStage]->getContentSize().width*stage_sprite[LastStage]->getScaleX() / 2
			+ stick->getLength()
			+ player->getSprite()->getContentSize().width / 2 - 5,
			stage_sprite[LastStage]->getContentSize().height
			);
		playerDesPos.x = std::min(playerDesPos.x, Director::getInstance()->getVisibleSize().width + player->getSprite()->getContentSize().width / 2);
	}
	else if (stick->getLength() >= DestLengthMin && stick->getLength() <= DestLengthMax)
	{
		successFlag = true;
		playerDesPos = Vec2(stage_sprite[NowStage]->getPositionX() +
			stage_sprite[NowStage]->getContentSize().width*stage_sprite[NowStage]->getScaleX() / 2
			- player->getSprite()->getContentSize().width / 2 - 5, stage_sprite[NowStage]->getContentSize().height);
		//scoreCount += 1;
	}
	playerDesPosBy = Vec2(playerDesPos.x - player->getSprite()->getPositionX(), 0);
	player->getSprite()->stopAction(player->getStayAnimate());
	player->getSprite()->runAction(kick);
	Sequence *actionN = Sequence::create(DelayTime::create(0.5),rotate90,
		CallFunc::create(CC_CALLBACK_0(BackgroundLayer::stickCallBack,this)),
		CallFunc::create([=](){this->scheduleUpdate();}),
			NULL);
	stick->getSprite()->runAction(actionN);
}

void BackgroundLayer::update(float){
	int NowStage = (nextStage == 0 ? 2 : nextStage - 1);
	int LastStage = NowStage == 0 ? 2 : (NowStage - 1);
	bool bGameover = false;
	bool bComplete = false;
	//走到杆子尽头死掉
	if (!successFlag && player->getSprite()->getPositionX() >= playerDesPos.x){
		bGameover = true;
	}
	if (!player->isFlip()){
		//撞死
		int playerMin = player->getSprite()->getPositionX() - player->getSprite()->getContentSize().width*player->getSprite()->getScaleX() / 2;
		int playerMax = player->getSprite()->getPositionX() + player->getSprite()->getContentSize().width*player->getSprite()->getScaleX() / 2;
		int stageMin = stage_sprite[NowStage]->getPositionX() - stage_sprite[NowStage]->getContentSize().width * stage_sprite[NowStage]->getScaleX() / 2;
		int stageMax = stage_sprite[NowStage]->getPositionX() + stage_sprite[NowStage]->getContentSize().width * stage_sprite[NowStage]->getScaleX() / 2;
		if (playerMax <= stageMin || playerMin >= stageMax){
			//nothing to do
		}
		else{
			bGameover = true;
		}
	}
	if (successFlag && player->getSprite()->getPositionX() >= playerDesPos.x){
		bComplete = true;
	}
	if (bGameover){
		this->unscheduleUpdate();
		player->getSprite()->stopAllActions();
		RotateTo *rotate180 = RotateTo::create(0.5f, 180);
		MoveBy *moveBy1000 = MoveBy::create(0.5f, Vec2(0,-1000));
		UserDefault::getInstance()->setIntegerForKey("scoreMax", scoreMax);
		player->getSprite()->runAction(moveBy1000);
		stick->getSprite()->runAction(rotate180);
		this->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([=](){this->gameOver(); }), NULL));
	}else if (bComplete){
		this->unscheduleUpdate();
		stageMove(2);
		player->getSprite()->stopAction(player->getWalkAnimate());
		player->stay();
		this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([&]()
		{ 
			scoreCount += 1;
			touchable = true;
			scoreLabel->setString(StringUtils::format("Score:%d", scoreCount));
			if (scoreCount > scoreMax){
				scoreMax = scoreCount;
				maxLabel->setString(StringUtils::format("Max:%d", scoreMax));
			}
		}),
			NULL));
	}
	

}

void BackgroundLayer::stickCallBack(){
	player->getSprite()->stopAllActions();
	player->walk();
	if (successFlag == true){
		auto playerMove = MoveBy::create(2, playerDesPosBy);
		//auto stay = TargetedAction::create(player->getSprite(), player->getStayAnimate());
		auto _stageMove = TargetedAction::create(this, CallFunc::create(CC_CALLBACK_0(BackgroundLayer::stageMove, this, 2)));
		auto playSeq = Sequence::create(playerMove, _stageMove,
			CallFunc::create([&](){ 
				player->getSprite()->stopAction(player->getWalkAnimate()); 
				player->stay();
				scoreLabel->setString(StringUtils::format("Score:%d", scoreCount));
				if (scoreCount > scoreMax){ 
					scoreMax = scoreCount;
					maxLabel->setString(StringUtils::format("Max:%d", scoreMax)); 
				}
				touchable = true; 
			}), 
			NULL
			);

		//this->runAction(Sequence::create(DelayTime::create(2),_stageMove,NULL));
		player->getSprite()->runAction(playerMove);
	}
	else{

		
		auto playerMove = MoveBy::create(1, playerDesPosBy);
		//UserDefault::getInstance()->setIntegerForKey("scoreMax", scoreMax);

		player->getSprite()->runAction(playerMove);
		//stick->getSprite()->runAction(Sequence::create(DelayTime::create(1), RotateTo::create(0.2, 180),NULL));
	}
}

void BackgroundLayer::gameOver(){
	/*
	* 游戏结束，添加结束界面
	*/
	isStart = false;
	gameOverLayer = GameOverLayer::create();
	this->addChild(gameOverLayer, 8);
}