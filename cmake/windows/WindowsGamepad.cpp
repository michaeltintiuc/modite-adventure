#include "WindowsGamepad.h"

#include <SDL.h>
#include <algorithm>
#include <memory>

namespace {
using Controller = std::unique_ptr<SDL_GameController, decltype(&SDL_GameControllerClose)>;

Controller &ActiveController() {
  static Controller controller(nullptr, SDL_GameControllerClose);
  return controller;
}
}

TUint16 ReadWindowsGamepad() {
  static const bool initialized = SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) == 0;
  if (!initialized) {
    return 0;
  }

  auto &controller = ActiveController();
  SDL_PumpEvents();
  if (controller && !SDL_GameControllerGetAttached(controller.get())) {
    controller.reset();
  }

  if (!controller) {
    for (int index = 0; index < SDL_NumJoysticks(); ++index) {
      if (SDL_IsGameController(index)) {
        controller.reset(SDL_GameControllerOpen(index));
        if (controller) {
          break;
        }
      }
    }
  }

  if (!controller) {
    return 0;
  }

  constexpr TUint16 buttons[] = {
    BUTTONB, BUTTONA, BUTTONX, BUTTONY, BUTTON_SELECT, BUTTONQ, BUTTON_START,
    0, 0, BUTTONL, BUTTONR, JOYUP, JOYDOWN, JOYLEFT, JOYRIGHT
  };
  static_assert(SDL_CONTROLLER_BUTTON_DPAD_RIGHT + 1 == sizeof(buttons) / sizeof(buttons[0]),
                "Unexpected SDL controller button order");

  TUint16 keys = 0;
  for (int index = 0; index <= SDL_CONTROLLER_BUTTON_DPAD_RIGHT; ++index) {
    if (SDL_GameControllerGetButton(controller.get(), static_cast<SDL_GameControllerButton>(index))) {
      keys |= buttons[index];
    }
  }

  constexpr Sint16 deadzone = 24000;
  const Sint16 x = SDL_GameControllerGetAxis(controller.get(), SDL_CONTROLLER_AXIS_LEFTX);
  const Sint16 y = SDL_GameControllerGetAxis(controller.get(), SDL_CONTROLLER_AXIS_LEFTY);
  if (x < -deadzone) keys |= JOYLEFT;
  if (x > deadzone) keys |= JOYRIGHT;
  if (y < -deadzone) keys |= JOYUP;
  if (y > deadzone) keys |= JOYDOWN;
  return keys;
}

void RumbleWindowsGamepad(float strength, int duration) {
  auto &controller = ActiveController();
  if (!controller || !SDL_GameControllerGetAttached(controller.get())) {
    return;
  }

  const float normalized = std::max(0.0f, std::min(strength, 1.0f));
  const Uint16 magnitude = static_cast<Uint16>(normalized * 65535.0f);
  SDL_GameControllerRumble(controller.get(), magnitude, magnitude, duration);
}
