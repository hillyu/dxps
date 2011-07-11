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

package oversim.tier2.xmlpsapp;

//
// TODO auto-generated type

import oversim.common.BaseApp;
import oversim.common.ITier;
//simple XmlPsApp extends BaseApp
//{
//    parameters:
//        @class(ALMTest);
//        bool joinGroups = default(true);
//        int messageLength;
//        bool sendMessages = default(true);
//}

simple XmlPsApp extends BaseApp
{
    parameters:
        @class(XmlPsApp);
        bool joinGroups = default(true);
        int messageLength;
        bool sendMessages = default(true);
        int maxSubscription;
        double subRate;
        double unsubRate;
}

module XmlPsAppModule like ITier
{
    gates:
        input udpIn;
        input from_lowerTier;
        input from_upperTier;
        input tcpIn;  
        output tcpOut;
        output udpOut;
        output to_lowerTier;
        output to_upperTier;
        
    submodules:
        xmlPsApp: XmlPsApp;
    connections allowunconnected:
        from_lowerTier --> xmlPsApp.from_lowerTier;
        to_lowerTier <-- xmlPsApp.to_lowerTier;
        from_upperTier --> xmlPsApp.from_upperTier;
        to_upperTier <-- xmlPsApp.to_upperTier;
        udpIn --> xmlPsApp.udpIn;
        udpOut <-- xmlPsApp.udpOut;
}
