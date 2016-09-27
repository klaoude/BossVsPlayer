#pragma once

#include <KlaoudeEngine.h>
#include <Window.h>
#include <GLSLProgram.h>
#include <InputManager.h>
#include <Camera2D.h>
#include <SpriteBatch.h>
#include <Timing.h>

#include "Player.h"

enum class GameStates {PLAY, EXIT};

class MainGame {
public:
  MainGame();
  ~MainGame();

  void run(bool multi = false);

private:
  void initSystems();
  void initShaders();

  void gameLoop();
  void processInput();
  void drawGame();

  KlaoudeEngine::Window m_window;
  KlaoudeEngine::GLSLProgram m_textureProgram;
  KlaoudeEngine::InputManager m_inputManager;
  KlaoudeEngine::Camera2D m_camera;
  KlaoudeEngine::SpriteBatch m_agentSpriteBatch;

  Player m_player;

  int m_screenWidht, m_screenHeight;
  float m_fps;

  GameStates m_gameState;
};
