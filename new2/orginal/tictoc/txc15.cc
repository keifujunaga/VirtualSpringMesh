#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "tictoc15_m.h"

using namespace omnetpp;

/**
 * Let's make it more interesting by using several (n) `tic' modules,
 * and connecting every module to every other. For now, let's keep it
 * simple what they do: module 0 generates a message, and the others
 * keep tossing it around in random directions until it arrives at
 * module 3.
 */
class Txc15 : public cSimpleModule
{
private:
    long numSent;
    long numReceived;
    cLongHistogram hopCountStats;
    cOutVector hopCountVector;
protected:
    virtual TicTocMsg15 *generateMessage();
    virtual void refreshDisplay() const override;
    virtual void forwardMessage(TicTocMsg15 *msg);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

Define_Module(Txc15);


void Txc15::initialize()
{
    numSent = 0;
    numReceived = 0;
    WATCH(numSent);
    WATCH(numReceived);
    if (getIndex() == 0) {
        // Boot the process scheduling the initial message as a self-message.
        TicTocMsg15 *msg = generateMessage();
        numSent++;
        scheduleAt(0.0, msg);
    }
}

void Txc15::handleMessage(cMessage *msg)
{
    TicTocMsg15 *ttmsg = check_and_cast<TicTocMsg15 *>(msg);
    if (ttmsg->getDestination() == getIndex()) {
        // Message arrived.
        int hopcount = ttmsg->getHopCount();
        hopCountVector.record(hopcount);
        hopCountStats.collect(hopcount);
        EV << "Message " << ttmsg << " arrived after" << hopcount << "hops.\n";
        numReceived++;
        bubble("ARRIVED, starting new one!");
        delete ttmsg;

        //Generate another one
        EV << "Generating another message: ";
        TicTocMsg15 *newmsg = generateMessage();
        EV << newmsg << endl;
        forwardMessage(newmsg);
        numSent++;
    }
    else {
        // We need to forward the message.
        forwardMessage(ttmsg);
    }
}

TicTocMsg15 *Txc15::generateMessage()
{
    int src = getIndex();
    int n = getVectorSize();
    int dest = intuniform(0, n-2);
    if (dest >= src)
        dest++;
    char msgname[20];
    sprintf(msgname, "tic-%d-to-%d", src, dest);

    //Create message object and set source and destination field
    TicTocMsg15 *msg = new TicTocMsg15(msgname);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

void Txc15::forwardMessage(TicTocMsg15 *msg)
{
    // In this example, we just pick a random gate to send it on.
    // We draw a random number between 0 and the size of gate `out[]'.
    int n = gateSize("gate");
    int k = intuniform(0, n-1);

    EV << "Forwarding message " << msg << " on gate[" << k << "]\n";
    send(msg, "gate$o", k);
}

void Txc15::refreshDisplay() const
{
    char buf[40];
    sprintf(buf, "rcvd: %ld sent: %ld", numReceived, numSent);
    getDisplayString().setTagArg("t", 0, buf);
}

void Txc15::finish()
{
    EV << "Sent: " << numSent << endl;
    EV << "Received: " << numReceived << endl;
    EV << "Hop count, min:    " << hopCountStats.getMin() << endl;
    EV << "Hop count, max:    " << hopCountStats.getMax() << endl;
    EV << "Hop count, mean:   " << hopCountStats.getMean() << endl;
    EV << "Hop count, stddev: " << hopCountStats.getStddev() << endl;

    recordScalar("#sent", numSent);
    recordScalar("#received", numReceived);
    hopCountStats.recordAs("hop count");
}