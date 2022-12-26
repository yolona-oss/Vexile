#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <vector>

class Animation {
public:
  unsigned int startFrame;
  unsigned int endFrame;

  float duration;

  Animation(unsigned int startFrame, unsigned int endFrame, float duration) {
    this->startFrame = startFrame;
    this->endFrame = endFrame;
    this->duration = duration;
  }

  unsigned int getLength() { return endFrame - startFrame + 1; }
};

class AnimationHandler {
public:
  AnimationHandler() {
    _curLoopTime = .0f;
    _curAnim = -1;
  }

  AnimationHandler(const sf::IntRect &frameSize) {
    FrameSize = frameSize;

    _curLoopTime = .0f;
    _curAnim = -1;
  }

  void addAnim(Animation &anim);
  void update(const float dt);
  void changeAnim(unsigned int animNum);

  sf::IntRect Bounds;
  sf::IntRect FrameSize;

private:
  std::vector<Animation> _anims;
  float _curLoopTime;

  int _curAnim;
};
