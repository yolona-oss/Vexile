#pragma once

#include "Game/GameBase.hpp"

class GameState {
public:
  GameState(GameBase &a_game);
  virtual ~GameState();

  // Lifetime management functions
  virtual void pause() = 0;
  virtual void resume() = 0;

  // State loop functions, called in this order
  // Note: elapsed times are measured from the last frame, not as totals
  virtual void event(sf::Time elapsed, sf::Event a_event) = 0;
  virtual void update(sf::Time elapsed) = 0;
  virtual void draw(VirtualScreen &screen) = 0;

protected:
  GameBase &game;
};
