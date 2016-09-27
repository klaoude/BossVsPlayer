#pragma once

#include <SpriteBatch.h>
#include <InputManager.h>

class Player
{
public:
  Player();
  ~Player();

  void init(glm::vec2 position, glm::vec2 direction,
            float speed, KlaoudeEngine::InputManager* inputManager);

  void update(float deltaTime);
  void draw(KlaoudeEngine::SpriteBatch& spriteBatch);

private:
  glm::vec2 m_position;
  glm::vec2 m_direction;
  float m_speed;
  KlaoudeEngine::ColorRGBA8 m_color;
  GLuint m_textureID;
  KlaoudeEngine::InputManager* m_inputManager;
};
