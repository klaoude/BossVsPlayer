#include "MainGame.h"

MainGame::MainGame() : m_screenWidht(800), m_screenHeight(600),
  m_gameState(GameStates::PLAY) {}

MainGame::~MainGame() {}

void MainGame::run(bool multi)
{
  initSystems();

  gameLoop();
}

void MainGame::initSystems()
{
  KlaoudeEngine::init(); //initialisation de l'engine

  m_window.create("BossVsPlayer", m_screenWidht, m_screenHeight, 0); //creation de la fênetre
  glClearColor(0.7f, 0.7f, 0.7f, 1.f); //on met un fond gris clair

  initShaders(); //on initialise les shaders

  m_agentSpriteBatch.init();

  m_camera.init(m_screenWidht, m_screenHeight);
}

void MainGame::initShaders()
{
  m_textureProgram.compileShaders("Shaders/textureShading.vert",
                                  "Shaders/textureShading.frag");
  m_textureProgram.addAttribute("vertexPosition");
  m_textureProgram.addAttribute("vertexColor");
  m_textureProgram.addAttribute("vertexUV");
  m_textureProgram.linkShaders();
}

void MainGame::gameLoop()
{
  const float DESIRED_FPS = 60.0f;
  const int MAX_PHYSICS_STEPS = 5;

  KlaoudeEngine::FpsLimiter fpsLimiter;
  fpsLimiter.setMaxFPS(1337.0f);

  const float MS_PER_SEC = 1000.0f;
  const float DESIRED_FRAMETIME = MS_PER_SEC / DESIRED_FPS;
  const float MAX_DELTA_TIME = 1.0f;

  float previousTicks;
  previousTicks = SDL_GetTicks();

  while(m_gameState != GameStates::EXIT)
  {
    fpsLimiter.begin();

    float newTicks;
    newTicks = SDL_GetTicks();
    float frameTime = newTicks - previousTicks;
    previousTicks = newTicks;
    float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

    m_inputManager.update();

    processInput();

    int i = 0;
    while(totalDeltaTime > 0.f && i < MAX_PHYSICS_STEPS)
    {
      float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);



      totalDeltaTime -= deltaTime;
      i++;
    }

    m_camera.update();

    drawGame();
  }
}

void MainGame::processInput()
{
  SDL_Event evnt;
  while(SDL_PollEvent(&evnt))
  {
    switch(evnt.type)
    {
    case SDL_QUIT:
      m_gameState = GameStates::EXIT;
      break;
    case SDL_KEYDOWN:
      m_inputManager.pressKey((unsigned int) evnt.key.keysym.sym);
      break;
    case SDL_KEYUP:
      m_inputManager.releaseKey((unsigned int) evnt.key.keysym.sym);
      break;
    case SDL_MOUSEMOTION:
      m_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
      break;
    case SDL_MOUSEBUTTONDOWN:
      m_inputManager.pressKey(evnt.button.button);
      break;
    case SDL_MOUSEBUTTONUP:
      m_inputManager.releaseKey(evnt.button.button);
      break;
    default:
      break;
    }
  }
}

void MainGame::drawGame()
{
  glClearDepth(1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_textureProgram.use();

  glActiveTexture(GL_TEXTURE0);

  GLint textureUniform = m_textureProgram.getUniformLocation("mySampler");
  glUniform1i(textureUniform, 0);

  glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
  GLint pUniform = m_textureProgram.getUniformLocation("P");
  glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

  m_agentSpriteBatch.begin();


  m_agentSpriteBatch.end();
  m_agentSpriteBatch.renderBatch();

  m_textureProgram.unUse();

  m_window.swapBuffer();
}
