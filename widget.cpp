#include "widget.h"
#include <QPainter>
#include <QMouseEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);    // get rid of those jagged rounded corners
    QPen pen(Qt::black);
    pen.setWidth(4);
    painter.setPen(pen);
    QRect r = rect().adjusted(10, 10, -10, -50);    // bring the rectangle inward. creates a margin
    painter.drawRoundedRect(r, 20, 10);

    // painter.save() stores all parameters of the painter in an internal stack.
    // We can then modify the painter state (by changing its a ributes, applying transforma ons, and so on) and then,
    // if at any point we want to go back to the saved state, it is enough to call painter.restore() to undo all the modifications in one go
    painter.save();

    // The save() and restore() methods can be called as many  mes as needed.
    // Just remember to always pair a call to save() with a similar call to restore(), or the internal painter state will get corrupted.
    // Each call to restore() will revert the painter to the last saved state.

    // After the state is saved, we modify the rectangle again by adjusting for the width of the border.
    r.adjust(2, 2, -2, -2);

    // Then, we set the new rectangle as the viewport, informing the painter about the physical range of coordinates to operate on
    painter.setViewport(r);

    // Then we move the rectangle by half its height and set that as the painter window.
    // This effectively puts the origin of the painter at half the height of the widget.
    r.moveTo(0, -r.height()/2);

    painter.setWindow(r);

    painter.setClipRect(r);

    // Then, the drawChart() method is called whereby a red line is drawn on the x axis of the new coordinate system.
    drawSelection(&painter, r);
    drawChart(&painter, r);
    painter.restore();
}

void Widget::drawChart(QPainter *painter, const QRect &rect)
{
    painter->setPen(Qt::red);
    painter->drawLine(0, 0, rect.width(), 0);

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->setPen(Qt::blue);

    for(int i=0;i < m_points.size(); ++i) {
        if(m_selectionStart <= i && m_selectionEnd >=i) {
            painter->setPen(Qt::white);
        }else
            painter->setPen(Qt::blue);

        painter->drawLine(i, -m_points.at(i), i, m_points.at(i));
    }

    painter->restore();
}

void Widget::drawSelection(QPainter *painter, const QRect &rect) {
     if(m_selectionStart < 0 ) return;
     painter->save();
     painter->setPen(Qt::NoPen);
     painter->setBrush(palette().highlight());
     QRect selectionRect = rect;
     selectionRect.setLeft(m_selectionStart);
     selectionRect.setRight(m_selectionEnd);
     painter->drawRect(selectionRect);
     painter->restore();
}

void Widget::mousePressEvent(QMouseEvent *mouseEvent) {
    m_selectionStart = m_selectionEnd = mouseEvent->pos().x() - 12;
    emit selectionChanged(m_selectionStart);
    update();
  }

void Widget::mouseMoveEvent(QMouseEvent *mouseEvent) {
    m_selectionEnd = mouseEvent->pos().x() - 12;
    emit selectionChanged(m_selectionEnd);
    update();
 }


