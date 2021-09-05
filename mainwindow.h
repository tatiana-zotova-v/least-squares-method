#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "lsm.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void drawAxes(QPixmap& graph, QPainter& paint, bool notEmpty);
    void drawGraphs();
    void draw(QPixmap& graph, QPainter& paint);
    void clear();
    double polinome(double x, double a, double b, double c);
    double line(double x, double b, double c);

private slots:
    void on_exit_clicked();
    void on_draw_clicked();
    void on_clear_clicked();

private:
    Ui::MainWindow *ui;
    double leftX, rightX, leftY, rightY;
    double pixX, pixY, Ox, Oy;
    int width, height;
    double step;
};
#endif // MAINWINDOW_H
