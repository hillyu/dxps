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
#include "Filter_m.h"
#include "XmlPsAppTracedMessage_m.h"
Define_Module(XmlPsApp);


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
  pubRate=par("pubRate");
  unsubRate=par("unsubRate");
  groupNum=0;
  subSize=0;
  expandJoin=par("expandJoin");
  WATCH_VECTOR(subscribeList);
  WATCH(ov_key);
  bloom_l=par("bloom_l");
  bloom_k=par("bloom_k");
  bloom2_l=par("bloom2_l");
  bloom2_k=par("bloom2_k");
  xpepath=par("xpepath").stdstringValue(); 
  xmllist=par("xmllist").stdstringValue();
  appStartDelay=par("appStartDelay");
  filter_l=par("filter_l");
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
    //subPool=SubGen::getPool(bloom_l,bloom_k,overlay->getThisNode().getKey(),xpepath);//This has been replaced since I do not reuire subkey to be equals to the nodes  key. 
    cancelEvent(timer);
    //test functions please comment out
    //testxmldoc(xmllist);
    //texst function end;
    scheduleAt(simTime() + appStartDelay, timer);//wait for 3000s
    ov_key=overlay->getThisNode().getKey();
  }
  delete msg;
}


void XmlPsApp::handleTimerEvent( cMessage* msg )
{
  if( msg == timer ) {
    double random = uniform( 0, 1 );
    if (subscribeList.size()>=maxSubscription)
    //if (subSize>=maxSubscription)
      joinGroups=false;
    //if (subscribeList.empty()) {
    if ( random < subRate && joinGroups) {
      SubGen sub (bloom_l,bloom_k, xpepath);
      //std::cout<<subPool.size()<<"\n";
      //std::cout<<sub.getXpe()<<"\n";
      OverlayKey filter= sub.getBloom();
      std::vector<SubGen>::iterator it;
      it =find(subscribeList.begin(),subscribeList.end(),sub);
      if (!filter.isUnspecified() && it==subscribeList.end())
      //if (!filter.isUnspecified() )
      {
        //EV <<"the bloom filter from list is:"<<subscribeList.back().getBloom().toString()<<"\n";
        joinGroup(filter,sub.getXpe());
        subscribeList.push_back (sub);
        //subSize++;
      }
    }
    else if (random < subRate+pubRate && sendMessages ) {//FIXME only let 15 send.
      //else if (0 ) {//FIXME only let 15 send.
      //int i=(intuniform(1, subscribeList.size())-1);
      //sendDataToGroup( subscribeList[i].getBloom());
      //while (1){
        std::string xmlfile=xmlGen();
        //std::cout<<"I got the file to bloom"<<xmlfile<<"\n";
        OverlayKey tmpkey=xml2bloom(xmlfile,bloom_l, bloom_k);
        if (!tmpkey.isUnspecified()){
          sendDataToGroup(tmpkey,xmlfile);
          //break;
        }
      //}
    }
    scheduleAt( simTime() + 10, timer );
    }
  }
//{
  //if( msg == timer ) {
    //double random = uniform( 0, 1 );
    ////subrate=0.1;
    //if (subscribelist.size()>=maxsubscription)
      //joingroups=false;
    ////if (overlay->getthisnode().getkey().todouble()==2 && subscribelist.empty()) {//fixme;; test should use following line
    ////if (subscribelist.empty()) {
    //if ((!subpool.empty()) && random < subrate && joingroups) {
      ////subgen sub (bloom_l,bloom_k,overlay->getthisnode().getkey(),   xpepath);
      //double rindex=uniform(0,subpool.size());
      //subgen sub=subpool[rindex];
      ////std::cout<<subpool.size()<<"\n";
      ////std::cout<<sub.getxpe()<<"\n";
      //overlaykey filter= sub.getbloom();
      //std::vector<subgen>::iterator it;
      //it =find(subscribelist.begin(),subscribelist.end(),sub);
      //if (!filter.isunspecified() && it==subscribelist.end())
      //{
        //ev <<"the xpe is:"<<sub.getxpe().c_str()<<"\n";
        //ev <<"the bloom filter from list is:"<<subscribelist.back().getbloom().tostring()<<"\n";
        //joingroup(filter,sub.getxpe());
        //subscribelist.push_back (sub);
      //}
    //}
    //else if (random < subrate+pubrate && sendmessages ) {//fixme only let 15 send.
      ////else if (sendmessages ) {//fixme only let 15 send.
      ////int i=(intuniform(1, subscribelist.size())-1);
      ////senddatatogroup( subscribelist[i].getbloom());
      //while (1){
        //std::string xmlfile=xmlgen();
        ////std::cout<<"i got the file to bloom"<<xmlfile<<"\n";
        //overlaykey tmpkey=xml2bloom(xmlfile,bloom_l, bloom_k);
        //if (!tmpkey.isunspecified()){
          //senddatatogroup(tmpkey,xmlfile);
          //break;
        //}
      //}


    //}
    //scheduleAt( simTime() + 10, timer );
    //}

  //}
  //void XmlPsApp::subscribe(OverlayKey ovkey){
  //if (expandJoin){
  //recursiveJoin(ovkey,0);
  //EV<<"Original Key to subscribe is : "<<ovkey<<"\n";
  //}
  //else joinGroup(ovkey);
  //}
  void XmlPsApp::recursiveJoin(OverlayKey ovkey, int i){
    //while( i <=ovkey.getLength()) {
    //while( i <=bloom_l) {

    // if(i==ovkey.getLength())
    //if(i==bloom_l){
    //joinGroup(ovkey);
    //EV<<"Genreated Subscrition is:"<<ovkey.toString(2)<<"\n";}
    //else if (ovkey[ovkey.getLength()-i-1]==0){
    //OverlayKey tmpkey=ovkey;
    //tmpkey[ovkey.getLength()-i-1]=1;
    //recursiveJoin(ovkey,i+1);
    //recursiveJoin(tmpkey,i+1);
    //break;
    //}
    //++i;
    //}
  }
  void XmlPsApp::joinGroup(OverlayKey ovkey,std::string xpath)
  {

    ALMSubscribeMessage* msg = new ALMSubscribeMessage("Subscribe Message");
    msg->setGroupId(ovkey);
    Filter * filter=new Filter;

    int i=0;//Very important used by recursive funcition, need to reset every new run.
    bloom_filter filtertmplate (bloom2_l,bloom2_k);
    SubGen sub;//create a empty subgen object to use its parse function.
    //std::cout<<"the xpe to test is:\n"<<xpath;

    sub.parseXpe(xpath+"/",&filtertmplate,"",i);
    int size=filtertmplate.size()/bits_per_char;
    //OverlayKey secondfilter=OverlayKey (filtertmplate.table(), size);
    filter->setFilterArraySize(size);
    //std::cout<<"filer size"<<filter->getFilterArraySize();
    //std::cout<<"subkey is:\n";
    for (size_t i = 0; i < size; ++i)
    {
      //std::cout<<"original: "<<(int)filtertmplate.table()[i];
      filter->setFilter(i,filtertmplate.table()[i]);
      //std::cout<<std::hex<<(int) filtertmplate.table()[i];
    }
    //std::cout<<"\n";
    //filter->setFilter(filtertmplate.table());//TODO: temperarily set it to 1

    filter->setFilterSize(bloom2_l);
    msg->encapsulate(filter);
    //TODO: for test purpose.
    //Filter* testfilter = dynamic_cast<Filter*>(msg->getEncapsulatedPacket());
    //std::cout<<"test getencap"<<testfilter->getFilterSize();
    //test end
    send(msg, "to_lowerTier");
    //std::cout<<"create sub filter success \n";
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

  //dataMsg->setDstLogicalNodeKey(subMsg->getGroupId());
  //void XmlPsApp::sendDataToGroup(const unsigned char *buffer, uint32_t size){
  void XmlPsApp::sendDataToGroup(OverlayKey ovkey,std::string data){

    ALMMulticastMessage* msg = new ALMMulticastMessage("Publication message");
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
    Filter* filter=new Filter;
    bloom_filter tmpbl=xml2bloom2(data,bloom2_l,bloom2_k);
    filter->setFilterArraySize(bloom2_l/bits_per_char);
    //std::cout<<"pubKeyfor"<<data<<"\n";
    for (size_t i = 0; i <bloom2_l/bits_per_char ; ++i)
    {
      filter->setFilter(i,tmpbl.table()[i]);  
      //std::cout<<std::hex<<(int) tmpbl.table()[i];
    }
    //std::cout<<"\n test answer is; \n";
    //int i=0;//Very important used by recursive funcition, need to reset every new run.
    //bloom_filter filtertmplate (bloom2_l,bloom2_k);
    //SubGen sub;//create a empty subgen object to use its parse function.
    //std::string xpath1="/club/clubname";
    //sub.parseXpe(xpath1+"/",&filtertmplate,"",i);
    //int size=filtertmplate.size()/bits_per_char;
    //for (size_t i = 0; i < size; ++i)
    //{
    //std::cout<<std::hex<<(int) ((tmpbl.table()[i]&filtertmplate.table()[i])^filtertmplate.table()[i]);
    ////std::cout<<std::hex<<(int) filtertmplate.table()[i];
    //}
    //std::cout<<"\n";
    filter->setFilterSize(bloom2_l);
    filter->setBitLength(filter_l);
    traced->encapsulate(filter);
    msg->encapsulate(traced);

    send(msg, "to_lowerTier");
    //std::cout<<"create data filter success\n";
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
    std::string pathlist = xmllist;//"/home/hill/sim/OverSim-20101103/samplefiles/xmldocs/filelist2.txt";
    std::string xmlfile=SubGen::random_line(pathlist);
    //std::cout <<xmlfile<<"\n";
    EV << "The PathList is "<<pathlist<<"\n";
    EV << "The XMLFILE INPUT is"<<xmlfile<<"\n";
    struct stat filestatus;
    stat( xmlfile.c_str(), &filestatus );
    msglen=filestatus.st_size;
    //std::cout<<"size is"<<msglen<<"\n";
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

  OverlayKey XmlPsApp::xml2bloom(std::string xmlfilename,int l, int k){
    bloom_filter bloomfilter (l,k);
    TiXmlDocument  XDp_doc;
    //std::cout<<"the file to load:"<<xmlfilename<<"\n";
    if (XDp_doc.LoadFile (xmlfilename.c_str(),TIXML_ENCODING_UTF8 )){
      //std::cout<<"TheRootElementis:"<<XDp_doc.RootElement()->ValueStr()<<"\n";
      recursivex2b(XDp_doc.RootElement (),bloomfilter);
      return OverlayKey (bloomfilter.table(), bloomfilter.size()/bits_per_char);
    }
    //else throw new cRuntimeError("file %s can not be opened",xmlfilename.c_str());
    return OverlayKey::UNSPECIFIED_KEY;
  }
  bloom_filter XmlPsApp::xml2bloom2(std::string xmlfilename,int l, int k){
    bloom_filter bft (l,k);
    TiXmlDocument  XDp_doc;
    //std::cout<<"the file to load:"<<xmlfilename<<"\n";
    if (XDp_doc.LoadFile (xmlfilename.c_str(),TIXML_ENCODING_UTF8 )){
      //std::cout<<"TheRootElementis:"<<XDp_doc.RootElement()->ValueStr()<<"\n";
      recursivex2b(XDp_doc.RootElement (),bft);
      //std::cout<<"the bloom inside xml2bloom2:\n";
      //for (size_t i = 0; i <bloom2_l/bits_per_char ; ++i)
      //{
      //std::cout<<std::hex<<(int)bft.table()[i];
      //}
      //std::cout<<"\n";
      return bft;
    }
    else throw new cRuntimeError("file %s can not be opened in creating a second filter",xmlfilename.c_str());
    //return OverlayKey::UNSPECIFIED_KEY;
  }
  void XmlPsApp::recursivex2b(TiXmlElement* parent, bloom_filter & bloomfilter){

    TiXmlElement* child = 0;
    //std::cout<<"parent"<<parent->ValueStr()<<"\n";
    bloomfilter.insert(parent->ValueStr());
    for( child = parent->FirstChildElement(); child; child = child->NextSiblingElement() ){
      //std::cout<<"child"<<child->ValueStr()<<"\n";
      bloomfilter.insert(child->ValueStr());
      bloomfilter.insert(parent->ValueStr()+child->ValueStr());
      if (!child->NoChildren()){
        recursivex2b(child, bloomfilter);

      }
    }
  }

  /***************************************************************************
   *                              testfunctions                              *
   ***************************************************************************/
  void XmlPsApp::testxmldoc(std::string xmldoclist){
    //std::string filepath="/home/hill/sim/OverSim-20101103/samplefiles/xmldocs/filelist.txt";
    bloom_filter bloomfilter (bloom_l,bloom_k);
    std::ifstream file (xmldoclist.c_str());
    std::string filetoload;
    while( getline( file, filetoload ) ){

      //std::cout<<"file to load"<<filetoload<<"\n";
      TiXmlDocument  XDp_doc;
      if (XDp_doc.LoadFile (filetoload.c_str(),TIXML_ENCODING_UTF8 )){
        //std::cout<<"TheRootElementis:"<<XDp_doc.RootElement()->ValueStr()<<"\n";
        recursivex2b(XDp_doc.RootElement (),bloomfilter);
        //std::cout<<"bloom: ["<< OverlayKey (bloomfilter.table(), bloomfilter.size()/bits_per_char);
      }
      else {
        //std::cout<<"bloom: [fail]";
      }
      //std::cout<<"] success"<<"\n";
    }
    file.close();
    throw new cRuntimeError("all files passed test");
    return ;
  }
  /***************************************************************************
   *                            test function end                            *
   ***************************************************************************/














  SubGen::SubGen():xpe(""),size(0),bloom(OverlayKey::UNSPECIFIED_KEY){}

  SubGen::SubGen(OverlayKey key, std::string myxpe){
    bloom=key;
    xpe=myxpe;
    size=key.getLength()/bits_per_char;
  }
  SubGen::SubGen(bloom_filter& filter){
    //reading from a subscription pool
    //std::string SUBFILE="/home/hill/sim/OverSim-20101103/samplefiles/xpaths/bib.xpelist";
    //xpe=random_line(SUBFILE);//TODO test so use a root as xpe
    xpe="/bib/vendor/name";
    int i=0;
    parseXpe(xpe+"/",&filter,"",i);
    size=filter.size()/bits_per_char;
    bloom=OverlayKey (filter.table(), size);
    //std::copy(filter.table(),filter.table() + (filter.size() / bits_per_char),bloom);
    //bloom = (unsigned char*) filter.table();
  }
  SubGen::SubGen(int l, int k, std::string xpelist){
    //    std::ifstream file (filepath.c_str());
    xpe=random_line(xpelist);//TODO test so use a root as xpe
      int i=0;//Very important used by recursive funcition, need to reset every new run.
      bloom_filter filter (l,k);
      parseXpe(xpe+"/",&filter,"",i);
      size=filter.size()/bits_per_char;
      OverlayKey tmpkey=OverlayKey (filter.table(), size);
        bloom=tmpkey;
      }
  SubGen::SubGen(int l, int k, OverlayKey mykey, std::string xpelist){
    //    std::ifstream file (filepath.c_str());
    std::string filepath=xpelist;//"/home/hill/sim/OverSim-20101103/samplefiles/xpaths/bib.xpelist";
    std::ifstream file (filepath.c_str());
    std::string line ;
    while( getline( file, line ) ){
      std::string tmpxpe = line ;
      int i=0;//Very important used by recursive funcition, need to reset every new run.
      bloom_filter filter (l,k);
      parseXpe(tmpxpe+"/",&filter,"",i);
      size=filter.size()/bits_per_char;
      OverlayKey tmpkey=OverlayKey (filter.table(), size);
      //std::cout<<tmpxpe<<"xpe_bloom: "<<tmpkey<<" mykey :"<<mykey<<"\n";
      if (tmpkey==mykey){
        bloom=tmpkey;
        xpe=tmpxpe;
        break;            
      }
    }
    file.close();
  }
  void SubGen::parseXpe(std::string xpstr, bloom_filter* bl,std::string parent, int &i){
    std::string current;
    //vector<string> rps;
    while (i<xpstr.length()){

      if (xpstr[i]=='/'){

        if (!(parent.empty()||current.empty())) {
          bl->insert(parent+current);
          //std::cout<<parent+current<<"bloom: "<<OverlayKey(bl->table(),bl->size()/bits_per_char)<<"\n";
        }
        if (!current.empty()) {
          bl->insert(current);
          //std::cout<<current<<"\n";
          //std::cout<<parent+current<<"bloom: "<<OverlayKey(bl->table(),bl->size()/bits_per_char)<<"\n";
        }
        parent=current;
        current.clear();
        i=i+1;
      }
      else if (xpstr[ i ]=='[') {
        if (!(parent.empty()||current.empty())) {
          bl->insert(parent+current);
          //std::cout<<parent+current<<"\n";
          //std::cout<<parent+current<<"bloom: "<<OverlayKey(bl->table(),bl->size()/bits_per_char)<<"\n";
        }
        if (!current.empty()) {
          bl->insert(current);
          //std::cout<<current<<"\n";
          //std::cout<<parent+current<<"bloom: "<<OverlayKey(bl->table(),bl->size()/bits_per_char)<<"\n";
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
          //std::cout<<parent+current<<"\n";
          //std::cout<<parent+current<<"bloom: "<<OverlayKey(bl->table(),bl->size()/bits_per_char)<<"\n";
        }
        if (!current.empty()) {
          bl->insert(current);
          //std::cout<<current<<"\n";
          //std::cout<<parent+current<<"bloom: "<<OverlayKey(bl->table(),bl->size()/bits_per_char)<<"\n";
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


  std::vector<SubGen> SubGen::getPool(int l, int k, OverlayKey mykey, std::string xpelist)
  {
    std::vector<SubGen> pool;
    std::string filepath=xpelist;//"/home/hill/sim/OverSim-20101103/samplefiles/xpaths/bib.xpelist";
    std::ifstream file (filepath.c_str());
    std::string line ;
    while( getline( file, line ) ){
      std::string tmpxpe = line ;
      int i=0;//Very important used by recursive funcition, need to reset every new run.
      bloom_filter filter (l,k);
      parseXpe(tmpxpe+"/",&filter,"",i);
      size_t mysize=filter.size()/bits_per_char;
      OverlayKey tmpkey=OverlayKey (filter.table(), mysize);
      //std::cout<<tmpxpe<<"xpe_bloom: "<<tmpkey<<" mykey :"<<mykey<<"\n";
      if (tmpkey==mykey){
        pool.push_back(SubGen(tmpkey,tmpxpe));
      }
    }
    file.close();
    return pool;
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







