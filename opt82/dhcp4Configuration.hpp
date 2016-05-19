#ifndef DHCP4_CONFIGURATION_HPP_
#define DHCP4_CONFIGURATION_HPP_

#include <stdint.h>
//#include "../../yangobj/ietf_interfaces.hpp"

namespace ns_opt82 {
  // DHCP4Profile & DHCP4Configuration
  // -------------------------------------------------------------------------
  enum E_DHCP4Subopt {
    E_DHCP4Subopt_CircuitID,
    E_DHCP4Subopt_RemoteID,
    E_DHCP4Subopt_AccessLoopChar,
  };
  struct DHCP4Profile {
    std::string name;           // The key
    uint16_t maxPktSize;
    std::vector<E_DHCP4Subopt> subopts;
    std::string defCircuitIDSyntax;
    std::string defRemoteIDSyntax;
    // struct {
    //   int:1 bit1;
    //   int:1 bit2;
    // } accessLoopChar;
    bool startNumberingFrom0;
    bool useLeadingZeroes;
  };

  class DHCP4Configuration {
  public:
    DHCP4Configuration(DHCP4Profile *d = NULL): dhcp4Prof(d) {}
    bool isEnabled() {return enabled;}
    bool isPortTrusted() {return portTrusted;}

    // Accessers
    bool & Enable() {return enabled;}
    bool & PortTrusted() {return portTrusted;}
    DHCP4Profile *& DHCP4Prof() {return dhcp4Prof;}

  private:
    bool enabled;
    bool portTrusted;
    // The opt82 profile cache
    DHCP4Profile *dhcp4Prof;
  };

  // SubscriberConfiguration & SubscriberProfile
  // -------------------------------------------------------------------------
  struct SubscriberProfile {
    std::string name;           // The key
    std::string circuitID;
    std::string remoteID;
    std::string subscriberID;
  };

  class SubscriberConfiguration {
  public:
    SubscriberConfiguration(SubscriberProfile *s = NULL): subsProf(s) {}
    SubscriberProfile *& SubsProf() {return subsProf;}

  private:
    // Subscriber profile
    SubscriberProfile *subsProf;
  };

  enum E_BaseIfNetworkSide {
    E_BaseIfNetworkSide_Unknown,
    E_BaseIfNetworkSide_User,
    E_BaseIfNetworkSide_Net,
  };

  class BaseInterface {
  public:
    BaseInterface(std::string &nam);
    std::string & Name() {return name;}
    E_BaseIfNetworkSide getNetworkSide();

  private:
    std::string name;
    E_BaseIfNetworkSide networkSide;
  };

  // The SubInterface
  // -------------------------------------------------------------------------
  class SubInterface {
  public:
    SubInterface(int objIndex);
    SubInterface(int objIndex, std::string &ifName);
    SubInterface(int objIndex, BaseInterface & baseIf);
    // SubInterface(SubInterface *s);
    ~SubInterface();

    int getObjIndex() {return objIndex;}

    bool isEnabled() {return enabled;}
    // The accesser to @enabled@
    bool & Enable() {return enabled;}

    // Get the network side of this SubInterface
    E_BaseIfNetworkSide getNetworkSide();

    // Accesser to @bIf@
    BaseInterface & BaseIf() {return bIf;}

    // The accesser to @dhcp4@
    DHCP4Configuration& DHCP4() {return dhcp4;}
    DHCP4Configuration& getDHCP4() {return dhcp4;}
    void setDHCP4(dhcp4Configuration& d) {dhcp4 = d;}

    // The accesser to @subsConf@
    SubscriberConfiguration& SubsConf() {return subsConf;}
    SubscriberConfiguration& getSubsConf() {return subsConf;}
    void setSubsConfig(SubscriberProfile& s) {subsConf = s;}

  private:
    int objIndex;               // The key
    bool enabled;
    BaseInterface bIf;

    // The bbf-dhcpv4 augment
    DHCP4Configuration dhcp4;
    // The bbf-subscriber-configuration augment
    SubscriberConfiguration subsConf;
  };

  // Class I_SubInterfaces supplies functions to access and manage
  // SubInterface(s) objects.
  // ------------------------------------------------------------------
  typedef map<int, SubInterface *> SubIfs_T;

  class I_SubInterfaces {
  public:
    I_SubInterfaces();
    ~I_SubInterfaces();

    // Get a subInterface element.
    SubInterface * getSubIf(int objIndex);
    // Copy and store @subIf@. Object with the same key have only one entry.
    int storeSubIf(SubInterface & subIf);
    // Erase a subInterface by @objIndex@.
    int eraseSubIf(int objIndex);
    // Erase a subInterface object, and retrieve it in @out@.
    int eraseSubIf(int objIndex, SubInterface *& out);

    SubInterface * operator[](int objIndex);

  private:
    // The SubInterfaces container
    SubIfs_T *subIfs;
  }
}
#endif
