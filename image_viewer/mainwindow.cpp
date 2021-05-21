#include "mainwindow.h"
#include "ui_image_viewer.h"

#include <QDebug>

MainWindow::MainWindow(::QWidget* parent) : ::QMainWindow(parent), _ui(new ::Ui::MainWindow()) {
    _ui->setupUi(this);

    connect(_ui->browse_button, &::QPushButton::clicked, this, &MainWindow::on_browse_button_clicked);
    connect(_ui->save_button, &::QPushButton::clicked, this, &MainWindow::on_save_button_clicked);
    connect(_ui->scale_slider, &::QSlider::valueChanged, this, &MainWindow::on_scale_changed);
    connect(_ui->horizontal_slider, &::QSlider::valueChanged, this, &MainWindow::on_horizontal_changed);
    connect(_ui->vertical_slider, &::QSlider::valueChanged, this, &MainWindow::on_veritical_changed);
}

MainWindow::~MainWindow() {
    delete _ui;
}

void MainWindow::paintEvent(::QPaintEvent* event) {
    if (!_can_draw) {
        return;
    }

    this->paint_image(_ui->image_frame->pos().x(), _ui->image_frame->pos().y());
}

void MainWindow::on_browse_button_clicked() {
    ::QString filepath = ::QFileDialog::getOpenFileName(this, tr("Open Image"), ::QDir::currentPath(), tr("Image Files (*.jpg *.jpeg *.JPG *.png *.PNG"));

    if (filepath.isEmpty()) {
        qDebug() << "No file selected";
        return;
    }

    auto pix = new ::QPixmap(filepath);
    if (pix->isNull()) {
        qDebug() << "Fail to open:" << filepath;
        ::QMessageBox::warning(this, tr("Invalid path"),
                QString("Fail to open image:%1, maybe it's not an image").arg(filepath));
        return;
    }

    if (pix->width() < _ui->image_frame->width() || pix->height() < _ui->image_frame->height()) {
        qDebug() << "image:" << filepath << " is too small:" << pix->width() << "x" << pix->height()
            << ", expect:" << _ui->image_frame->width() << "x" << _ui->image_frame->height();
        ::QMessageBox::warning(this, tr("Invalid Size"),
                QString("Image size too small. Please use an image larger than %1 x %2")
                    .arg(_ui->image_frame->width(), _ui->image_frame->height()));
        return;
    }

    _pix = pix;
    _image_size = pix->size();
    _draw_size = _ui->image_frame->size();
    _ui->horizontal_slider->setValue(50);
    _ui->vertical_slider->setValue(50);
    _can_draw = true;
}

void MainWindow::on_save_button_clicked() {
    if (!_can_draw || _pix->isNull()) {
        return;
    }

    this->save_image(::QCoreApplication::applicationDirPath() + "/image.jpg");
}

void MainWindow::on_scale_changed(int value) {
    if (!_can_draw) {
        return;
    }

    _draw_size = _image_size * value / 100;
    this->update();
}

void MainWindow::on_horizontal_changed(int value) {
    if (!_can_draw) {
        return;
    }

    _draw_position.setX(_draw_size.width() * ((value - 50) / 100.0));
    this->update();
}

void MainWindow::on_veritical_changed(int value) {
    if (!_can_draw) {
        return;
    }

    _draw_position.setY(_draw_size.height() * ((value - 50) / 100.0));
    this->update();
}

void MainWindow::paint_image(int x, int y) {
    ::QPainter painter;

    painter.begin(this);
    if (!_pix->isNull()) {
        auto rect = ::QRect(x, y, _ui->image_frame->width(), _ui->image_frame->height());
        painter.setClipRect(rect);
        painter.fillRect(rect, ::Qt::SolidPattern);
        painter.drawPixmap(x - _draw_position.x(), y - _draw_position.y(), _draw_size.width(), _draw_size.height(), *_pix);
    }
    painter.end();
}

void MainWindow::save_image(::QString filepath) {
    ::QImage image(_ui->image_frame->width(), _ui->image_frame->height(), ::QImage::Format_RGB16);
    ::QPainter painter(&image);

    painter.begin(this);
    if (!_pix->isNull()) {
        auto rect = ::QRect(0, 0, _ui->image_frame->width(), _ui->image_frame->height());
        painter.setClipRect(rect);
        painter.fillRect(rect, ::Qt::SolidPattern);
        painter.drawPixmap(0 - _draw_position.x(), 0 - _draw_position.y(), _draw_size.width(), _draw_size.height(), *_pix);
    }
    painter.end();

    image.save(filepath);

    ::QMessageBox::information(this, "Success", ::QString("Image has been successfully saved to %1").arg(filepath));
}
