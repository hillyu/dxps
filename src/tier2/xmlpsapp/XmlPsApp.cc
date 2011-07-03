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
#include "subgen.h"
Define_Module(XmlPsApp);
const int BLOOM_L=32;
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
}

void XmlPsApp::handleTimerEvent( cMessage* msg )
{
    if( msg == timer ) {
        double random = uniform( 0, 1 );
        if( (random < 1 && joinGroups) || subscribeList.empty() ) {
            bloom_filter bloomfilter (BLOOM_L,BLOOM_K);
            SubGen sub (bloomfilter);
            //groupNum=sub.getBloom();

            //EV <<"the Xpath expression is:"<<sub.getXpe()<<"\n";
            EV <<"the bloom filter is:"<<(unsigned long)*bloomfilter.table()<<"\n";
            EV <<"the overlaykey is:" <<OverlayKey(bloomfilter.table(),bloomfilter.size()/8).toString();
            //joinGroup(16);
            joinGroup(bloomfilter.table(),bloomfilter.size()/8);
            //    subscribeList.push_back (bloomfilter);
            //            std::list<int>::iterator it;
            //            it=subscribeList.end();
            //            it=--it;
            //            EV<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<*it<<"groupNum is:"<<groupNum;
        }
        //        else if( random < subRate+unsubRate && joinGroups ) {
        //            std::list<bloom_filter>::iterator it;
        //            it=subscribeList.begin();
        //            int random=intuniform(1, subscribeList.size()/8);
        //            int i;
        //            for (i = 0; i < random; i++) {
        //                it++;
        //            }
        //            //leaveGroup( it->table(),it->size()/8);
        //            subscribeList.erase(it);//randomly delete a subscription
        //        }
        else if ( sendMessages ) {
            sendDataToGroup( intuniform( 1, groupNum ));
        }
        scheduleAt( simTime() + 10, timer );
    }
}
//void XmlPsApp::sendDataToGroup( int i )
//{
//
//    ALMMulticastMessage* msg = new ALMMulticastMessage("Multicast message");
//    msg->setGroupId(OverlayKey(i));
//
//    ALMTestTracedMessage* traced = new ALMTestTracedMessage("Traced message");
//    traced->setTimestamp();
//    traced->setGroupId(OverlayKey(i));
//    traced->setMcastId(traced->getId());
//    traced->setSenderId(getId());
//    traced->setByteLength(msglen);
//
//    msg->encapsulate(traced);
//
//    send(msg, "to_lowerTier");
//
//    observer->sentMessage(traced);
//}
void XmlPsApp::joinGroup(const unsigned char *buffer, uint32_t size)
{

    ALMSubscribeMessage* msg = new ALMSubscribeMessage;
    msg->setGroupId(OverlayKey (buffer, size));
    send(msg, "to_lowerTier");

    observer->joinedGroup(getId(), OverlayKey (buffer, size));
}

void XmlPsApp::leaveGroup(const unsigned char *buffer, uint32_t size)
{
    ALMLeaveMessage* msg = new ALMLeaveMessage;
    msg->setGroupId(OverlayKey (buffer, size));
    send(msg, "to_lowerTier");

    observer->leftGroup(getId(), OverlayKey (buffer, size));
}

SubGen::SubGen(bloom_filter& filter){
    //reading from a subscription pool
    std::string SUBFILE="/Users/hill/work/oversim/test/bib.xpelist";
    xpe=random_line(SUBFILE);
    xpe+="/";
    int i=0;
    parseXpe(xpe,&filter,"",i);
    bloom=(unsigned int)*(const unsigned char*)filter.table();

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

