// uiitem.h

#ifndef _UIITEM_H_
#define _UIITEM_H_

#include <main.h>

class UiItem {
public:
    UiItem();
    virtual ~UiItem();
protected:
    const QColor colorBackground;
    const QColor colorBorder;
    const QColor colorButtonBackground;
    const QColor colorButtonBackgroundHovered;
    const QColor colorButtonBorder;
    const QColor colorButtonBorderHovered;
    const QColor colorButtonText;
    const QColor colorButtonTextHovered;
};

#endif
