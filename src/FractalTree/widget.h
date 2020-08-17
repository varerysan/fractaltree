#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void drawBranch(QPainter &p, QLineF line);
    QLineF createLine(QLineF line, float mid, float angle, float len);
    ~Widget();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
