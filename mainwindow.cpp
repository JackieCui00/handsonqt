#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <qmessagebox.h>
#include <qpushbutton.h>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), _ui(new Ui::MainWindow) {
    _ui->setupUi(this);

    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName("./db");

    if (!_db.open()) {
        qDebug() << "Failed to connect";
        exit(0);
    }
    qDebug() << "Succ to connect";

    connect(_ui->loginButton, &::QPushButton::clicked, this, &MainWindow::on_submit);
}

MainWindow::~MainWindow() {
    delete _ui;
}

void MainWindow::on_submit() {
    QString username = _ui->usernameInput->text();
    QString password = _ui->passwordInput->text();
    qDebug() << "username:" << username << ", password:" << password;

    QString sql_command = "SELECT * FROM user WHERE username = '" + username
                            + "' AND password = '" + password + "'";
    QSqlQuery query(_db);
    if (query.exec(sql_command)) {
        if (query.size() > 0) {
            ::QMessageBox::information(this, "Login Success.", "You have successfully logged in!");
        } else {
            ::QMessageBox::information(this, "Login failed.", "Login failed, Please try again...");
        }
    } else {
        qDebug() << "Fail to exec sql:<" << sql_command << ">, error:" << query.lastError();
    }
}
