#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance()->draw("background", 400, 300, 0, 255, true);
	
	TextureManager::Instance()->draw("ship", 525, 500, 0, 255, true);
	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);

	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
}

void PlayScene::update()
{
	updateDisplayList();

	m_pVelocityLabel->setText("Velocity = "+ std::to_string(m_pBall->throwSpeed.x));
	/*string str;*/ /*= (m_pBall->getRigidBody()->acceleration);*/
	m_pAccelerationLabel->setText("Acceleration = ");/* += str;*/

	m_pMassLabel->setText("Mass =2.2");

	m_pPositionLabel->setText("Position of Player =" +std::to_string(m_pPlayer->getTransform()->position.x));

	m_pDistanceLabel->setText("Distance =" + std::to_string(getTransform()->position.x = 565.0f - m_pPlayer->getTransform()->position.x));

	m_pAngleLabel->setText("Angle = ");
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	// handle player movement with GameController
	if (SDL_NumJoysticks() > 0)
	{
		if (EventManager::Instance().getGameController(0) != nullptr)
		{
			const auto deadZone = 10000;
			if (EventManager::Instance().getGameController(0)->LEFT_STICK_X > deadZone)
			{
				m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
				m_playerFacingRight = true;
			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_X < -deadZone)
			{
				m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
				m_playerFacingRight = false;
			}
			else
			{
				if (m_playerFacingRight)
				{
					m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
				}
				else
				{
					m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
				}
			}
		}
	}


	// handle player movement if no Game Controllers found
	if (SDL_NumJoysticks() < 1)
	{
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
			m_playerFacingRight = false;
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
			m_playerFacingRight = true;
		}
		else
		{
			if (m_playerFacingRight)
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
			}
			else
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
			}
		}
	}
	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	//Set up background
	TextureManager::Instance()->load("../Assets/textures/Background.png", "background");

	//Stromstropper
	TextureManager::Instance()->load("../Assets/textures/ship3.png", "ship");
	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	//Ball Sprite
	m_pBall = new Target();
	addChild(m_pBall);

	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);
	m_playerFacingRight = true;

	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(400.0f, 580.0f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
	{
		m_pBackButton->setActive(false);
		TheGame::Instance()->changeSceneState(START_SCENE);
	});

	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pBackButton->setAlpha(128);
	});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pBackButton->setAlpha(255);
	});
	addChild(m_pBackButton);

	///* Velocity Label */
	m_pVelocityLabel = new Label("Velocity", "Consolas");
	m_pVelocityLabel->getTransform()->position = glm::vec2(120.0f, 40.0f);

	addChild(m_pVelocityLabel);

	///* Acceleration Label */
	m_pAccelerationLabel = new Label("Acceleration", "Consolas");
	m_pAccelerationLabel->getTransform()->position = glm::vec2(120.0f, 100.0f);

	addChild(m_pAccelerationLabel);

	///* Mass Label */
	m_pMassLabel = new Label("Mass", "Consolas");
	m_pMassLabel->getTransform()->position = glm::vec2(120.0f, 160.0f);

	addChild(m_pMassLabel);

	///* Position Label */
	m_pPositionLabel = new Label("Position", "Consolas");
	m_pPositionLabel->getTransform()->position = glm::vec2(420.0f, 40.0f);

	addChild(m_pPositionLabel);

	///* Distance Label */
	m_pDistanceLabel = new Label("Distance", "Consolas");
	m_pDistanceLabel->getTransform()->position = glm::vec2(420.0f, 100.0f);

	addChild(m_pDistanceLabel);

	///* Angle Label */
	m_pAngleLabel = new Label("Angle", "Consolas");
	m_pAngleLabel->getTransform()->position = glm::vec2(420.0f, 160.0f);

	addChild(m_pAngleLabel);

	//// Next Button
	//m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
	//m_pNextButton->getTransform()->position = glm::vec2(500.0f, 400.0f);
	//m_pNextButton->addEventListener(CLICK, [&]()-> void
	//{
	//	m_pNextButton->setActive(false);
	//	TheGame::Instance()->changeSceneState(END_SCENE);
	//});

	//m_pNextButton->addEventListener(MOUSE_OVER, [&]()->void
	//{
	//	m_pNextButton->setAlpha(128);
	//});

	//m_pNextButton->addEventListener(MOUSE_OUT, [&]()->void
	//{
	//	m_pNextButton->setAlpha(255);
	//});

	//addChild(m_pNextButton);

	///* Instructions Label */
	//m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas");
	//m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 500.0f);

	//addChild(m_pInstructionsLabel);
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Physic Control", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if (ImGui::Button("Throw")) {
		m_pBall->doThrow();
	}
	ImGui::Separator();

	static bool isGravityEnabled = false;
	if (ImGui::Checkbox("Gravity", &isGravityEnabled)) {
		m_pBall->isGravityEnabled = isGravityEnabled;
	};

	static int xPlayerpos = 300;
	if (ImGui::SliderInt("Player Position X", &xPlayerpos, 0, 800)) {
		m_pPlayer->getTransform()->position.x = xPlayerpos;
		m_pBall->throwPosition = glm::vec2(xPlayerpos, 500);
	}
	
	static int velocity[2] = { 5, 5 };
	if (ImGui::SliderInt2("Throw Speed", velocity, 0, 500)) {
		m_pBall->throwSpeed = glm::vec2(velocity[0], -velocity[1] * 0.1);
	}

	ImGui::End();
	ImGui::EndFrame();
	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
