#ifndef __REACT_NATIVE_MEMCACHEJSI_H__
#define __REACT_NATIVE_MEMCACHEJSI_H__
#include <jsi/jsi.h>

namespace memcachejsi {
  int multiply(double a, double b);
  void install(facebook::jsi::Runtime& runtime);
}

#endif /* __REACT_NATIVE_MEMCACHEJSI_H__ */
