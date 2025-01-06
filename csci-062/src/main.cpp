#include "socialnetworkwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  srand(time(nullptr));
  QApplication a(argc, argv);
  SocialNetworkWindow w;
  w.show();
  return a.exec();
}
