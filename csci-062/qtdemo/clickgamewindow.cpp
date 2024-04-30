#include "clickgamewindow.h"
#include "ui_clickgamewindow.h"

ClickGameWindow::ClickGameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClickGameWindow)
    , counter()
{
    ui->setupUi(this);
    ui->label_3->hide();
}

ClickGameWindow::~ClickGameWindow()
{
    delete ui;
}

void ClickGameWindow::slot1()
{
    int count = this->counter.getCount();

    if (count >= 10) {
        return;
    }

    this->counter.add();

    if (++count < 10) {
        this->ui->label->setText(QString::fromStdString("Number of Clicks: " + std::to_string(count)));
    } else {
        this->ui->pushButton->hide();
        this->ui->label->hide();
        ui->label_3->show();
    }

};

