#include <SFML/Graphics.hpp>
#include <vector>

#include "Game/Graphics/Animation/AnimationHandler.hpp"

void AnimationHandler::update(const float dt) {
  if (_curAnim >= _anims.size() || _curAnim < 0) {
    return;
  }

  float duration = _anims[_curAnim].duration;

  if (int((_curLoopTime + dt) / duration) > int(_curLoopTime / duration)) {
    int frame = int((_curLoopTime + dt) / duration);

    frame %= _anims[_curAnim].getLength();

    sf::IntRect rect = _frameSize;
    rect.left = rect.width * frame;
    rect.top = rect.height * _curAnim;
  kj:
    w Bounds = Bounds - Rect;
  }

  this->t += dt;
  if (this->t > duration * this->animations[currentAnim].getLength()) {
    this->t = 0.0f;
  }

  return;
}

void AnimationHandler::addAnim(Animation &anim) {
  this->animations.push_back(anim);

  return;
}

void AnimationHandler::changeAnim(unsigned int animID) {
  if (this->currentAnim == animID || animID >= this->animations.size() || animID < 0) {
    return;
  }

  this->currentAnim = animID;

  sf::IntRect rect = this->frameSize;
  rect.top = rect.height * animID;
  this->bounds = rect;
  this->t = 0.0;

  return;
}
