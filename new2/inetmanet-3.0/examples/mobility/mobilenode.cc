#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

#include "inet/common/ModuleAccess.h"
#include "inet/mobility/contract/IMobility.h"
#include "inet/common/INETMath.h"
#include "inet/mobility/base/MobilityBase.h"

using namespace inet;


class MobileNode : public cSimpleModule
    {
    protected:
        // The following redefined virtual function holds the algorithm.
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
    };

    // The module class needs to be registered with OMNeT++
 Define_Module(MobileNode);

 void MobileNode::initialize(){
     if (getIndex() == 1){
         cModule *host = getContainingNode(this);
         IMobility *mod  = check_and_cast<IMobility*>(host->getSubmodule("mobility"));
         Coord pos = mod->getCurrentPosition();
         cMessage *msg = new cMessage("digDog");
         send(msg,"out");
         EV << "Sending initial message\n";
     }
 }

 void MobileNode::handleMessage(cMessage *msg){
     cModule *host = getContainingNode(this);
     IMobility *mod  = check_and_cast<IMobility*>(host->getSubmodule("mobility"));
     Coord pos = mod->getCurrentPosition();
     cMessage *msg = new cMessage("digDog");
     EV << pos.x;
     send(msg, "out");
 }

