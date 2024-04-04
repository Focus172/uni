#include <cstdio>

int main(int argc, char **argv, char *envs[]) {
  int i = 0;
  for (char *p = envs[i]; p != nullptr; p = envs[i++]) {
    printf("%s\n", p);
  }
  // entry point
  return 0;
}
