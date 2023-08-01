#pragma once
#include <functional>

class IInputDispatcher {
public:
  virtual ~IInputDispatcher() = default;
  virtual void
  SetOnKeyPressedCallback(char c, std::function<void()> const &callback) = 0;
  virtual void EventLoop() = 0;
};
