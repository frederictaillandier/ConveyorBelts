#pragma once
#include "belt/ibelt.h"
#include "displayer/idisplayer.h"
#include <atomic>
#include <thread>
#include <vector>

class Belt : public IBelt {
private:
  unsigned int _id = 0;

  std::jthread thread = std::jthread(&Belt::EventLoop, this);
  constexpr static float BELT_SIZE = 10;
  float _beltSpeed = 1;

  std::atomic<bool> _killCalled = false;
  std::atomic<bool> _paused = false;

  std::weak_ptr<IBelt> _nextBelt;
  std::weak_ptr<IBelt> _previousBelt;
  std::shared_ptr<IDisplayer> _displayer;

  std::vector<std::unique_ptr<Luggage>> _luggages;
  std::atomic<size_t> _luggagesCount = 0;
  std::vector<std::unique_ptr<Luggage>> _fallingLuggages;
  std::mutex _fallingLuggagesMutex;

  void EventLoop();
  void Update();
  void ProcessFallingLuggages();
  void ProcessLuggagesOnBelt();

public:
  unsigned int GetId() const override;
  void Resume() override;
  void Pause() override;
  void Reverse() override;
  void SwitchOnOff() override;
  ~Belt() override;
  void SetNextBelt(std::weak_ptr<IBelt> nextBelt) override;
  void SetPreviousBelt(std::weak_ptr<IBelt> previousBelt) override;
  void DropLuggageFront(std::unique_ptr<Luggage> luggage) override;
  void DropLuggageBack(std::unique_ptr<Luggage> luggage) override;
  size_t GetLuggageNumber() const override;

  friend class BeltFactory;
};
