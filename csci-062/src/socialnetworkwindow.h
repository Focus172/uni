#ifndef SOCIALNETWORKWINDOW_H
#define SOCIALNETWORKWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QAbstractItemView>
#include "network.h"
#include "socialnetworkwindowui.h"

class SelectedUser {
public:
    SelectedUser() : id(-1), model(new QStringListModel) {}
    ~SelectedUser() { delete model; }

    void select(User *user, int uid) {
        // assert(u != nullptr);
        auto strs = QStringList();

        for (auto post : user->getPosts() ) {
            // if the current user is the displayed user OR the post is public
            if (uid == user->getId() || post->getIsPublic()) {
                strs.append(QString::fromStdString(post->toString()));
            }
        }

        this->id = user->getId();
        delete this->model;
        this->model = new QStringListModel(strs);
    }

    int id;
    QStringListModel *model;
};


class SocialNetworkWindow : public QMainWindow
{
    Q_OBJECT

public:
    SocialNetworkWindow(QWidget *parent = nullptr);
    ~SocialNetworkWindow();

    void login();

    void showprofile(int user);
    void gohome();
    void addfriend();

    void gofriend(int row, int col);
    void addsuggestedfriend(int row, int col);

private:
    SocialNetworkWindowUi *ui;
    Network network;

    int id;
    SelectedUser user;
};

#endif // SOCIALNETWORKWINDOW_H
