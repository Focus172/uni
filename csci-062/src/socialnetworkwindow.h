#ifndef SOCIALNETWORKWINDOW_H
#define SOCIALNETWORKWINDOW_H

#include <QMainWindow>
#include "network.h"

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

private:
    enum SocialNetworkDisplayWindow {
        Login,
        Profile
    };

    void show_window(SocialNetworkDisplayWindow window);

    Ui::SocialNetworkWindow *ui;

    Network network;
    int id;
};
#endif // SOCIALNETWORKWINDOW_H
