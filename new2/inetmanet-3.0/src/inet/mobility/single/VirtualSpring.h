/*
 * VirtualSpring.h
 *
 *  Created on: 2018/09/16
 *      Author: kei fukunaga
 */

#ifndef INET_MOBILITY_SINGLE_VIRTUALSPRING_H_
#define INET_MOBILITY_SINGLE_VIRTUALSPRING_H_


#include "inet/common/INETDefs.h"

#include "inet/mobility/base/VirtualSpringBase.h"
#include "inet/common/geometry/common/Coord.h"
#include "inet/physicallayer/pathloss/FreeSpacePathLoss.h"


namespace inet {


class INET_API VirtualSpring : public VirtualSpringBase
{
  protected:
    double speed;    ///< speed of the host
    double speedMean;    ///< speed mean
    double angleMean;    ///< angle mean
    double variance;    ///< variance
    double cRange;    ///< communication range
    int numHost; ///< total number of the Host
    int nodeNum; ///< number of the Host
    double lo; ///< natural distance
    double kAtA;
    Coord *nodePs = nullptr; ///< total number of the coordination
    double **li = nullptr;
    bool nextMoveIsWait;
    Coord *acceleration = nullptr;
    Coord **unitvector = nullptr;
    //Coord velocity;
    double frequency;
    double propagationSpeed;
    int division;
    double dbm;
    double lbreq;
    bool *selectSN = nullptr;
    Coord **neighborlist = nullptr;
    double *sinlist = nullptr;
    double *coslist = nullptr;

  protected:

    /** @brief Initializes mobility model parameters.*/
    virtual void initialize(int stage) override;

   // virtual void initializePosition() override;

    //virtual void handleSelfMessage(cMessage *message) override;

    /** @brief Move the host*/
    virtual void move() override;

    /** @brief Overriden from VirtualSpringBase. */
    virtual void setTargetPosition() override;

    /** @brief set initial Position **/
    void setinitialPosition();

    /** @brief set unitvector **/
    void setUnitvector();

    /** @brief set acceleration **/
    void setAcceleration();

    /** @brief set Lastspeed **/
    void resetAcceleration();

    /** @brief Acceleration To Velocity **/
    //void AccelerationToVelocity(simtime_t traveltime);

    /** @brief Acceleration To Position **/
    void AccelerationToPosition(simtime_t traveltime);

    /** @brief set passlossmodel **/
    double computePathLoss();
    double computeFreeSpacePathLoss(double distance);

    /** @brief convert position into distance **/
    double PositionToDistance(Coord a, Coord b);

    /** @brief convert position into delta **/
    double DistanceToDelta(int i, int j, double dbm, double lbreq);

    /** @brief set virtualspring **/
    bool setVirtualSpring(int i, int j);

    /** @brief set Acute Angle Test **/
    double AcuteAngleTest(Coord a, Coord b, Coord c);

    /** @brief Check Functions **/
    void CheckFunction();

    /** @brief ScoutSelection **/
    void ScoutSelection();

  public:
    VirtualSpring();
    virtual ~VirtualSpring();
};

} // namespace inet

#endif /* INET_MOBILITY_SINGLE_VIRTUALSPRING_H_ */
