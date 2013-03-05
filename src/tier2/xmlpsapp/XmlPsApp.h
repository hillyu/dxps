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
#include "bloom_filter.h"
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "bloom_filter.h"

class XmlPsApp : public BaseApp {
public:
	int maxSubscription;
	double subRate;
	double unsubRate;
  double pubRate;
	bool expandJoin;
	XmlPsApp();
	~XmlPsApp();
	void initializeApp(int stage);
	cMessage* timer;
	int groupNum;
  OverlayKey ov_key;
protected:

	//        void joinGroup(const unsigned char *buffer, uint32_t size);
	//        void leaveGroup(const unsigned char *buffer, uint32_t size);
	//        void sendDataToGroup(const unsigned char *buffer, uint32_t size);
	void joinGroup(OverlayKey ovkey,std::string xpath);
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
  /***************************************************************************
 *                              testfunctions                              *
 ***************************************************************************/
  void testxmldoc(std::string xmldoclist);
  /***************************************************************************
 *                            test function end                            *
 ***************************************************************************/
  
	std::vector<SubGen> subscribeList;
	std::vector<SubGen> subPool;
  int subSize;
 //std::vector<bloom_filter *> subscribeList;
	bool joinGroups;
  std::string xpepath;
  std::string xmllist;
	bool sendMessages;
	int msglen;
	bool evaluateXpe(std::string xmlfilename);
	OverlayKey xml2bloom(std::string xmlfilename,int l, int k);
	bloom_filter xml2bloom2(std::string xmlfilename,int l, int k);
	void recursivex2b(TiXmlElement* parent, bloom_filter & bloomfilter);
	//void subscribe(OverlayKey ovkey);//used for original expansion method, not
  //working
	void recursiveJoin(OverlayKey ovkey, int i);
  int bloom_l;
  int bloom2_l;
  int bloom_k;
  int bloom2_k;
  int filter_l; //filter size in Bit. to calc packet length.
  int appStartDelay;

};
std::ostream& operator<< (std::ostream& os, SubGen const & subg);
#endif /* XMLPSAPP_H_ */
