#pragma once
#include <functional>

/*
 * This class is responsible for dispatching input events to the rest of the
 * application.
 */
class IInputDispatcher {
public:
  static constexpr char QUIT_KEY = 'q';
  static constexpr char LUGGAGE_KEY = 'l';
  static constexpr char BELT_1_KEY = '1';
  static constexpr char REVERSE_BELTS = 'r';

  virtual ~IInputDispatcher() = default;

  /*
   * Set a callback to be called when a key is pressed.
   */
  virtual void
  SetOnKeyPressedCallback(char c, std::function<void()> const &callback) = 0;

  /*
   * Start the event loop to capture the input events.
   */
  virtual void EventLoop() = 0;
};
