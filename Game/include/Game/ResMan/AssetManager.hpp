#ifndef ASSETMANAGER_HPP_WQZQCZI9
#define ASSETMANAGER_HPP_WQZQCZI9

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <memory>

class AssetManager {
public:
  static sf::Texture &GetTexture(const std::string &filename, sf::IntRect = sf::IntRect());
  static sf::SoundBuffer &GetSoundBuffer(const std::string &filename);
  static sf::Font &GetFont(const std::string &filename);
  static sf::Shader *GetShader(const std::string &vsFile, const std::string &fsFile);

  static void setAssetDir(const std::string &dir);
  static const std::string &getAssetDir();

private:
  std::map<std::string, sf::Texture> _textures;
  std::map<std::string, sf::SoundBuffer> _soundBuffers;
  std::map<std::string, sf::Font> _fonts;
  std::map<std::string, std::unique_ptr<sf::Shader>> _shaders;
  std::string _asset_d;

  static AssetManager *sInstance;

  AssetManager();
};

#endif /* end of include guard: ASSETMANAGER_HPP_WQZQCZI9 */

