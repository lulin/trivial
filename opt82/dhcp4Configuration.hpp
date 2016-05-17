#ifndef DHCP4_CONFIGURATION_HPP_
#define DHCP4_CONFIGURATION_HPP_

#include "../../yangobj/ietf_interfaces.hpp"

namespace ns_opt82 {
  class DHCP4Profile {
    //
  };

  class Dhcp4Configuration {
    bool enabled;
    bool portTrusted;
    // Profile reference name
    std::string profileName;
    // The opt82 profile cache
    DHCP4Profile *dhcp4Prof;
  };

  class SubscriberProfile {
  public:
  private:
  };

  class SubscriberConfiguration {
  public:
    SubscriberConfiguration(SubscriberProfile *s = NULL): subsProf(s) {}

  private:
    // Subscriber profile name
    std::string subsProfName;
    // Subscriber profile
    SubscriberProfile *subsProf;
  };

  class SubInterface {
  public:
    explicit SubInterface(int objIndex);
    ~SubInterface();

    int& getObjIndex() {return objIndex;}

    bool& isEnabled() {return enabled;}
    // The accesser to @enabled@
    bool& Enable() {return enabled;}

    // The accesser to @dhcp4@
    Dhcp4Configuration& DHCP4() {return dhcp4;}
    Dhcp4Configuration& getDHCP4() {return dhcp4;}
    void setDHCP4(dhcp4Configuration& d) {dhcp4 = d;}

    // The accesser to @subsConf@
    SubscriberConfiguration& SubsConf() {return subsConf;}
    SubscriberConfiguration& getSubsConf() {return subsConf;}
    void setSubsConfig(SubscriberProfile& s) {subsConf = s;}

  private:
    int objIndex;
    bool enabled;

    // The bbf-dhcpv4 augment
    dhcp4Configuration dhcp4;
    // The bbf-subscriber-configuration augment
    SubscriberConfiguration subsConf;
  };

  typedef map<int, SubInterface *> SubIfs_T;

  class I_SubInterfaces {
  public:
    I_SubInterfaces();
    ~I_SubInterfaces();

    SubInterface *getSubIf(int objIndex);
    int insertSubIf(SubInterface *subIf);
    int removeSubIf(int objIndex, SubInterface *out);

  private:
    // The SubInterfaces container
    SubIfs_T *subIfs;
  }

}
#endif
