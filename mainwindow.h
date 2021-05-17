#pragma once

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
} // namespace Ui

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_submit();

private:
    Ui::MainWindow* _ui;

    QSqlDatabase _db;
};
