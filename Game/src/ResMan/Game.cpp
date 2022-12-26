#include "Engine/Game.hpp"

#include <SFML/System/Sleep.hpp>
#include <iostream>

Game::Game(Window * p) :
        _assetManager()
{
        if (p) {
                _win = p;
        } else {
                _win = new Window();
        }
}

Game::~Game()
{ }

void
Game::setGameSettings(int newSet)
{
        _settings = newSet;
}

int
Game::getGameSettings()
{
        return _settings;
}

