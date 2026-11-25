#pragma once

#include <cstring>

inline void bzero(void *buffer, size_t size) {
  std::memset(buffer, 0, size);
}
