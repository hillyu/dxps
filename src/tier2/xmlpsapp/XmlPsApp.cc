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
const int BLOOM_L=32;
const int BLOOM_K=1;

XmlPsApp::XmlPsApp() {
  // TODO Auto-generated constructor stub

  timer = new cMessage( "app_timer");
  joinGroups = true;
  sendMessages = true;
  xmlpsapp_observer = NULL;



}
//
XmlPsApp::~XmlPsApp() {
  cancelAndDelete( timer );
}

void XmlPsApp::initializeApp(int stage)
{
  if( stage != (numInitStages()-1))
  {
    return;
  }
  xmlpsapp_observer = check_and_cast<XmlPsAppMessageObserver*>(
      simulation.getModuleByPath("globalObserver.globalFunctions[0].function.observer"));
  joinGroups = par("joinGroups");
  msglen = par("messageLength");
  sendMessages = par("sendMessages");
  maxSubscription=par("maxSubscription");
  subRate=par("subRate");
  unsubRate=par("unsubRate");
  groupNum=0;
  expandJoin=par("expandJoin");
  WATCH_VECTOR(subscribeList);

}




void XmlPsApp::handleLowerMessage(cMessage* msg)
{
  ALMMulticastMessage* mcast = dynamic_cast<ALMMulticastMessage*>(msg);
  if ( mcast != 0 ) {
    handleMCast(mcast);
  }
}

void XmlPsApp::handleReadyMessage(CompReadyMessage* msg)
{
  if( (getThisCompType() - msg->getComp() == 1) && msg->getReady() ) {
    groupNum = 0;
    cancelEvent(timer);
    scheduleAt(simTime() + 1, timer);
  }
  delete msg;
}


void XmlPsApp::handleTimerEvent( cMessage* msg )
{
  if( msg == timer ) {
    double random = uniform( 0, 1 );
    //subRate=0.1;
    if (subscribeList.size()>=maxSubscription)
      joinGroups=false;

    if (subscribeList.empty()) {
      bloom_filter bloomfilter (BLOOM_L,BLOOM_K);
      SubGen sub (bloomfilter);
      subscribe(sub.getBloom());
      subscribeList.push_back (sub);
      EV <<"the xpe is:"<<sub.getXpe().c_str()<<"\n";
      EV <<"the bloom filter from list is:"<<subscribeList.back().getBloom().toString()<<"\n";
    }
    else if( (random < subRate && joinGroups) ) {

      bloom_filter bloomfilter (BLOOM_L,BLOOM_K);
      SubGen sub (bloomfilter);
      bool isrepeat=false;
      bool isblrepeat=false;
      for (size_t i = 0; i < subscribeList.size(); ++i) {
        if ((subscribeList[i].getBloom()== sub.getBloom())){
          isblrepeat=true;

        }
        if (subscribeList[i].getXpe()==sub.getXpe()) {
          isrepeat=true;
        }
      }
      if (!isrepeat) {
        if (!isblrepeat) {
          subscribe(sub.getBloom());
        }
        subscribeList.push_back (sub);
      }

    }
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
      //int i=(intuniform(1, subscribeList.size())-1);
      //sendDataToGroup( subscribeList[i].getBloom());
      std::string xmlfile=xmlGen();
      OverlayKey validkey=xml2bloom(xmlfile);
      if(!validkey.isUnspecified())
      sendDataToGroup(validkey,xmlfile);

      //EV <<"data send to"<<(unsigned long)*subscribeList[i].getBloom()<<"\n";
      //
    }
    scheduleAt( simTime() + 10, timer );
  }

}


void XmlPsApp::subscribe(OverlayKey ovkey)
{
  if (expandJoin){
    recursiveJoin(ovkey,0);
    EV<<"Original Key to subscribe is : "<<ovkey<<"\n";
  }
  else joinGroup(ovkey);
}
void XmlPsApp::recursiveJoin(OverlayKey ovkey, int i){
  //while( i <=ovkey.getLength()) {
  while( i <=BLOOM_L) {

    // if(i==ovkey.getLength())
    if(i==BLOOM_L){
      joinGroup(ovkey);
      EV<<"Genreated Subscrition is:"<<ovkey.toString(2)<<"\n";}
    else if (ovkey[ovkey.getLength()-i-1]==0){
      OverlayKey tmpkey=ovkey;
      tmpkey[ovkey.getLength()-i-1]=1;
      recursiveJoin(ovkey,i+1);
      recursiveJoin(tmpkey,i+1);
      break;
    }
    ++i;
  }
}
void XmlPsApp::joinGroup(OverlayKey ovkey)
{

  ALMSubscribeMessage* msg = new ALMSubscribeMessage;
  msg->setGroupId(ovkey);
  send(msg, "to_lowerTier");

  xmlpsapp_observer->joinedGroup(getId(), ovkey);
}

//void XmlPsApp::leaveGroup(const unsigned char *buffer, uint32_t size)
void XmlPsApp::leaveGroup(OverlayKey ovkey)
{
  ALMLeaveMessage* msg = new ALMLeaveMessage;
  //msg->setGroupId(OverlayKey (buffer, size));
  msg->setGroupId(ovkey);
  send(msg, "to_lowerTier");

  xmlpsapp_observer->leftGroup(getId(), ovkey);
}

//void XmlPsApp::sendDataToGroup(const unsigned char *buffer, uint32_t size){
void XmlPsApp::sendDataToGroup(OverlayKey ovkey,std::string data){

  ALMMulticastMessage* msg = new ALMMulticastMessage("Multicast message");
  //msg->setGroupId(OverlayKey (buffer, size));
  msg->setGroupId(ovkey);
  //TODO maybe have something to do with the ned file definition of the msg type.
  XmlPsAppTracedMessage* traced = new XmlPsAppTracedMessage("Traced message");
  traced->setTimestamp();
  traced->setGroupId(ovkey);
  traced->setMcastId(traced->getId());
  traced->setSenderId(getId());
  traced->setXmlFileName(data.c_str());
  traced->setByteLength(msglen);

  msg->encapsulate(traced);

  send(msg, "to_lowerTier");

  xmlpsapp_observer->sentMessage(traced);
}

void XmlPsApp::handleMCast( ALMMulticastMessage* mcast )
{
  getParentModule()->getParentModule()->bubble("Received message!");
  EV << "[ALMTest::handleMCast()]\n"
      << "    App received data message for group: " << mcast->getGroupId()
      << endl;

  XmlPsAppTracedMessage* traced = check_and_cast<XmlPsAppTracedMessage*>(mcast->decapsulate());
  traced->setReceiverId(getId());

  traced->setFalse_positive(evaluateXpe(traced->getXmlFileName()));
  xmlpsapp_observer->receivedMessage(traced);

  delete traced;

  delete mcast;
}




std::string XmlPsApp::xmlGen()
{
  std::string pathlist = "../samplefiles/xmldocs/filelist.txt";
  std::string xmlfile=SubGen::random_line(pathlist);
  EV << "The PathList is "<<pathlist<<"\n";
  EV << "The XMLFILE INPUT is"<<xmlfile<<"\n";
  struct stat filestatus;
  stat( xmlfile.c_str(), &filestatus );
  msglen=filestatus.st_size;
  return xmlfile;
}


bool XmlPsApp::evaluateXpe(std::string xmlfilename){
  TiXmlDocument  XDp_doc;
  XDp_doc.LoadFile (xmlfilename);
  //			XDp_doc.LoadFile ("/Users/hill/test.xml");
  //			EV<<"The XML FILENAME IS: "<<xmlfilename<<"\n";
  //			TIXML_STRING S_res;
  //S_res=TinyXPath::S_xpath_string (XDp_doc.RootElement (), "/");
  //int i_res;//int is not working.
  //			S_res = TinyXPath::S_xpath_string (XDp_doc.RootElement (), "/*");
  //			EV<<"THE RESUlt IS: "<<S_res<<"\n";
  //i_res = TinyXPath::i_xpath_int (XDp_doc.RootElement (), "/bib");
  //groupNum=sub.getBloom();
  for (int i = 0; i < subscribeList.size(); ++i) {
    if (!((TinyXPath::S_xpath_string (XDp_doc.RootElement (), subscribeList[i].getXpe().c_str())).empty()))
      //				if (!((TinyXPath::S_xpath_string (XDp_doc.RootElement (), "/bib/")).empty()))
      return false;
  }
  return true;
}

OverlayKey XmlPsApp::xml2bloom(std::string xmlfilename){
  bloom_filter bloomfilter (BLOOM_L,BLOOM_K);
  TiXmlDocument  XDp_doc;
  XDp_doc.LoadFile (xmlfilename);
  if(XDp_doc.RootElement()){
  EV<<"TheRootElementis:"<<XDp_doc.RootElement()->ValueStr()<<"\n";
  recursivex2b(XDp_doc.RootElement (),bloomfilter);
  return OverlayKey (bloomfilter.table(), bloomfilter.size()/bits_per_char);
  }
  return OverlayKey::UNSPECIFIED_KEY;
}
void XmlPsApp::recursivex2b(TiXmlElement* parent, bloom_filter & bloomfilter){

  TiXmlElement* child = 0;
  if(parent)
	  bloomfilter.insert(parent->ValueStr());
  if(parent->FirstChildElement()){
  for( child = parent->FirstChildElement(); child; child = child->NextSiblingElement() ){
    bloomfilter.insert(child->ValueStr());
    bloomfilter.insert(parent->ValueStr()+child->ValueStr());
    if (!child->NoChildren()){
      recursivex2b(child, bloomfilter);

    }
  }
  }
}















SubGen::SubGen():xpe(""),size(0),bloom(0){}

SubGen::SubGen(bloom_filter& filter){
  //reading from a subscription pool
  std::string SUBFILE="/Users/hill/work/oversim/test/bib.xpelist";
  xpe=random_line(SUBFILE);
  int i=0;
  parseXpe(xpe+"/",&filter,"",i);
  size=filter.size()/bits_per_char;
//  EV<<"BLOOM SIXE  IS:"<<filter.size()<<"\n";
  bloom=OverlayKey (filter.table(), size);
//size=8;
//  unsigned char p[size];
//  for (size_t i = 0;  i < size; ++i) {
////	  EV<<"BLOOM FILTER IN SUBGEN IS:"<<(unsigned long)filter.table()[i]<<"\n";
//	  p[i]&=0x00;
//	  p[i]|=0x01;
//}
//  bloom=OverlayKey (p, 8);
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

std::ostream & operator <<(std::ostream & os,  SubGen  & subg)
{
  return os << "bloom: " << subg.getBloom() << "; xpe: " << subg.getXpe();
}







