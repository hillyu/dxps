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
#include <list>

class XmlPsApp: public ALMTest {
public:
	int maxSubscription;
	double subRate;
	double unsubRate;
	XmlPsApp();
	void initializeApp(int stage);
protected:
	void handleTimerEvent( cMessage* msg );
	void handleMCast( ALMMulticastMessage* mcast );
private:
	std::list<int> subscribeList;
};
class SubGen {
	public:
		SubGen();
		//TODO SubGen(string xpe)
		int getBloom();
		std::string getXpe();
	private:
		int bloom;
		std::string xpe;
}
#endif /* XMLPSAPP_H_ */
