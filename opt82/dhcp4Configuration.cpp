#include "dhcp4Configuration.hpp"

namespace ns_opt82 {
  // The globals
  static Opt82Profs_T *g_opt82Profs = new Opt82Profs_T;
  static SubIfs_T *g_subIfs = new SubIfs_T;

  // class SubInterface


  // class I_SubInterfaces
  I_SubInterfaces::I_SubInterfaces(SubIfs_T *s): subIfs(s) {
    if (s == NULL)
      subIfs = g_subIfs;
  }
}
