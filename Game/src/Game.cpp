#include "Game.hpp"
#include <SFML/System/Sleep.hpp>
#include <iostream>

SnakeGame::SnakeGame(Window * p) :
        Game(p),
        _map(new Map(
                     MapLayout(
                             sf::FloatRect(_win->getSize().x/50.0, _win->getSize().x/50.0, _win->getSize().x-_win->getSize().x/50.0, _win->getSize().y-_win->getSize().x/50.0),
                             sf::Vector2f(_win->getSize().x/50.0, _win->getSize().x/50.0)
                     )
             ))

{
        _win->getEventManager()->addKeyReleasedCallback(
                        sf::Keyboard::S,
                        [&](const sf::Event&e) {
                                _snake->setDirection(Snake::UP);
                        });
        _win->getEventManager()->addKeyReleasedCallback(
                        sf::Keyboard::A,
                        [&](const sf::Event&e) {
                                _snake->setDirection(Snake::LEFT);
                        });
        _win->getEventManager()->addKeyReleasedCallback(
                        sf::Keyboard::W,
                        [&](const sf::Event&e) {
                                _snake->setDirection(Snake::DOWN);
                        });
        _win->getEventManager()->addKeyReleasedCallback(
                        sf::Keyboard::D,
                        [&](const sf::Event&e) {
                                _snake->setDirection(Snake::RIGHT);
                        });
        _win->getEventManager()->addKeyReleasedCallback(
                        sf::Keyboard::Space,
                        [&](const sf::Event& e) {
                                if (_isPaused) {
                                        resumeGame();
                                } else {
                                        pauseGame();
                                }
                                _isPaused = !_isPaused;
                        });
        _win->setFPS(60);

        sf::Texture head;
        sf::Texture bone;
        sf::Texture tail;
        head.loadFromFile("snake.png", sf::IntRect(0, 0, 50, 50));
        bone.loadFromFile("snake.png", sf::IntRect(50, 0, 50, 50));
        tail.loadFromFile("snake.png", sf::IntRect(100, 0, 50, 50));

        float tile_size = _win->getSize().x/50.0;

        _snake = new Snake(
                        sf::Vector2f(_win->getSize().x/2.0-(tile_size*2), _win->getSize().y/2.0-(tile_size*2)),
                        _map->layout().size(),
                        tile_size,
                        Snake::UP,
                        head,
                        bone,
                        tail);


        _bg_tile.loadFromFile("/home/data/projects/desktop/games/drill snake/build/grass.jpg",
                              sf::IntRect(0, 0, _map->layout().tileSize().x, _map->layout().tileSize().y));
        for (int j = 0; j < (_map->layout().size().height-_map->layout().size().top)/_map->layout().tileSize().x; j++) {
                for (int i = 0; i < (_map->layout().size().width-_map->layout().size().left)/_map->layout().tileSize().x; i++) {
                        _map->addEntity(
                                        Entity(
                                                _bg_tile,
                                                _map->layout().tileSize(),
                                                sf::Vector2f(_map->layout().size().left + i*_map->layout().tileSize().x,
                                                             _map->layout().size().top + j*_map->layout().tileSize().x
                                                             )
                                        )
                                );
                }
        }

        _border = new Border(
                        sf::FloatRect(_map->layout().size()),
                        sf::FloatRect(0, 0, _win->getSize().x, _win->getSize().y),
                        sf::Color::Red);

        // setupMainMenu();
        mainLoop();
}

SnakeGame::~SnakeGame()
{
        delete _snake;
}

void
SnakeGame::spawnFood()
{
        auto snake_bounds = _snake->getGlobalBounds();
        // _food.push_back(new Food());
}

void
SnakeGame::pauseGame()
{
        _snake->stop();
}

void
SnakeGame::resumeGame()
{
        _snake->start();
}

void
SnakeGame::mainLoop()
{
        // _mainMenu->display();
        _snake->spawn();

        sf::Time timePerFrame = sf::milliseconds((1.0 / _win->getFPS()) * 1000.0);
        sf::Clock clock;
        sf::Time timeSinceLastUpdate = sf::Time::Zero;
        while (!_win->isDone()) {
                _win->getEventManager()->processEvents();
                timeSinceLastUpdate += clock.restart();
                while (timeSinceLastUpdate > timePerFrame) {
                        timeSinceLastUpdate -= timePerFrame;
                        update(timePerFrame);
                }

                render();

                // auto sleepv = timePerFrame - sf::milliseconds(clock.getElapsedTime().asMilliseconds());
                // sf::sleep((sleepv.asMilliseconds() > 0 ? sleepv : sf::milliseconds(0)));
        }
}

#include <iostream>
void
SnakeGame::update(const sf::Time& t)
{
        _snake->update(t);
        if (!_snake->isAlive()) {
                _snake->spawn();
                return;
        }
}

void
SnakeGame::render()
{
        _win->beginDraw();
        _map->forEach([&](Entity& e) {
                              e.render(_win->getRenderWindow());
                      });
        _border->render(_win->getRenderWindow());
        // sf::RectangleShape s;
        // s.setPosition(_snake->area().left, _snake->area().top);
        // s.setSize(sf::Vector2f(_snake->area().width, _snake->area().height));
        // s.setFillColor(sf::Color::Red);
        // _win->draw(s);
        _snake->render(*_win->getRenderWindow());
        _win->endDraw();
}

void
SnakeGame::setupMainMenu()
{
        MenuOption* o1 = new MenuOption("Start game",   true);
        MenuOption* o2 = new MenuOption("Change track", false);
        MenuOption* o3 = new MenuOption("Settings",     false);
        MenuOption* o4 = new MenuOption("Exit",         true);

        _mainMenu->addOption(o1).
                addOption(o2).
                addOption(o3).
                addOption(o4);

        _mainMenu->setLayout(MenuLayout::VerticleCentered);
        _mainMenu->setBackground(AssetManager::GetTexture("main_menu_bg.jpeg"));

        sf::Font font(AssetManager::GetFont("RobotoMono-Regular.ttf")),
        fontHovered(AssetManager::GetFont("RobotoMono-Bold.ttf"));
        sf::Text text, textHovered; //templates

        text.setFont(font);
        text.setStyle(sf::Text::Style::Regular);
        textHovered.setFont(fontHovered);
        textHovered.setStyle(sf::Text::Style::Bold);

        _mainMenu->setTemplateText(text);
        _mainMenu->setTemplateTextHovered(textHovered);
}

void
SnakeGame::setupPauseMenu()
{
        /* MenuOption o1("Resume",   true); */
        /* MenuOption o2("Restart",  false); */
        /* MenuOption o3("Settings", false); */
        /* MenuOption o4("Exit",     true); */

        /* _pauseMenu->addOption(o1). */
        /*    addOption(o2). */
        /*    addOption(o3). */
        /*    addOption(o4); */

        /* _pauseMenu->setLayout(MenuLayout::VerticleCentered); */
        /* _pauseMenu->setBackground(AssetManager::GetTexture("pauseMenuBG.jpeg")); */

        /* sf::Font font(AssetManager::GetFont("RobotoMono-Regular.ttf")), */
        /*          fontHovered(AssetManager::GetFont("RobotoMono-Bold.ttf")); */
        /* sf::Text text, textHovered; //templates */

        /* text.setFont(font); */
        /* text.setStyle(sf::Text::Style::Regular); */
        /* textHovered.setFont(fontHovered); */
        /* textHovered.setStyle(sf::Text::Style::Bold); */

        /* _pauseMenu->setTemplateText(text); */
        /* _pauseMenu->setTemplateTextHovered(textHovered); */
}
