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

#include "XmlPsApp.h"
Define_Module(XmlPsApp);


XmlPsApp::XmlPsApp() {
	// TODO Auto-generated constructor stub

	timer = new cMessage( "app_timer");
	joinGroups = true;
	sendMessages = true;
	observer = NULL;



}
//
//XmlPsApp::~XmlPsApp() {
//	// TODO Auto-generated destructor stub
//}

void XmlPsApp::initializeApp(int stage)
{
	if( stage != (numInitStages()-1))
	{
		return;
	}
	observer = check_and_cast<MessageObserver*>(
			simulation.getModuleByPath("globalObserver.globalFunctions[0].function.observer"));
	joinGroups = par("joinGroups");
	msglen = par("messageLength");
	sendMessages = par("sendMessages");
	maxSubscription=par("maxSubscription");
	subRate=par("subRate");
	unsubRate=par("unsubRate");
}

void XmlPsApp::handleTimerEvent( cMessage* msg )
{
	if( msg == timer ) {
		double random = uniform( 0, 1 );
		if( (random < subRate && joinGroups) || subscribeList.empty() ) {
			joinGroup(int groupNum=SubGen().bloom());
			subscribeList.push_back (groupNum);
			//            std::list<int>::iterator it;
			//            it=subscribeList.end();
			//            it=--it;
			//            EV<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<*it<<"groupNum is:"<<groupNum;
		}
		else if( random < subRate+unsubRate && joinGroups ) {
			std::list<int>::iterator it;
			it=subscribeList.begin();
			int random=intuniform(1, subscribeList.size());
			for (i = 0; i < random; i++) {
				it++;
			}
			leaveGroup( *it);
			subscribeList.erase(i);//randomly delete a subscription
		}
		else if ( sendMessages ) {
			sendDataToGroup( intuniform( 1, groupNum ));
		}
		scheduleAt( simTime() + 10, timer );
	}
}
void XmlPsApp::sendDataToGroup( int i )
{

	ALMMulticastMessage* msg = new ALMMulticastMessage("Multicast message");
	msg->setGroupId(OverlayKey(i));

	ALMTestTracedMessage* traced = new ALMTestTracedMessage("Traced message");
	traced->setTimestamp();
	traced->setGroupId(OverlayKey(i));
	traced->setMcastId(traced->getId());
	traced->setSenderId(getId());
	traced->setByteLength(msglen);

	msg->encapsulate(traced);

	send(msg, "to_lowerTier");

	observer->sentMessage(traced);
}
void SubGen::SubGen(){
	//reading from a subscription pool
	string SUBFILE;
	ifstream subFile (SUBFILE);
	BloomFilter.bloomfy
	string random_line( ifstream subFile )
	{
		string line ;
		string selected_line ; // added
		int nlines = 0 ;
		while( getline( file, line ) )
			if(  ( rand() % ++nlines  ) == 0 ) // break ;
		selected_line = line ;      
		return selected_line ;
	}	
}
