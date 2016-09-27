#include "Player.h"

#include <RessourceManager.h>
#include <SDL2/SDL_keycode.h>

Player::Player() : m_inputManager(nullptr) {}
Player::~Player() {}

void Player::init(glm::vec2 position, glm::vec2 direction,
                  float speed, KlaoudeEngine::InputManager* inputManager)
{
  m_position = position;
  m_direction = direction;

  m_speed = speed;

  m_color = KlaoudeEngine::ColorRGBA8(255, 255, 255, 255);

  m_textureID = KlaoudeEngine::RessourceManager::getTexture("Texture/bite.png").id;

  m_inputManager = inputManager;
}

void Player::update(float deltaTime)
{
  if(m_inputManager->isKeyDown(SDLK_z))
    m_position.y += m_speed * deltaTime;
  else if(m_inputManager->isKeyDown(SDLK_s))
    m_position.y -= m_speed * deltaTime;
  if(m_inputManager->isKeyDown(SDLK_d))
    m_position.x += m_speed * deltaTime;
  else if(m_inputManager->isKeyDown(SDLK_q))
    m_position.x -= m_speed * deltaTime;
}

void Player::draw(KlaoudeEngine::SpriteBatch& spriteBatch)
{
  glm::vec4 uvRect(0.f, 0.f, 1.f, 1.f);
  glm::vec4 destRect(m_position.x, m_position.y, 32, 32);
  spriteBatch.draw(destRect, uvRect, m_textureID, 0, m_color, m_direction);
}
