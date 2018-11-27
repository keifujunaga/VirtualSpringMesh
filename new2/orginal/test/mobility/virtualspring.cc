#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

#include "inet/common/ModuleAccess.h"
#include "inet/mobility/contract/IMobility.h"
#include "inet/common/INETMath.h"

using namespace inet;

    /**
     * Derive the Txc1 class from cSimpleModule. In the Tictoc1 network,
     * both the `tic' and `toc' modules are Txc1 objects, created by OMNeT++
     * at the beginning of the simulation.
     */
class Virtualspring : public cSimpleModule
    {
      protected:
        // The following redefined virtual function holds the algorithm.
        virtual void initialize() override;
        virtual void handleMessage(cMessage *msg) override;
    };

    // The module class needs to be registered with OMNeT++
    Define_Module(Virtualspring);

    void Virtualspring::initialize()
    {
        // Initialize is called at the beginning of the simulation.
        // To bootstrap the tic-toc-tic-toc process, one of the modules needs
        // to send the first message. Let this be `tic'.

        // Am I Tic or Toc?
            // create and send first message on gate "out". "tictocMsg" is an
            // arbitrary string which will be the name of the message object.
            cMessage *msg = new cMessage("tictocMsg");
    }

    void Virtualspring::handleMessage(cMessage *msg)
    {
        // The handleMessage() method is called whenever a message arrives
        // at the module. Here, we just send it to the other module, through
        // gate `out'. Because both `tic' and `toc' does the same, the message
        // will bounce between the two.
        //cModule *host = getContainingNode(this);
        //IMobility *mod = check_and_cast<IMobility*>(host->getSubmodule("mobility"));
        //Coord pos = mod->getCurrentPosition();
        send(msg, "out"); // send out the message
    }
