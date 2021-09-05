#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    leftX = -0.5;
    rightX = 1.5;
    leftY = -1.5;
    rightY = 1.7;
    width = 300;
    height = 480;
    step = 0.0001;
    pixX = width / (rightX - leftX);
    pixY = height / (rightY - leftY);
    Ox = std::fabs(leftX);
    Oy = rightY;

    drawGraphs();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawAxes(QPixmap& graph, QPainter& paint, bool notEmpty){
    paint.begin(&graph);
    paint.eraseRect(0, 0, width, height);
    paint.drawLine(0, Oy * pixY, width, Oy * pixY);
    paint.drawLine(Ox * pixX, 0, Ox * pixX, height);

    paint.setPen(QPen(Qt::red, 2));
    for(const auto& i : coord){
        paint.drawPoint((Ox + i.first) * pixX, (Oy + (-1) * i.second) * pixY);
    }

    if(!notEmpty) {
        draw(graph, paint);
    }
}

void MainWindow::drawGraphs(){
    QPixmap graph(width, height);
    QPainter paint;

    drawAxes(graph, paint, 1);

    if(ui->quadratic->isChecked()){
        std::pair<double*, int> abc = abc_coef();

        QPainterPath path;
        bool first = true;
        for(double i = leftX; i <= rightX; i += step){
            if(!std::isnan(polinome(i, abc.first[0], abc.first[1], abc.first[2]))){
                if(first){
                    path.moveTo((i + Ox) * pixX,
                                (polinome(i, abc.first[0], abc.first[1], abc.first[2]) + Oy) * pixY);
                    first = false;
                } else {
                    path.lineTo((i + Ox) * pixX,
                                (polinome(i, abc.first[0], abc.first[1], abc.first[2]) + Oy) * pixY);
                }
            }
        }

        paint.setPen(QPen(Qt::darkGreen, 1, Qt::SolidLine));
        paint.setRenderHint(QPainter::Antialiasing, true);
        paint.drawPath(path);
    }

    if(ui->linear->isChecked()){
        paint.setPen(QPen(Qt::darkBlue, 1, Qt::SolidLine));
        std::pair<double*, int> bc = bc_coef();
        paint.drawLine((leftX + Ox) * pixX, (Oy * line(leftX, bc.first[0], bc.first[1])) * pixY, (rightX + Ox) * pixX, (Oy + line(rightX, bc.first[0], bc.first[1])) * pixY);
    }

    draw(graph, paint);
}

void MainWindow::draw(QPixmap& graph, QPainter& paint){
    paint.end();
    ui->Graph->setPixmap(graph);
    return;
}

void MainWindow::clear(){
    QPixmap graphs(width, height);
    QPainter paint;
    drawAxes(graphs, paint, 0);
}

double MainWindow::polinome(double x, double a, double b, double c){
    return (a * std::pow(x, 2) + b * x + c) * (-1);
}

double MainWindow::line(double x, double b, double c){
    return (b * x + c) * (-1);
}

void MainWindow::on_exit_clicked(){
    this->close();
}

void MainWindow::on_clear_clicked(){
    clear();
}

void MainWindow::on_draw_clicked(){
    drawGraphs();
}
