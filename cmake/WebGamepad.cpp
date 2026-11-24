#include "WebGamepad.h"

#include <emscripten.h>

EM_JS(void, RumbleWebGamepad, (float strength, int duration), {
  void (async () => {
    const gamepads = navigator.getGamepads?.();
    const gamepad = gamepads && Array.from(gamepads).find(
      pad => pad?.connected && pad.mapping === "standard"
    );
    if (!gamepad) return;

    const actuator = gamepad.vibrationActuator;
    if (actuator?.playEffect) {
      try {
        const result = await actuator.playEffect("dual-rumble", {
          duration,
          startDelay: 0,
          strongMagnitude: strength,
          weakMagnitude: strength
        });
        if (result === "complete" || result === "preempted") return;
      } catch {
        // Some controllers expose a pulse actuator even when dual rumble fails.
      }
    }

    const pulseActuator = actuator?.pulse ? actuator :
      Array.from(gamepad.hapticActuators ?? []).find(haptic => haptic?.pulse);
    await pulseActuator?.pulse(strength, duration);
  })().catch(() => {
    // Haptics are optional, and access can be blocked by the browser or embed.
  });
});
