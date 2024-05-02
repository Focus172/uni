#ifndef SOCIALNETWORKWINDOW_H
#define SOCIALNETWORKWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QAbstractItemView>
#include "network.h"

class SelectedUser {
public:
    SelectedUser() : id(-1), model(new QStringListModel) {}
    ~SelectedUser() { delete model; }

    void select(User *user, bool showprivate) {
        // assert(u != nullptr);
        auto strs = QStringList();

        for (auto post : user->getPosts() ) {
            // if the post is not public and this is not use then skip
            if (!post->getIsPublic() && !showprivate) {
                continue;
            }
            strs.append(QString::fromStdString(post->toString()));
        }

        this->id = user->getId();
        delete this->model;
        this->model = new QStringListModel(strs);
    }

    int id;
    QStringListModel *model;
};


QT_BEGIN_NAMESPACE
namespace Ui { class SocialNetworkWindow; }
QT_END_NAMESPACE

class SocialNetworkWindow : public QMainWindow
{
    Q_OBJECT

public:
    SocialNetworkWindow(QWidget *parent = nullptr);
    ~SocialNetworkWindow();

    void login();

    void showprofile(int user);
    void gohome();
    void gofriend(int row, int col);

private:
    Ui::SocialNetworkWindow *ui;
    Network network;

    int id;
    SelectedUser user;
};

#endif // SOCIALNETWORKWINDOW_H
