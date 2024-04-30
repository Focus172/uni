#ifndef CLICKGAMEWINDOW_H
#define CLICKGAMEWINDOW_H

#include <QMainWindow>
#include "counter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ClickGameWindow; }
QT_END_NAMESPACE

class ClickGameWindow : public QMainWindow
{
    Q_OBJECT

public:
    ClickGameWindow(QWidget *parent = nullptr);
    ~ClickGameWindow();

private slots:
    void slot1();

private:
    Ui::ClickGameWindow *ui;
    Counter counter;
};
#endif // CLICKGAMEWINDOW_H
