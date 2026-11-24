#ifndef MODITE_WEB_GAMEPAD_H
#define MODITE_WEB_GAMEPAD_H

#include "Controls.h"
#include <cstring>
#include <emscripten/html5.h>

inline TUint16 ReadWebGamepad() {
  if (emscripten_sample_gamepad_data() != EMSCRIPTEN_RESULT_SUCCESS) {
    return 0;
  }

  constexpr TUint16 buttons[] = {
    BUTTONB, BUTTONA, BUTTONX, BUTTONY, BUTTONL, BUTTONR, 0, 0,
    BUTTON_SELECT, BUTTON_START, 0, 0, JOYUP, JOYDOWN, JOYLEFT, JOYRIGHT
  };
  constexpr double deadzone = 0.73;
  const int count = emscripten_get_num_gamepads();
  for (int index = 0; index < count; ++index) {
    EmscriptenGamepadEvent pad{};
    if (emscripten_get_gamepad_status(index, &pad) != EMSCRIPTEN_RESULT_SUCCESS ||
        !pad.connected || std::strcmp(pad.mapping, "standard") != 0) {
      continue;
    }

    TUint16 keys = 0;
    for (int button = 0; button < pad.numButtons && button < 16; ++button) {
      if (pad.digitalButton[button]) {
        keys |= buttons[button];
      }
    }
    if (pad.numAxes >= 2) {
      if (pad.axis[0] < -deadzone) keys |= JOYLEFT;
      if (pad.axis[0] > deadzone) keys |= JOYRIGHT;
      if (pad.axis[1] < -deadzone) keys |= JOYUP;
      if (pad.axis[1] > deadzone) keys |= JOYDOWN;
    }
    return keys;
  }
  return 0;
}

#endif
