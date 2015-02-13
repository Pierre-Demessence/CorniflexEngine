#pragma once

namespace corniflex {

class Event {
public:
  virtual ~Event() = 0;
};

inline Event::~Event() = default;

}
