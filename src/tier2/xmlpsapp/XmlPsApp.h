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


#include <omnetpp.h>
#include "BaseApp.h"
#include "CommonMessages_m.h"
#include "XmlPsAppMessageObserver.h"
#include "subgen.h"
#include <vector>
#include "bloom_filter.hpp"
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

class XmlPsApp : public BaseApp {
public:
	int maxSubscription;
	double subRate;
	double unsubRate;
	XmlPsApp();
	~XmlPsApp();
	void initializeApp(int stage);
	cMessage* timer;
	int groupNum;
protected:

	//        void joinGroup(const unsigned char *buffer, uint32_t size);
	//        void leaveGroup(const unsigned char *buffer, uint32_t size);
	//        void sendDataToGroup(const unsigned char *buffer, uint32_t size);
	void joinGroup(OverlayKey ovkey);
	void leaveGroup(OverlayKey ovkey);
	void sendDataToGroup(OverlayKey ovkey,std::string data);
	void handleMCast( ALMMulticastMessage* mcast );
	void handleLowerMessage(cMessage* msg);
	void handleReadyMessage(CompReadyMessage* msg);
	void handleTimerEvent( cMessage* msg );
	std::string xmlGen();
friend std::ostream& operator<< (std::ostream& os, SubGen const & subg);

	XmlPsAppMessageObserver* xmlpsapp_observer;
private:
	std::vector<SubGen> subscribeList;
	//std::vector<bloom_filter *> subscribeList;
	bool joinGroups;

	bool sendMessages;
	int msglen;
	bool evaluateXpe(std::string xmlfilename);
	OverlayKey xml2bloom(std::string xmlfilename);
	void recursivex2b(TiXmlElement* parent, bloom_filter & bloomfilter);

};
std::ostream& operator<< (std::ostream& os, SubGen const & subg);
#endif /* XMLPSAPP_H_ */
