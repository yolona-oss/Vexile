#ifndef _GAME_H_
#define _GAME_H_

#include <memory>
#include <stack>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>

class GameState;

class GameBase {
public:
  GameBase(sf::RenderWindow &p);
  virtual ~GameBase();

  void loop();

  void changeState(std::unique_ptr<GameState> state);
  void pushState(std::unique_ptr<GameState> state);
  void popState();

  void quit();

protected:
  sf::RenderWindow &_window;

private:
  // Game loop methods, called in this order
  virtual void event(sf::Time elapsed, sf::Event a_event);
  virtual void update(sf::Time elapsed);
  virtual void draw();

  // Proxy methods to ensure that both the game loop and state loop
  // methods are called (particularly to ensure that derived classes
  // can't change this behavior)
  void masterEvent(sf::Time elapsed, sf::Event a_event);
  void masterUpdate(sf::Time elapsed);
  void masterDraw();

  void maintainAspectRatio(sf::View &view, sf::RenderWindow &window);

  sf::Sprite screenSprite;
  sf::View screenView;

  std::stack<std::unique_ptr<GameState>> states;
  bool running;

  sf::Clock clock;
};

#endif
