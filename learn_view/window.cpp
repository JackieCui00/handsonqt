#include "window.h"
#include "ui_learn_view.h"

#include <QDebug>
#include <QListWidgetItem>

MainWindow::MainWindow(::QWidget* parent) : ::QMainWindow(parent), _ui(new Ui::MainWindow()) {
    _ui->setupUi(this);

    { // setup the list widget
        _ui->listWidget->addItem("Cuijiacheng");

        auto list_item = new ::QListWidgetItem();
        list_item->setText("My second item");
        list_item->setData(100, 1000);
        _ui->listWidget->addItem(list_item);

        connect(_ui->listWidget, &::QListWidget::itemClicked, this, &MainWindow::on_list_item_clicked);
    }

    { // setup the tree widget
        auto item1 = new ::QTreeWidgetItem();
        item1->setText(0, "Cuijiacheng in tree");
        _ui->treeWidget->addTopLevelItem(item1);

        auto item2 = new ::QTreeWidgetItem();
        item2->setText(0, "my test Subitem");
        item1->addChild(item2);
    }

    { // setup the table widget
        auto item1 = new ::QTableWidgetItem();
        item1->setText("Cuijiacheng in table");
        _ui->tableWidget->setItem(0, 0, item1);

        auto item2 = new ::QTableWidgetItem();
        item2->setText("my test table item");
        _ui->tableWidget->setItem(1, 2, item2);
    }
}

MainWindow::~MainWindow() {
    delete _ui;
}

void MainWindow::on_list_item_clicked(::QListWidgetItem* item) {
    qDebug() << "item:" << item->text() << ", data:" << item->data(100);
}
