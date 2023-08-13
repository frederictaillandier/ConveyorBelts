#pragma once
#include <functional>

class IInputDispatcher {
public:
  static constexpr char QUIT_KEY = 'q';
  static constexpr char LUGGAGE_KEY = 'l';
  static constexpr char BELT_1_KEY = '1';

  virtual ~IInputDispatcher() = default;
  virtual void
  SetOnKeyPressedCallback(char c, std::function<void()> const &callback) = 0;
  virtual void EventLoop() = 0;
};
