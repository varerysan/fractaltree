#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <cmath>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget) {
    ui->setupUi(this);
}

void Widget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    drawBranch(p, QLineF(QPointF(300, 500), QPointF(310, 300)));
}

QLineF Widget::createLine(QLineF line, float mid, float angle, float len) {
    //
    auto vect = line.p2() - line.p1();
    auto midP = line.pointAt(mid);
    auto vect1 = vect * len;

    float x = vect1.x() * cos(angle) - vect1.y() * sin(angle);
    float y = vect1.x() * sin(angle) + vect1.y() * cos(angle);
    auto resP1 = midP + QPointF(x, y);

    return QLineF(midP, resP1);
}

void Widget::drawBranch(QPainter &p, QLineF line) {
    //
    float len = line.length();
    if (len < 3) {
        return;
    }

    p.drawLine(line);

    float mid1 = 0.9f;
    float angle1 = 0.3f;
    angle1 = 6.28f * (static_cast<float>(ui->angle1Slider->value()) / ui->angle1Slider->maximum());
    float len1 = 0.5f;
    auto line1 = createLine(line, mid1, angle1, len1);
    drawBranch(p, line1);

    float mid2 = 0.9f;
    float angle2 = -0.5f;
    float len2 = 0.7f;
    auto line2 = createLine(line, mid2, angle2, len2);
    drawBranch(p, line2);

}

Widget::~Widget() {
    delete ui;
}


void Widget::on_angle1Slider_valueChanged(int value)
{
    update();
}
