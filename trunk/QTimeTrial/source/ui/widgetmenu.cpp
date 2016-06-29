// widgetmenu.cpp

#include <ui/widgetmenu.h>

#include <application.h>
#include <applicationdatabase.h>

#include <utilities.h>

WidgetMenu::WidgetMenu(QWidget *_parent) :
    Widget(_parent) {

}

WidgetMenu::~WidgetMenu() {
    // free memory
    deleteButtons();
}

void WidgetMenu::update() {
    Widget::update();
    updateButtons();
}

void WidgetMenu::enterEvent(QEvent *_event) {
    Q_UNUSED(_event);
    // set all buttons to non-hovered
    foreach(Button *button, vectorButtons) {
        if(button) {
            button->hovered = false;
        }
    }
    repaint();
}

void WidgetMenu::leaveEvent(QEvent *_event) {
    Q_UNUSED(_event);
    // set all buttons to non-hovered
    foreach(Button *button, vectorButtons) {
        if(button) {
            button->hovered = false;
        }
    }
    repaint();
}

void WidgetMenu::mouseMoveEvent(QMouseEvent *_event) {
    foreach(Button *button, vectorButtons) {
        if(button) {
            button->hovered = isButtonHovered(button, _event->pos());
        }
    }
    repaint();
}

void WidgetMenu::mousePressEvent(QMouseEvent *_event) {
    foreach(Button *button, vectorButtons) {
        if(button) {
            if(button->hovered) {
                Qt::MouseButton mouseButton;
                if(_event->buttons() & Qt::LeftButton) {
                    mouseButton = Qt::LeftButton;
                }
                if(_event->buttons() & Qt::RightButton) {
                    mouseButton = Qt::RightButton;
                }
                if(mouseButton == Qt::LeftButton || mouseButton == Qt::RightButton) {
                    if(button->text == "ABOUT") {
                        emit signalPressedButtonAbout(mouseButton);
                        return;
                    }
                    if(button->text == "RECORDS") {
                        emit signalPressedButtonRecords(mouseButton);
                        return;
                    }
                    if(button->text == "DRIVERS") {
                        emit signalPressedButtonDrivers(mouseButton);
                        return;
                    }
                    if(button->text == "OPTIONS") {
                        emit signalPressedButtonOptions(mouseButton);
                        return;
                    }
                    if(button->text == "QUIT") {
                        emit signalPressedButtonQuit(mouseButton);
                        return;
                    }
                }
            }
        }
    }
}

void WidgetMenu::paintEvent(QPaintEvent *_event) {
    Widget::paintEvent(_event);
    QPainter painter(this);
    // acquire border rect and background rect
    const QRect rectBorder = rect();
    const QRect rectBackground = Utilities::Graphics::getRectInset(rectBorder, 0);
    // draw border
    painter.setBrush(colorBorder);
    painter.drawRect(rectBorder);
    // draw background
    painter.setBrush(colorBackground);
    painter.drawRect(rectBackground);
    // draw buttons
    foreach(const Button *button, vectorButtons) {
        if(button) {
            painter.drawPixmap(button->rect, button->hovered ? button->pixmapHovered : button->pixmap);
        }
    }
}

void WidgetMenu::updateButtons() {
    // initialize temporary variables
    const int buttonWidth = rect().width();
    const int buttonHeight = rect().width() * 3;
    const int buttonMargin = 4;
    // delete existing buttons
    deleteButtons();
    // create buttons
    Button *buttonAbout = new Button();
    Button *buttonRecords = new Button();
    Button *buttonDrivers = new Button();
    Button *buttonOptions = new Button();
    Button *buttonQuit = new Button();
    // initialize button rect variables
    buttonAbout->rect = QRect(rect().x(), rect().y(), buttonWidth, buttonHeight);
    buttonRecords->rect = QRect(rect().x(), rect().y() + buttonHeight + buttonMargin, buttonWidth, buttonHeight);
    buttonDrivers->rect = QRect(rect().x(), rect().y() + buttonHeight * 2 + buttonMargin * 2, buttonWidth, buttonHeight);
    buttonOptions->rect = QRect(rect().x(), rect().y() + buttonHeight * 3 + buttonMargin * 3, buttonWidth, buttonHeight);
    buttonQuit->rect = QRect(rect().x(), rect().y() + rect().height() - buttonHeight, buttonWidth, buttonHeight);
    // initialize button text variables
    buttonAbout->text = "ABOUT";
    buttonRecords->text = "RECORDS";
    buttonDrivers->text = "DRIVERS";
    buttonOptions->text = "OPTIONS";
    buttonQuit->text = "QUIT";
    // add buttons to vector
    vectorButtons.push_back(buttonAbout);
    vectorButtons.push_back(buttonRecords);
    vectorButtons.push_back(buttonDrivers);
    vectorButtons.push_back(buttonOptions);
    vectorButtons.push_back(buttonQuit);
    // initialize button pixmap variables
    foreach(Button *button, vectorButtons) {
        const int borderThickness = 3;
        const QRect rectBorder = QRect(0, 0, button->rect.width(), button->rect.height());
        const QRect rectBackground = Utilities::Graphics::getRectInset(rectBorder, borderThickness);
        const int fontSize = rectBorder.width() * 0.30;
        // pixmap normal
        button->pixmap = QPixmap(rectBorder.size());
        QPainter painter(&button->pixmap);
        painter.setBrush(colorButtonBorder);
        painter.drawRect(rectBorder);
        painter.setBrush(colorButtonBackground);
        painter.drawRect(rectBackground);
        painter.setPen(colorButtonText);
        // text normal (needs to be rotated)
        painter.rotate(-90);
        painter.translate(0, fontSize / 2);
        painter.setFont(QFont("Bitwise", fontSize));
        painter.drawText(QRect(0, 0, -rectBackground.height(), +rectBackground.width()), Qt::AlignCenter, button->text);
        // pixmap hovered
        button->pixmapHovered = QPixmap(rectBorder.size());
        QPainter painterHovered(&button->pixmapHovered);
        painterHovered.setBrush(colorButtonBorderHovered);
        painterHovered.drawRect(rectBorder);
        painterHovered.setBrush(colorButtonBackgroundHovered);
        painterHovered.drawRect(rectBackground);
        painterHovered.setPen(colorButtonTextHovered);
        // text hovered (needs to be rotated)
        painterHovered.rotate(-90);
        painterHovered.translate(0, fontSize / 2);
        painterHovered.setFont(QFont("Bitwise", fontSize));
        painterHovered.drawText(QRect(0, 0, -rectBackground.height(), +rectBackground.width()), Qt::AlignCenter, button->text);
    }
    // call explicit repaint
    repaint();
}

void WidgetMenu::deleteButtons() {
    foreach(Button *button, vectorButtons) {
        delete button;
    }
    vectorButtons.clear();
}

bool WidgetMenu::isButtonHovered(const Button *_button, const QPoint &_point) const {
    if(_button) {
        if(_point.x() < _button->rect.x()) return false;
        if(_point.x() > _button->rect.x() + _button->rect.width()) return false;
        if(_point.y() < _button->rect.y()) return false;
        if(_point.y() > _button->rect.y() + _button->rect.height()) return false;
        return true;
    }
    return false;
}
