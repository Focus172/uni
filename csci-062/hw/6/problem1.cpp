#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct buffer {
  char password[16];
  int flag;
};

int auth() {
  volatile buffer buf = buffer{
      .password = "",
      .flag = 0,
  };
  gets((char *)buf.password);

  if (strcmp((char *)buf.password, "brilling") == 0)
    buf.flag = 1;

  return buf.flag;
}

int main() {
  if (auth()) {
    printf(" Access Granted.\n");
  } else {
    printf("\nAccess Denied.\n");
  }
}
