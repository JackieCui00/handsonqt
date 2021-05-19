#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
} // namespace Ui

class MainWindow final : public ::QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void setup_bar();

    void setup_pie();

private:
    Ui::MainWindow* _ui;
};
