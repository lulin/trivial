#include "dhcp4Configuration.hpp"

namespace ns_opt82 {
  // BaseInterface
  //-----------------------------------------------
  BaseInterface::BaseInterface(std::string &nam): name(nam) {
    // TODO: compute the network side.
  }

  E_BaseIfNetworkSide BaseInterface::getNetworkSide() {
    // TODO:
  }

  // SubInterface
  //-----------------------------------------------
  SubInterface::SubInterface(int key): objIndex(key) {}
  SubInterface::SubInterface(int key, std::string &ifName)
    : bIf(BaseInterface(ifName)),
      objIndex(key) {}
  SubInterface::~SubInterface(int key, BaseInterface &base)
    : bIf(base),
      objIndex(key) {}

  E_BaseIfNetworkSide SubInterface::getNetworkSide() {
    return bIf.getNetworkSide();
  }

  //-----------------------------------------------
  // I_SubInterfaces
  //-----------------------------------------------
  SubInterfaces_t *g_subIfs = new SubInterfaces_t;

  I_SubInterfaces::I_SubInterfaces(): subIfs(g_subIfs) {}

  SubInterface * I_SubInterfaces::getSubIf(int objIndex) {
    return (*subIfs)[objIndex];
  }

  SubInterface * I_SubInterfaces::operator [](int objIndex) {
    return getSubIf(objIndex);
  }

  int I_SubInterfaces::eraseSubIf(int objIndex) {
    subIfs->erase(objIndex);
  }

  int I_SubInterfaces::eraseSubIf(int objIndex, SubInterface *&out) {
    out = (*subIfs)[objIndex];
    subIfs->erase(objIndex);
  }

  I_SubInterfaces::~I_SubInterfaces() {
  }
}
