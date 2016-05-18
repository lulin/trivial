#include "../../include/dhcp4Configuration.hpp"

namespace ns_opt82 {
  //-----------------------------------------------
  // SubInterface
  //-----------------------------------------------
  SubInterface::SubInterface(int key): objIndex(key) {}
  SubInterface::~SubInterface() {}

  //-----------------------------------------------
  // I_SubInterfaces
  //-----------------------------------------------
  SubInterfaces_t *g_subIfs = new SubInterfaces_t;

  I_SubInterfaces::I_SubInterfaces(SubInterfaces_t *s = g_subIfs): subIfs(s) {}

  SubInterface * I_SubInterfaces::index(int objIndex) {
    return this->subIfs[objIndex];
  }

  SubInterface I_SubInterfaces::operator [](int objIndex) {
    return this->index(objIndex);
  }

  I_SubInterfaces::~I_SubInterfaces() {
    // Release subIfs
  }
}
