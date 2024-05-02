#include "socialnetworkwindow.h"
#include "ui_socialnetworkwindow.h"

SocialNetworkWindow::SocialNetworkWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SocialNetworkWindow)
    , id(-1)
    , user()
{
    int ret = network.readUsers("/home/focus/dev/uni/csci-062/example/users.txt");
    if (ret < 0) throw;
    ret = network.readPosts("/home/focus/dev/uni/csci-062/example/posts.txt");
    if (ret < 0) throw;

    ui->setupUi(this);

    ui->login_error->hide();
    ui->profile_friends_table->setColumnCount(1);

    // login ports
    QObject::connect(ui->login_button, &QPushButton::clicked, this, &SocialNetworkWindow::login);

    // profile ports
    QObject::connect(ui->profile_home, &QPushButton::clicked, this, &SocialNetworkWindow::gohome);
    QObject::connect(ui->profile_friends_table, &QTableWidget::cellClicked, this, &SocialNetworkWindow::gofriend);
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
        this->id = id;
        SocialNetworkWindow::showprofile(id);
        ui->main_view->setCurrentIndex(1);
    }
};


void SocialNetworkWindow::showprofile(int newuser) {
    User *u = network.getUser(newuser);

    this->user.select(u, newuser == id);

    if (newuser == this->id) {
        // this user
        ui->profile_label->setText(QString("My Profile"));
        ui->profile_home->hide();
    } else {
        // other user
        ui->profile_label->setText(QString::asprintf("%s's Profile", u->getName().c_str()));
        ui->profile_home->show();
    }

    ui->profile_friends_table->clear();

    auto fr = u->getFriends();
    ui->profile_friends_table->setRowCount(fr.size());

    int index = 0;
    for (auto f : fr) {
        User *uf = this->network.getUser(f);

        // this call takes owevership of the object
        auto it = new QTableWidgetItem(QString::fromStdString(uf->getName()));
        ui->profile_friends_table->setItem(index, 0, it);
        index += 1;
    }

    ui->profile_post_list->setModel(user.model);

}

void SocialNetworkWindow::gohome() {
    SocialNetworkWindow::showprofile(this->id);
}

void SocialNetworkWindow::gofriend(int row, int col) {
    assert(col == 0);

    User *u = this->network.getUser(this->user.id);
    auto fr = u->getFriends();

    int show = -1;
    int index = 0;
    for (int f : fr) {
        if (index == row) {
            show = f;
            break;
        }
        index += 1;
    }
    if (show < 0) return;

    SocialNetworkWindow::showprofile(show);
    // printf("wassup poss %d, %d\n", row, col);
}

