#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

#include "inet/common/ModuleAccess.h"
#include "inet/mobility/contract/IMobility.h"
#include "inet/common/INETMath.h"
#include "inet/mobility/base/MobilityBase.h"

using namespace inet;

Register_Abstract_Class(MobilityBase);

    /**
     * Derive the Txc1 class from cSimpleModule. In the Tictoc1 network,
     * both the `tic' and `toc' modules are Txc1 objects, created by OMNeT++
     * at the beginning of the simulation.
     */
class MobileHost : public cSimpleModule
    {
    protected:
        // The following redefined virtual function holds the algorithm.

        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
    };

    // The module class needs to be registered with OMNeT++
 Define_Module(MobileHost);

 void MobileHost::initialize(){
     cModule *host = getContainingNode(this);
    // IMobility *mod  = check_and_cast<IMobility*>(host->getSubmodule("mobility"));
    // Coord pos = mod->getCurrentPosition();
 }

 void MobileHost::handleMessage(cMessage *msg){
     delete msg;
 }
