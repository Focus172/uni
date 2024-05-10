#include "postwidget.h"

postwidget::postwidget(Post *post, int *id, QWidget *parent)
    : QWidget{parent}, post(post), id(id), ui(new ui::postwidget(this)) {
  QObject::connect(ui->like, &QPushButton::clicked, this, &postwidget::postliked);
}

postwidget::~postwidget() {
  delete ui;
}

void postwidget::postliked() {
    post->set_liked(*id);
}
