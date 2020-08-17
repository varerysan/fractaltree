#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <cmath>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget) {
    ui->setupUi(this);
}

void Widget::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    drawBranch(p, QLineF(QPointF(300, 500), QPointF(200, 100)));
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
    p.drawLine(line);
    float rate = 0.3f;

    float angle1 = 0.3f;
    float len1 = 0.5f;
    auto line1 = createLine(line, rate, angle1, len1);
    p.drawLine(line1);

    float angle2 = -0.5f;
    float len2 = 0.7f;
    auto line2 = createLine(line, rate, angle2, len2);
    p.drawLine(line2);
}

Widget::~Widget() {
    delete ui;
}

