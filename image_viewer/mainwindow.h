#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QPainter>

namespace Ui {
class MainWindow;
};

class MainWindow final : public ::QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(::QWidget* parent = nullptr);
    ~MainWindow();

    void paintEvent(::QPaintEvent* event) override;

private:
    void on_browse_button_clicked();
    void on_save_button_clicked();
    void on_scale_changed(int value);
    void on_horizontal_changed(int value);
    void on_veritical_changed(int value);

    void paint_image(int x, int y);
    void save_image(::QString filepath);

private:
    ::Ui::MainWindow* _ui = nullptr;

    bool _can_draw = false;
    ::QPixmap* _pix = nullptr;
    ::QSize _image_size;
    ::QSize _draw_size;
    ::QPoint _draw_position;
};
