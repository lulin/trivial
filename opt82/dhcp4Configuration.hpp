#ifndef DHCP4CONFIGURATION_HPP_
#define DHCP4CONFIGURATION_HPP_

namespace ns_opt82 {
  class Opt82Profile {
    //
  };

  typedef map<std::string, Opt82Profile *> Opt82Profs_T;

  class I_Opt82Profiles {
  public:
  private:
    // The container
    Opt82Profs_T *profs;
  };

  class SubInterface {
  public:
  private:
    // Profile reference name
    std::string profileRef;
    // The opt82 profile cache
    Opt82Profile *opt82Prof;
  };

  typedef map<int, SubInterface *> SubIfs_T;

  enum E_ISubIfRet {
    E_ISubIfRet_OK,
  };

  class I_SubInterfaces {
  public:
    I_SubInterfaces(SubIfs_T *s = NULL);
    ~I_SubInterfaces() {}

    SubInterface *getSubIf(int objIndex);
    E_ISubIfRet insertSubIf(SubInterface *subIf);
    E_ISubIfRet removeSubIf(int objIndex, SubInterface *out);
  private:
    // The subInterfaces container
    SubIfs_T *subIfs;
  }
}
#endif
