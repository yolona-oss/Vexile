#include "Game/ResMan/Cheatsheet.hpp"
#include <assert.h>

KeyBind::KeyBind()
    : KeyCode(sf::Keyboard::Key::A), EventType(sf::Event::KeyPressed), InputType(Keyboard) {}

KeyBind::KeyBind(const INPUT_TYPE inputType, const sf::Keyboard::Key &key,
                 const sf::Event::EventType &event)
    : KeyCode(key), EventType(event), InputType(inputType) {}

KeyBind::KeyBind(const INPUT_TYPE inputType, const sf::Mouse::Button &button,
                 const sf::Event::EventType &event)
    : MouseButton(button), EventType(event), InputType(inputType) {}

KeyBind::~KeyBind() {}

KeyBind::KeyBind(const KeyBind &other)
    : InputType(other.InputType), EventType(other.EventType), KeyCode(other.KeyCode),
      MouseButton(other.MouseButton) {}

bool KeyBind::testEvent(const KeyBind &k, const sf::Event &e) const {
  // Mouse event
  if (k.InputType == Mouse && k.EventType == e.type && k.MouseButton == e.mouseButton.button) {
    return true;
  }
  // Keyboard event
  if (k.InputType == Keyboard && k.EventType == e.type && k.KeyCode == e.key.code) {
    return true;
  }

  return false;
}

/* bool */
/* KeyBind::eq(const KeyBind& k) */
/* { */
/*    if (this->InputType == k.InputType) { */
/*       if (this->InputType == Keyboard) { */
/*          if (this->KeyCode == k.KeyCode) { */
/*             return true; */
/*          } */
/*       } else if (this->InputType == Mouse) { */
/*          if (this->MouseButton == k.MouseButton) { */
/*             return true; */
/*          } */
/*       } */
/*    } */

/*    return false; */
/* } */
bool operator==(const KeyBind &k1, const KeyBind &k2) {
  if (k1.InputType == k2.InputType) {
    if (k1.InputType == Keyboard) {
      if (k1.KeyCode == k2.KeyCode) {
        return true;
      }
    } else if (k1.InputType == Mouse) {
      if (k1.MouseButton == k2.MouseButton) {
        return true;
      }
    }
  }

  return false;
}

/**********************************************************************
 *                         Cheatsheet members                         *
 **********************************************************************/

Cheatsheet *Cheatsheet::csInstance = nullptr;

/*! \brief Class constructor
 *  Cheatsheet class constructor */
Cheatsheet::Cheatsheet() {
  assert(csInstance == nullptr);

  csInstance = this;
}

/*! \brief Class deconstructor
 *  Cheatsheet class deconstructor */
Cheatsheet::~Cheatsheet() {}

/*! \brief Key code getter
 *  Name-base key code getter
 * \param const std::string& name Mapped action name
 * \return SFML key code */
KeyBind &Cheatsheet::GetKey(std::string const &name) {
  auto &kc = csInstance->_codes;
  auto pairFound = kc.find(name);

  assert(pairFound != kc.end());
  return pairFound->second;
}

/*! \brief Setting new map entry
 *  Setting new map entry
 * \param name name of key action
 * \param key key code
 * \return true if key action name already not used, false if in-use */
bool Cheatsheet::AddKey(const std::string &name, const KeyBind &key) {
  auto &kc = csInstance->_codes;
  if (!csInstance->IsMapped(key)) {
    kc[name] = key;
    return true;
  }
  return false;
}

/*! \brief Check for mapped keys
 *  Check for key is mapped
 * \param key key code
 * \return true if key not mapped, false if in-use */
bool Cheatsheet::IsMapped(KeyBind const &key) {
  auto &kc = csInstance->_codes;
  for (auto it = kc.begin(); it != kc.end(); ++it) {
    if (it->second == key) {
      return true;
    }
  }

  return false;
}
