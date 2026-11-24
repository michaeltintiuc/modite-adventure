#include "GRumbleWidget.h"
#include "Game.h"

static const TRange rumbleOptions = {0, TOptions::RUMBLE_MAX, 1};

GRumbleWidget::GRumbleWidget()
  : GSoundSliderWidget("Rumble", &rumbleOptions, COLOR_TEXT, COLOR_TEXT_BG) {
  mHeight = 11;
}

TInt GRumbleWidget::Render(TInt aX, TInt aY) {
  mSelectedValue = gOptions->rumble;
  return GSoundSliderWidget::Render(aX, aY);
}

void GRumbleWidget::Select(TInt aVal) {
  if (gOptions->rumble == aVal) {
    return;
  }

  gOptions->rumble = aVal;
  gOptions->Save();
  GGame::RumbleImpact();
}
