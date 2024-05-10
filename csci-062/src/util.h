#ifndef UTIL_H
#define UTIL_H

#define thrownull(p)                                                           \
  if (p == nullptr)                                                            \
    throw;

// #define thrownull(p) (void*)p

#define gaurd(expr)                                                            \
  if (!expr)                                                                   \
    return -1;

#endif // !UTIL_H
