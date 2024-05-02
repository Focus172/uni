#include "socialnetworkwindow.h"
#include "ui_socialnetworkwindow.h"

SocialNetworkWindow::SocialNetworkWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SocialNetworkWindow)
    , id(-1)
{
    int ret = network.readUsers("/home/focus/dev/uni/csci-062/users.txt");
    if (ret < 0) throw;

    ui->setupUi(this);


    ui->login_error->hide();

    QObject::connect(ui->login_button, &QPushButton::clicked, this, &SocialNetworkWindow::login);
}


void SocialNetworkWindow::show_window(SocialNetworkDisplayWindow) {
    /*
    switch (window) {
    case Login:
        break;
    case Profile:
        break;
    }
    */
}

SocialNetworkWindow::~SocialNetworkWindow() {
    delete ui;
}

void SocialNetworkWindow::login() {
    auto t = this->ui->login_input->text();
    std::string s = t.toStdString();


    int id = network.getId(s);
    if (id < 0) {
        this->ui->login_error->show();
        this->ui->login_error->setText(QString::asprintf("User %s doesn't exists.", s.c_str()));
    } else {
        ui->main_view->setCurrentIndex(1);
        // this->hide();
        // this->profile->show();

        // this->id = id;
        // ui->login_button->hide();
        // ui->login_input->hide();
        // ui->login_error->hide();
        // ui->login_label->hide();
        // do the login
    }
};

