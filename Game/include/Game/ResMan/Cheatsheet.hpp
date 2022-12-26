#ifndef CHEATSHEET_HPP_VXGT4S8F
#define CHEATSHEET_HPP_VXGT4S8F

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <map>
#include <string>

enum INPUT_TYPE {
  Keyboard,
  Mouse,
  Joystick,
};

class KeyBind {
public:
  KeyBind();
  KeyBind(const INPUT_TYPE inputType, const sf::Keyboard::Key &key,
          const sf::Event::EventType &event = sf::Event::KeyPressed);
  KeyBind(const INPUT_TYPE inputType, const sf::Mouse::Button &button,
          const sf::Event::EventType &event = sf::Event::MouseLeft);
  KeyBind(const KeyBind &other);
  ~KeyBind();
  friend bool operator==(const KeyBind &k1, const KeyBind &k2);

  bool testEvent(const KeyBind &kb, const sf::Event &) const;
  /* bool eq(const KeyBind& k); */

  INPUT_TYPE InputType;
  sf::Keyboard::Key KeyCode;
  sf::Event::EventType EventType;
  sf::Mouse::Button MouseButton;
};

class Cheatsheet {
public:
  Cheatsheet();
  virtual ~Cheatsheet();

  static KeyBind &GetKey(std::string const &name);
  static bool AddKey(const std::string &name, const KeyBind &keyBind);
  static bool IsMapped(KeyBind const &keyBind);

private:
  std::map<std::string, KeyBind> _codes;

  static Cheatsheet *csInstance;
};

#endif /* end of include guard: CHEATSHEET_HPP_VXGT4S8F */
