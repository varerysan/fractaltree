#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <cmath>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget) {
    ui->setupUi(this);
    ui->angle1Slider->setValue(12);
}

void Widget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    drawBranch(p, QLineF(QPointF(300, 500), QPointF(310, 300)));
}

QPointF Widget::rotatePoint(QPointF R, float angle) {
    float x1 = R.x();
    float y1 = R.y();

    float x2 = x1 * cos(angle) - y1 * sin(angle);
    float y2 = x1 * sin(angle) + y1 * cos(angle);

    auto R2 = QPointF(x2, y2);
    return R2;
}

QLineF Widget::createLine(QLineF lineAB, float mid, float angle, float len) {
    //
    auto A = lineAB.p1();
    auto B = lineAB.p2();

    auto R1 = B - A;
    auto R2 = rotatePoint(R1, angle);

    auto P = R2 * len;

    auto M = lineAB.pointAt(mid);

    auto resP1 = M + P;
    return QLineF(M, resP1);
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


void Widget::on_angle1Slider_valueChanged(int)
{
    update();
}
