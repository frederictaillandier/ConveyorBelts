#pragma once

/*
 * brief : Listen the luggages updates and display them
 */
class IDisplayer {
public:
  virtual ~IDisplayer() = default;

  /*
   * brief : Blocking event loop of the displayer
   */
  virtual void EventLoop() = 0;

  /*
   * brief : Must be called when a luggage moves on a belt
   * param id : Id of the luggage
   * param beltId : Id of the belt
   * param position : Position of the luggage on the belt
   */
  virtual void OnLuggageMove(unsigned int const id, unsigned int const beltId,
                             float position) = 0;
};