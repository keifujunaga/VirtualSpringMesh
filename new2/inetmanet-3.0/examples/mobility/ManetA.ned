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

package inet.examples.mobility;

import inet.common.figures.DelegateSignalConfigurator;
import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.physicallayer.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.visualizer.integrated.IntegratedCanvasVisualizer;
import inet.environment.common.PhysicalEnvironment;

network ManetA
{
	parameters:
		int numNodes;

	submodules:
	visualizer: IntegratedCanvasVisualizer {
   		@display("p=59,103");
	}
    configurator: IPv4NetworkConfigurator {
        @display("p=59,164");
    }
    radioMedium: Ieee80211ScalarRadioMedium {
        @display("p=60,50,i=misc/sun");
    }
    figureHelper: DelegateSignalConfigurator {
        @display("p=61,236");
    }
    mnode[numNodes]: MobileHost {
        @display("i=device/palm");
    }
    physicalEnvironment: PhysicalEnvironment {
        @display("p=59,306");
    }
}