#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QMainWindow>
#include <QPieSeries>
#include <QPieSlice>
#include <qchartview.h>
#include <qnamespace.h>
#include <qpen.h>
#include <qpieseries.h>

#include "window.h"
#include "ui_learn_charts.h"

MainWindow::MainWindow(QWidget* parent) : ::QMainWindow(parent), _ui(new Ui::MainWindow()) {
    _ui->setupUi(this);

    // this->setup_bar();
    this->setup_pie();
}

void MainWindow::setup_bar() {
    ::QBarSet* set0 = new QBarSet("Jane");
    ::QBarSet* set1 = new QBarSet("John");
    ::QBarSet* set2 = new QBarSet("Axel");
    ::QBarSet* set3 = new QBarSet("Mary");
    ::QBarSet* set4 = new QBarSet("Samantha");

    *set0 << 10 << 20 << 30 << 40 << 50 << 60;
    *set1 << 50 << 70 << 40 << 45 << 80 << 70;
    *set2 << 30 << 50 << 80 << 13 << 80 << 50;
    *set3 << 50 << 60 << 70 << 30 << 40 << 25;
    *set4 << 90 << 70 << 50 << 30 << 16 << 42;

    ::QBarSeries* series = new ::QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);

    ::QChart* chart = new ::QChart();
    chart->addSeries(series);
    chart->setTitle("Student Performance");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    ::QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
    ::QBarCategoryAxis* axis = new ::QBarCategoryAxis();
    axis->append(categories);
    series->attachAxis(axis);

    chart->createDefaultAxes();
    assert(chart->axes(Qt::Horizontal).size() == 1);
    chart->removeAxis(chart->axes(Qt::Horizontal).at(0));

    chart->addAxis(axis, Qt::AlignBottom);

    auto chartview = new QChartView(chart);
    chartview->setParent(_ui->verticalFrame);
}

void MainWindow::setup_pie() {
    auto series = new ::QPieSeries();
    series->append("Jane", 10);
    series->append("Joe", 20);
    series->append("Andy", 30);
    series->append("Barbara", 40);
    series->append("Jason", 50);

    auto slice = series->slices().at(1);
    slice->setExploded();
    slice->setLabelVisible();
    slice->setPen(::QPen(::Qt::darkGreen, 2));
    slice->setBrush(::Qt::green);

    auto chart = new ::QChart();
    chart->addSeries(series);
    chart->setTitle("Students Performance");

    auto chartview = new ::QChartView(chart);
    chartview->setParent(_ui->verticalFrame);
}

MainWindow::~MainWindow() {
    delete _ui;
}
