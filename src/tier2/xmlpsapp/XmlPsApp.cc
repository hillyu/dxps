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
#include "./tinyxpath/xpath_static.h"
#include "XmlPsApp.h"

#include "XmlPsAppTracedMessage_m.h"
Define_Module(XmlPsApp);
const int BLOOM_L=4;
const int BLOOM_K=1;


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
	groupNum=0;

}

void XmlPsApp::handleTimerEvent( cMessage* msg )
{
	if( msg == timer ) {
		double random = uniform( 0, 1 );
		subRate=0.1;

		if (subscribeList.empty()) {
			bloom_filter bloomfilter (BLOOM_L,BLOOM_K);
			SubGen sub (bloomfilter);
			joinGroup(sub.getBloom());
			subscribeList.push_back (sub);
			EV <<"the xpe is:"<<sub.getXpe().c_str()<<"\n";
			EV <<"the bloom filter from list is:"<<subscribeList.back().getBloom().toString()<<"\n";
		}
		else if( (random < subRate && joinGroups) ) {
			//if( (random < subRate && joinGroups)||groupNum<1){

			bloom_filter bloomfilter (BLOOM_L,BLOOM_K);
			SubGen sub (bloomfilter);
			bool isrepeat=false;
			for (int i = 0; i < subscribeList.size(); ++i) {
				if ((subscribeList[i].getBloom()== sub.getBloom())){
					isrepeat=true;
					break;
				}
			}
			if (!isrepeat) {
				joinGroup(sub.getBloom());
				subscribeList.push_back (sub);
			}

		}

		//TiXmlDocument  XDp_doc;
		//XDp_doc.LoadFile ("/Users/hill/work/bib_0.xml");
		//TIXML_STRING S_res;
		//int i_res;//int is not working.
		//S_res = TinyXPath::S_xpath_string (XDp_doc.RootElement (), sub.getXpe().c_str());
		//i_res = TinyXPath::i_xpath_int (XDp_doc.RootElement (), "/bib");
		//groupNum=sub.getBloom();

		//EV <<"the Xpath expression is:"<<sub.getXpe()<<"\n";
		//EV <<"the bloom filter is:"<<(unsigned long)*bloomfilter.table()<<"\n";
		//EV <<"the overlaykey is:" <<OverlayKey(bloomfilter.table(),bloomfilter.size()/8).toString()<<"\n";

		//  EV <<"the result string is:"<<S_res<<"\n";
		//joinGroup(1);groupNum=1;



		else if( random < subRate+unsubRate && joinGroups ) {
			int i=intuniform(1, subscribeList.size());
			i=i-1;
			leaveGroup( subscribeList[i].getBloom());

			EV<<"the size of sublist is"<<subscribeList.size()<<"\n";
			EV<<"the xpe of sublist is"<<subscribeList[i].getXpe()<<"\n";
			//EV <<"unsubscribe to"<<(unsigned long)*(subscribeList[i].getBloom())<<"\n";
			EV <<"unsubscribe to: "<<subscribeList[i].getBloom().toString()<<"\n";
			subscribeList.erase (subscribeList.begin()+i);

		}
		else if ( sendMessages ) {
			int i=(intuniform(1, subscribeList.size())-1);
			sendDataToGroup( subscribeList[i].getBloom());

			//EV <<"data send to"<<(unsigned long)*subscribeList[i].getBloom()<<"\n";
			//
		}
		scheduleAt( simTime() + 10, timer );
	}

}
//void XmlPsApp::handleTimerEvent( cMessage* msg )
//{
//    if( msg == timer ) {
//
//        double random = uniform( 0, 1 );
//        if( (random < 0 && joinGroups) || groupNum < 1 ) {
//            joinGroup( 1 );groupNum=1;
//        } else if( random < 0 && joinGroups ) {
//            leaveGroup( groupNum-- );
//        } else if ( sendMessages ) {
//            sendDataToGroup( 1 );
//        }
//        scheduleAt( simTime() + 10, timer );
//    }
//}
//void XmlPsApp::joinGroup(const unsigned char *buffer, uint32_t size)
void XmlPsApp::joinGroup(OverlayKey ovkey)
{

	ALMSubscribeMessage* msg = new ALMSubscribeMessage;
	msg->setGroupId(ovkey);
	send(msg, "to_lowerTier");

	observer->joinedGroup(getId(), ovkey);
}

//void XmlPsApp::leaveGroup(const unsigned char *buffer, uint32_t size)
void XmlPsApp::leaveGroup(OverlayKey ovkey)
{
	ALMLeaveMessage* msg = new ALMLeaveMessage;
	//msg->setGroupId(OverlayKey (buffer, size));
	msg->setGroupId(ovkey);
	send(msg, "to_lowerTier");

	observer->leftGroup(getId(), ovkey);
}

//void XmlPsApp::sendDataToGroup(const unsigned char *buffer, uint32_t size){
void XmlPsApp::sendDataToGroup(OverlayKey ovkey){

	ALMMulticastMessage* msg = new ALMMulticastMessage("Multicast message");
	//msg->setGroupId(OverlayKey (buffer, size));
	msg->setGroupId(ovkey);
	//TODO maybe have something to do with the ned file definition of the msg type.
	XmlPsAppTracedMessage* traced = new XmlPsAppTracedMessage("Traced message");
	traced->setTimestamp();
	traced->setGroupId(ovkey);
	traced->setMcastId(traced->getId());
	traced->setSenderId(getId());
	traced->setXmlFileName(xmlGen().c_str());
	traced->setByteLength(msglen);

	msg->encapsulate(traced);

	send(msg, "to_lowerTier");

	observer->sentMessage(traced);
}

void XmlPsApp::handleMCast( ALMMulticastMessage* mcast )
{
	getParentModule()->getParentModule()->bubble("Received message!");
	EV << "[ALMTest::handleMCast()]\n"
			<< "    App received data message for group: " << mcast->getGroupId()
			<< endl;

	XmlPsAppTracedMessage* traced = check_and_cast<XmlPsAppTracedMessage*>(mcast->decapsulate());
	traced->setReceiverId(getId());
	observer->receivedMessage(traced);

	delete traced;

	delete mcast;
}




std::string XmlPsApp::xmlGen()
{
	std::string pathlist = "../sim/repos/samplefiles/xmldocs/filelist.txt";
	std::string xmlfile=SubGen::random_line(pathlist);
	struct stat filestatus;
	stat( xmlfile.c_str(), &filestatus );
	msglen=filestatus.st_size;
	return xmlfile;
}


















SubGen::SubGen():xpe(""),size(0),bloom(0){}

SubGen::SubGen(bloom_filter& filter){
	//reading from a subscription pool
	std::string SUBFILE="/Users/hill/work/oversim/test/bib.xpelist";
	xpe=random_line(SUBFILE);
	xpe+="/";
	int i=0;
	parseXpe(xpe,&filter,"",i);
	size=filter.size()/bits_per_char;
	bloom=OverlayKey (filter.table(), size);
	//std::copy(filter.table(),filter.table() + (filter.size() / bits_per_char),bloom);
	//bloom = (unsigned char*) filter.table();



}

void SubGen::parseXpe(std::string xpstr, bloom_filter* bl,std::string parent, int &i){
	std::string current;
	//vector<string> rps;
	while (i<xpstr.length()){

		if (xpstr[i]=='/'){

			if (!(parent.empty()||current.empty())) {
				bl->insert(parent+current);
				std::cout<<parent+current<<"\n";
			}
			if (!current.empty()) {
				bl->insert(current);
				std::cout<<current<<"\n";
			}
			parent=current;
			current.clear();
			i=i+1;
		}
		else if (xpstr[ i ]=='[') {
			if (!(parent.empty()||current.empty())) {
				bl->insert(parent+current);
				std::cout<<parent+current<<"\n";
			}
			if (!current.empty()) {
				bl->insert(current);
				std::cout<<current<<"\n";
			}
			parent=current;
			i++;
			parseXpe(xpstr,bl,parent,i);//remember restore the static variable parent after the function returned.
			current.clear();
			i=i+1;
		}
		else if (xpstr[ i ]==']'){
			if (!(parent.empty()||current.empty())) {
				bl->insert(parent+current);
				std::cout<<parent+current<<"\n";
			}
			if (!current.empty()) {
				bl->insert(current);
				std::cout<<current<<"\n";
			}
			i++;
			return;
		}
		else{
			current.insert(current.end(),1,xpstr[i]);
			i=i+1;
		}
	}
}




std::string SubGen::random_line(std::string filepath)
{
	std::ifstream file (filepath.c_str());
	std::string line ;
	std::string selected_line ; // added
	int nlines = 0 ;
	while( getline( file, line ) )
		if(  ( rand() % ++nlines  ) == 0 ) // break ;
			selected_line = line ;
	file.close();
	return selected_line ;
}





