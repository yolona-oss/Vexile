#include "Game/ResMan/AssetManager.hpp"
#include <assert.h>
#include <filesystem>

namespace fs = std::filesystem;

AssetManager *AssetManager::sInstance = nullptr;

AssetManager::AssetManager() {
  assert(sInstance == nullptr);

  _asset_d = "./";
  sInstance = this;
}

sf::Texture &AssetManager::GetTexture(std::string const &filename, sf::IntRect area) {
  auto &texMap = sInstance->_textures;

  auto pairFound = texMap.find(filename);

  if (pairFound != texMap.end()) {
    return pairFound->second;
  } else {
    auto &texture = texMap[filename];
    // assert(texture.loadFromFile(fs::path(sInstance->_asset_d) / fs::path(filename), area));
    assert(texture.loadFromFile(filename, area));
    return texture;
  }
}

sf::SoundBuffer &AssetManager::GetSoundBuffer(std::string const &filename) {
  auto &sBufferMap = sInstance->_soundBuffers;

  auto pairFound = sBufferMap.find(filename);
  if (pairFound != sBufferMap.end()) {
    return pairFound->second;
  } else {
    auto &sBuffer = sBufferMap[filename];
    assert(sBuffer.loadFromFile(filename));
    return sBuffer;
  }
}

sf::Font &AssetManager::GetFont(std::string const &filename) {
  auto &fontMap = sInstance->_fonts;

  auto pairFound = fontMap.find(filename);
  if (pairFound != fontMap.end()) {
    return pairFound->second;
  } else {
    auto &sBuffer = fontMap[filename];
    assert(sBuffer.loadFromFile(filename));
    return sBuffer;
  }
}

sf::Shader *AssetManager::GetShader(std::string const &vsFile, std::string const &fsFile) {
  auto &shaderMap = sInstance->_shaders;

  auto combKey = vsFile + ';' + fsFile;
  auto pairFound = shaderMap.find(combKey);
  if (pairFound != shaderMap.end()) {
    return pairFound->second.get();
  } else {
    auto &shader = (shaderMap[combKey] = std::unique_ptr<sf::Shader>(new sf::Shader));
    /* shader->loadFromFile((ASSETS_DIR ? ASSETS_DIR : "") + vsFile, (ASSETS_DIR ? ASSETS_DIR : "")
     * +  fsFile); */
    assert(shader->loadFromFile(vsFile, fsFile));
    return shader.get();
  }
}

void AssetManager::setAssetDir(std::string const &dir) { sInstance->_asset_d = dir; }
