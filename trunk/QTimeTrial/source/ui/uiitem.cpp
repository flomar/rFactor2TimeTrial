// uiitem.cpp

#include <ui/uiitem.h>

UiItem::UiItem() :
    colorBackground(QColor(0, 0, 0, 255)),
    colorBorder(QColor(255, 255, 255, 255)),
    colorButtonBackground(QColor(0, 0, 0, 255)),
    colorButtonBackgroundHovered(QColor(25, 25, 25, 255)),
    colorButtonBorder(QColor(255, 255, 255, 255)),
    colorButtonBorderHovered(QColor(255, 255, 0, 255)),
    colorButtonText(QColor(255, 255, 255, 255)),
    colorButtonTextHovered(QColor(255, 255, 0, 255)) {

}

UiItem::~UiItem() {

}

