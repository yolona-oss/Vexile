// https://github.com/johnBuffer/SFML-EventManager/blob/master/inlcude/event_manager.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <unordered_map>

namespace sfev {

// Helper using for shorter types
using EventCallback = std::function<void(const sf::Event &event)>;

template <typename T> using EventCallbackMap = std::unordered_map<T, EventCallback>;

using CstEv = const sf::Event &;

/*
 * This class handles subtyped events like keyboard or mouse events
 * The unpack function allows to get relevant information from the processed event
 */
template <typename T> class SubTypeManager {
public:
  SubTypeManager(std::function<T(const sf::Event &)> unpack) : m_unpack(unpack) {}
  ~SubTypeManager() = default;

  void processEvent(const sf::Event &event) const {
    T sub_value = m_unpack(event);
    auto it(m_callmap.find(sub_value));
    if (it != m_callmap.end()) {
      // Call its associated callback
      (it->second)(event);
    }
  }

  void addCallback(const T &sub_value, EventCallback callback) { m_callmap[sub_value] = callback; }

private:
  EventCallbackMap<T> m_callmap;
  std::function<T(const sf::Event &)> m_unpack;
};

class EventMap {
public:
  EventMap(bool use_builtin_helpers = true)
      : m_key_pressed_manager([](const sf::Event &event) { return event.key.code; }),
        m_key_released_manager([](const sf::Event &event) { return event.key.code; }),
        m_mouse_pressed_manager([](const sf::Event &event) { return event.mouseButton.button; }),
        m_mouse_released_manager([](const sf::Event &event) { return event.mouseButton.button; }) {
    if (use_builtin_helpers) {
      // Register key events built in callbacks
      this->addEventCallback(sf::Event::EventType::KeyPressed, [&](const sf::Event &event) {
        m_key_pressed_manager.processEvent(event);
      });
      this->addEventCallback(sf::Event::EventType::KeyReleased, [&](const sf::Event &event) {
        m_key_released_manager.processEvent(event);
      });
      this->addEventCallback(sf::Event::EventType::MouseButtonPressed, [&](const sf::Event &event) {
        m_mouse_pressed_manager.processEvent(event);
      });
      this->addEventCallback(
          sf::Event::EventType::MouseButtonReleased,
          [&](const sf::Event &event) { m_mouse_released_manager.processEvent(event); });
    }
  }

  // Attaches new callback to an event
  void addEventCallback(sf::Event::EventType type, EventCallback callback) {
    m_events_callmap[type] = callback;
  }

  // Adds a key pressed callback
  void addKeyPressedCallback(sf::Keyboard::Key key_code, EventCallback callback) {
    m_key_pressed_manager.addCallback(key_code, callback);
  }

  // Adds a key released callback
  void addKeyReleasedCallback(sf::Keyboard::Key key_code, EventCallback callback) {
    m_key_released_manager.addCallback(key_code, callback);
  }

  // Adds a mouse pressed callback
  void addMousePressedCallback(sf::Mouse::Button button, EventCallback callback) {
    m_mouse_pressed_manager.addCallback(button, callback);
  }

  // Adds a mouse released callback
  void addMouseReleasedCallback(sf::Mouse::Button button, EventCallback callback) {
    m_mouse_released_manager.addCallback(button, callback);
  }

  // Runs the callback associated with an event
  void executeCallback(const sf::Event &e, EventCallback fallback = nullptr) const {
    auto it(m_events_callmap.find(e.type));
    if (it != m_events_callmap.end()) {
      // Call its associated callback
      (it->second)(e);
    } else if (fallback) {
      fallback(e);
    }
  }

  // Removes a callback
  void removeCallback(sf::Event::EventType type) {
    // If event type is registred
    auto it(m_events_callmap.find(type));
    if (it != m_events_callmap.end()) {
      // Remove its associated callback
      m_events_callmap.erase(it);
    }
  }

private:
  SubTypeManager<sf::Keyboard::Key> m_key_pressed_manager;
  SubTypeManager<sf::Keyboard::Key> m_key_released_manager;
  SubTypeManager<sf::Mouse::Button> m_mouse_pressed_manager;
  SubTypeManager<sf::Mouse::Button> m_mouse_released_manager;
  EventCallbackMap<sf::Event::EventType> m_events_callmap;
};

/*
    This class handles any type of event and call its associated callbacks if any.
    To process key event in a more convenient way its using a KeyManager
*/
class EventManager {
public:
  EventManager(sf::Window &window, bool use_builtin_helpers)
      : m_window(window), m_event_map(use_builtin_helpers) {}

  // Calls events' attached callbacks
  void processEvents(EventCallback fallback = nullptr) const {
    // Iterate over events
    sf::Event event;
    while (m_window.pollEvent(event)) {
      m_event_map.executeCallback(event, fallback);
    }
  }

  // Attaches new callback to an event
  void addEventCallback(sf::Event::EventType type, EventCallback callback) {
    m_event_map.addEventCallback(type, callback);
  }

  // Removes a callback
  void removeCallback(sf::Event::EventType type) { m_event_map.removeCallback(type); }

  // Adds a key pressed callback
  void addKeyPressedCallback(sf::Keyboard::Key key, EventCallback callback) {
    m_event_map.addKeyPressedCallback(key, callback);
  }

  // Adds a key released callback
  void addKeyReleasedCallback(sf::Keyboard::Key key, EventCallback callback) {
    m_event_map.addKeyReleasedCallback(key, callback);
  }

  // Adds a mouse pressed callback
  void addMousePressedCallback(sf::Mouse::Button button, EventCallback callback) {
    m_event_map.addMousePressedCallback(button, callback);
  }

  // Adds a mouse released callback
  void addMouseReleasedCallback(sf::Mouse::Button button, EventCallback callback) {
    m_event_map.addMouseReleasedCallback(button, callback);
  }

  sf::Window &getWindow() { return m_window; }

  sf::Vector2f getFloatMousePosition() const {
    const sf::Vector2i mouse_position = sf::Mouse::getPosition(m_window);
    return {static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y)};
  }

  sf::Vector2i getMousePosition() const { return sf::Mouse::getPosition(m_window); }

private:
  sf::Window &m_window;
  EventMap m_event_map;
};
} // namespace sfev

// #pragma once
//
// #include <SFML/Config.hpp>
// #include <SFML/Graphics/RenderWindow.hpp>
// #include <SFML/System/Vector2.hpp>
// #include <SFML/Window/Event.hpp>
// #include <string>
// #include <unordered_map>
// #include <vector>
// #include <functional>
//
// enum class EventType {
//         KeyDown       = sf::Event::KeyPressed,
//         KeyUp         = sf::Event::KeyReleased,
//         MouseMoved    = sf::Event::MouseMoved,
//         MButtonDown   = sf::Event::MouseButtonPressed,
//         MButtonUp     = sf::Event::MouseButtonReleased,
//         MouseWheel    = sf::Event::MouseWheelMoved,
//         WindowResized = sf::Event::Resized,
//         GainedFocus   = sf::Event::GainedFocus,
//         LostFocus     = sf::Event::LostFocus,
//         MouseEntered  = sf::Event::MouseEntered,
//         MouseLeft     = sf::Event::MouseLeft,
//         Closed        = sf::Event::Closed,
//         TextEntered   = sf::Event::TextEntered,
//         Keyboard      = sf::Event::Count + 1,
//         Mouse,
//         Joystick,
// };
//
// struct EventInfo {
//         EventInfo() { m_code = 0; }
//         EventInfo(int l_event) { m_code = l_event; }
//         union {
//                 int m_code;
//         };
// };
//
// using Events = std::vector<std::pair<EventType, EventInfo>>;
//
// struct EventDetails {
//         EventDetails(const std::string& l_bindName)
//                 : m_name(l_bindName)
//         {
//                 Clear();
//         }
//
//         std::string m_name;
//         sf::Vector2i m_size;
//         sf::Uint32 m_textEntered;
//         sf::Vector2i m_mouse;
//         int m_mouseWheelDelta;
//         int m_keyCode; // Single key code.
//
//         void Clear() {
//                 m_size = sf::Vector2i(0, 0);
//                 m_textEntered = 0;
//                 m_mouse = sf::Vector2i(0, 0);
//                 m_mouseWheelDelta = 0;
//                 m_keyCode = -1;
//         }
// };
//
// struct Binding {
//         Binding(const std::string& l_name)
//                 : m_name(l_name), m_details(l_name), c(0)
//         { }
//         void BindEvent(EventType l_type,
//                        EventInfo l_info = EventInfo())
//         {
//                 m_events.emplace_back(l_type, l_info);
//         }
//         Events m_events;
//         std::string m_name;
//         int c; // Count of events that are "happening".
//         EventDetails m_details;
// };
//
// using Bindings = std::unordered_map<std::string, Binding*>;
//
// template <class T>
// using Function = void (T::*)();
//
// template<class T>
// struct Callback {
//         std::string m_name;
//         T* CallbackInstance; // Pointer to instance.
//         void (T::*_callback)();
//         void Call() {
//                 CallbackInstance->*_callback();
//         }
// };
//
// using Callbacks = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
//
// class EventManager {
// public:
//         EventManager();
//         virtual ~EventManager();
//
//         bool AddBinding(Binding *l_binding);
//         bool RemoveBinding(std::string l_name);
//         void SetFocus(const bool& l_focus);
//
//         template<class T>
//         bool AddCallback(const std::string& l_name,
//                          void(T::*l_func)(EventDetails*), T* l_instance)
//         {
//                 auto temp = std::bind(l_func, l_instance,
//                                       std::placeholders::_1);
//                 return m_callbacks.emplace(l_name, temp).second;
//         }
//
//         void RemoveCallback(const std::string& l_name) {
//                 m_callbacks.erase(l_name);
//         }
//
//         void HandleEvent(sf::Event& l_event);
//         void Update();
//         sf::Vector2i GetMousePos(sf::RenderWindow* l_wind = nullptr)
//         {
//                 return (l_wind ? sf::Mouse::getPosition(*l_wind)
//                                : sf::Mouse::getPosition());
//         }
// private:
//         void LoadBindings();
//
//         Bindings m_bindings;
//         Callbacks m_callbacks;
//         bool m_hasFocus;
// };
