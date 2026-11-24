#ifndef MODITE_GRUMBLEWIDGET_H
#define MODITE_GRUMBLEWIDGET_H

#include "GSoundSliderWidget.h"

class GRumbleWidget : public GSoundSliderWidget {
public:
  GRumbleWidget();
  TInt Render(TInt aX, TInt aY) OVERRIDE;
  void Select(TInt aVal) OVERRIDE;
};

#endif
