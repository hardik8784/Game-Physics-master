#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pStartLabel = new Label("Assignment Group 23", "Consolas", 60, blue, glm::vec2(400.0f, 40.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("Press 1 to Play or click on start", "Consolas", 40, blue, glm::vec2(400.0f, 120.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	m_pInstructionsLabel = new Label("Hardik Shah-101249099", "Consolas", 40, blue, glm::vec2(400.0f, 220.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	m_pInstructionsLabel = new Label("Ahad Shaikh-101003423", "Consolas", 40, blue, glm::vec2(400.0f, 260.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	m_pInstructionsLabel = new Label("BaoLam Nguyen-101277611", "Consolas", 40, blue, glm::vec2(400.0f, 300.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	/*Instructions Label */
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View in game", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 500.0f);

	addChild(m_pInstructionsLabel);

	/*const SDL_Color blue = { 0, 0, 255, 255 };
	m_pGroup = new Label("Group 23", "Consolas", 80, blue, glm::vec2(400.0f, 80.0f));
	m_pGroup->setParent(this);
	addChild(m_pGroup);*/


	/*m_pShip = new Ship();
	m_pShip->getTransform()->position = glm::vec2(400.0f, 300.0f);
	addChild(m_pShip); */

	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->getTransform()->position = glm::vec2(400.0f, 400.0f); 

	m_pStartButton->addEventListener(CLICK, [&]()-> void
	{
		m_pStartButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});
	
	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pStartButton->setAlpha(128);
	});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pStartButton->setAlpha(255);
	});
	addChild(m_pStartButton);

	
}

