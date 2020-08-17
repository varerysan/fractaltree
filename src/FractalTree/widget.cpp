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
    drawBranch(p, QPointF(300, 500), QPointF(200, 100));
}

void Widget::drawBranch(QPainter &p, QPointF p1, QPointF p2) {
    p.drawLine(p1,p2);
    float rate = 0.3;
    auto vect = p2 - p1;

    auto midP = p1 + vect * rate;

    p.drawEllipse(midP, 3, 3);

    float angle1 = 0.3;
    float angle2 = 0.5;

    for (angle1 = 0; angle1 < 6.28; angle1 += 0.1) {
    //    float len1 = sqrt(QPointF::dotProduct(vect, vect));
        float x = vect.x() * cos(angle1) - vect.y() * sin(angle1);
        float y = vect.x() * sin(angle1) + vect.y() * cos(angle1);
        auto resP1 = p1 + QPointF(x, y);
        p.drawLine(p1, resP1);
        p.drawEllipse(resP1, 5, 5);
    }

}

Widget::~Widget() {
    delete ui;
}

