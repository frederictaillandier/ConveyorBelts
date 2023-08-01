#pragma once
#include "iinput-dispatcher.h"
#include <functional>
#include <map>

class InputDispatcher : public IInputDispatcher {
  std::map<char, std::function<void()>> _callbacks;

public:
  void EventLoop() override;
  void SetOnKeyPressedCallback(char c,
                               std::function<void()> const &callback) override;
};