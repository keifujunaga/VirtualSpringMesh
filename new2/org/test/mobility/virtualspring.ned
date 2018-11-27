//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package test.mobility;
import inet.mobility.contract.IMobility;

module MobileHost
{
    parameters:
        string mobilityType = default("StationaryMobility");
        @networkNode();
        @display("i=device/pocketpc_s");
        @statistic[coordX](title="coord X"; source="xCoord(mobilityPos(mobilityStateChanged))"; record=vector; interpolationmode=linear); //X座標の統計情報
        @statistic[coordY](title="coord Y"; source="yCoord(mobilityPos(mobilityStateChanged))"; record=vector; interpolationmode=linear); //Y座標の統計情報
        @statistic[coordZ](title="coord Z";source="zCoord(mobilityPos(mobilityStateChanged))";record=vector; interpolationmode=linear);
    submodules:
        mobility: <mobilityType> like IMobility;
}

network MobileNetwork
{
    parameters:
        int numHosts;
        @display("bgb=600,400");
    submodules:
        host[numHosts]: MobileHost {
            parameters:
                @display("p=300,300;r=,,#707070");
        }
}

	