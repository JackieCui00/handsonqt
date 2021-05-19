#pragma once

#include <QMainWindow>
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
} // namespace Ui

class MainWindow : public ::QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(::QWidget* parent = nullptr);
    ~MainWindow();

private:
    void on_list_item_clicked(::QListWidgetItem* item);

private:
    Ui::MainWindow* _ui = nullptr;
};
