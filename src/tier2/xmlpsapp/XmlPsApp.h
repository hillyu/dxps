//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef XMLPSAPP_H_
#define XMLPSAPP_H_

#include "ALMTest.h"
#include "subgen.h"
#include <vector>
#include "bloom_filter.hpp"
#include <iostream>
#include <fstream>

class XmlPsApp: public ALMTest {
public:
	int maxSubscription;
	double subRate;
	double unsubRate;
	XmlPsApp();
	void initializeApp(int stage);
protected:
	void handleTimerEvent( cMessage* msg );
//        void joinGroup(const unsigned char *buffer, uint32_t size);
//        void leaveGroup(const unsigned char *buffer, uint32_t size);
//        void sendDataToGroup(const unsigned char *buffer, uint32_t size);
        void joinGroup(OverlayKey ovkey);
                void leaveGroup(OverlayKey ovkey);
                void sendDataToGroup(OverlayKey ovkey);
	void handleMCast( ALMMulticastMessage* mcast );


private:
	std::vector<SubGen> subscribeList;
    //std::vector<bloom_filter *> subscribeList;

};

#endif /* XMLPSAPP_H_ */
