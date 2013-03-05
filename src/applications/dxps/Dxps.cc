//
// Copyright (C) 2006 Institut fuer Telematik, Universitaet Karlsruhe (TH)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//

/**
 * @file Dxps.cc
 * @author Stephan Krause
 */

#include <assert.h>

#include <BaseApp.h>
#include "Dxps.h"
#include <GlobalStatistics.h>
#include "../../tier2/xmlpsapp/bloom_filter.h"
#include "Comparator.h"
#include "../../tier2/xmlpsapp/Filter_m.h"

Define_Module(Dxps);


Dxps::Dxps()
{
  subscriptionTimer = new DxpsTimer("Subscription timer");
  subscriptionTimer->setTimerType( DXPS_SUBSCRIPTION_REFRESH );
  numJoins = 0;
  numChildTimeout = 0;
  numParentTimeout = 0;
  numForward = 0;
  forwardBytes = 0;
  numReceived = 0;
  receivedBytes = 0;
  numHeartbeat = 0;
  heartbeatBytes = 0;
  numSubscriptionRefresh = 0;
  subscriptionRefreshBytes = 0;
  numReplica = 3;
  numUpdateRTEntry  = 0;
}

Dxps::~Dxps()
{
  routingTableList.clear();
  cancelAndDelete(subscriptionTimer);
  // TODO: clear childTimeoutList
}

void Dxps::initializeApp(int stage)
{
  if( stage != (numInitStages()-1))
  {
    return;
  }
  WATCH(routingTableList);
  WATCH(numJoins);
  WATCH(numForward);
  WATCH(forwardBytes);
  WATCH(numReceived);
  WATCH(receivedBytes);
  WATCH(numHeartbeat);
  WATCH(heartbeatBytes);
  WATCH(numSubscriptionRefresh);
  WATCH(subscriptionRefreshBytes);
  WATCH(numChildTimeout);
  WATCH(numParentTimeout);

  childTimeout = par("childTimeout");
  parentTimeout = par("parentTimeout");
  subscriptionfilter =par("subscriptionfilter");
}

void Dxps::finishApp()
{
  simtime_t time = globalStatistics->calcMeasuredLifetime(creationTime);
  if (time < GlobalStatistics::MIN_MEASURED) return;

  globalStatistics->addStdDev("Dxps: Received JOIN Messages/s",
                              numJoins / time);
  globalStatistics->addStdDev("Dxps: Forwarded Publication Messages/s",
                              numForward / time);
  globalStatistics->addStdDev("Dxps: Forwarded Publication Bytes/s",
                              forwardBytes / time);
  globalStatistics->addStdDev("Dxps: Received Publication Messages/s (subscribed groups only)",
                              numReceived / time);
  globalStatistics->addStdDev("Dxps: Received Publication Bytes/s (subscribed groups only)",
                              receivedBytes / time);
  globalStatistics->addStdDev("Dxps: sent Routing Update Message Count)",
                              numUpdateRTEntry  );
  globalStatistics->addStdDev("Dxps: Routing List Entry Count)",
                              routingTableList.size()  );
  //globalStatistics->addStdDev("Dxps: Send Heartbeat Messages/s",
  //numHeartbeat / time);
  //globalStatistics->addStdDev("Dxps: Send Heartbeat Bytes/s",
  //heartbeatBytes / time);
  //globalStatistics->addStdDev("Dxps: Send Subscription Refresh Messages/s",
  //numSubscriptionRefresh / time);
  //globalStatistics->addStdDev("Dxps: Send Subscription Refresh Bytes/s",
  //subscriptionRefreshBytes / time);
  //globalStatistics->addStdDev("Dxps: Number of Child Timeouts/s",
  //numChildTimeout / time);
  //globalStatistics->addStdDev("Dxps: Number of Parent Timeouts/s",
  //numParentTimeout / time);
}

//void Dxps::forward(OverlayKey* key, cPacket** msg,
//                NodeHandle* nextHopNode)
//{
//    DxpsJoinCall* joinMsg = dynamic_cast<DxpsJoinCall*> (*msg);
//    if( joinMsg == NULL ) {
//        // nothing to be done
//        return;
//    }
//
//    if( joinMsg->getSrcNode() == overlay->getThisNode() ) return;
//
//    handleJoinMessage( joinMsg, false );
//
//    *msg = NULL;
//}
void Dxps::forward(OverlayKey* key, cPacket** msg, NodeHandle* nextHopNode){}

void Dxps::update(NodeHandle const& node, bool joined){
  bool err;
  RoutingTableList::iterator it;
  for ( it = routingTableList.begin(); it != routingTableList.end(); ++it)
  {
    if (joined)
    {
      if(it->second.getIsResponsible())
      {
        NodeVector* siblings = overlay->local_lookup(it->first,numReplica,false);
        if (siblings->size()==0){
          delete siblings;
          continue;
        }
        if (overlay->distance(node.getKey(), it->first) < overlay->distance(overlay->getThisNode().getKey(), it->first)) 
        {

          sendPutCall(node,  it->second);
          it->second.setIsResponsible(false);
        }

        if (overlay->distance(node.getKey(), it->first) <= overlay->distance(siblings->back().getKey(), it->first)) 
        {

          sendPutReplicaCall(node,  it->second);
        }
      }
    }
    else{
      it->second.setIsResponsible(overlay->isSiblingFor(overlay->getThisNode(), it->first, 1, &err));
    }

  }

}
void Dxps::sendPutCall(const NodeHandle& node,  const DxpsRoutingTable & entry)
{
  DxpsPutCall* dxpsMsg= new DxpsPutCall();
  dxpsMsg->setRoutingTableEntry(entry);
  sendRouteRpcCall(TIER1_COMP,node,dxpsMsg);
  numUpdateRTEntry++;
}

void Dxps::sendPutReplicaCall(const NodeHandle& node,  const DxpsRoutingTable & entry)
{
  DxpsRoutingTable tmpEntry=entry;
  tmpEntry.setIsResponsible(false);
  sendPutCall(node,tmpEntry);
}


//void Dxps::update( const NodeHandle& node, bool joined )
//{
//    // if node is closer to any group i'm root of, subscribe
//    for( RoutingTableList::iterator it = routingTableList.begin(); it != routingTableList.end(); ++it ){
//        // if I'm root ...
//        if( !it->second.getParent().isUnspecified()
//                && it->second.getParent() == overlay->getThisNode() ) {
//            KeyDistanceComparator<KeyRingMetric> comp( it->second.getLogicalNodeKey() );
//            // ... and new node is closer to groupId
//            if( comp.compare(node.getKey(), overlay->getThisNode().getKey()) < 0){
//                // then the new node is new group root, so send him a subscribe
//                DxpsJoinCall* m = new DxpsJoinCall;
//                m->setlogicalNodeKey( it->second.getLogicalNodeKey() );
//                m->setBitLength( DXPS_JOINCALL_L(m) );
//                sendRouteRpcCall(TIER1_COMP, node, m);
//            }
//        }
//    }
//}

bool Dxps::handleRpcCall(BaseCallMessage* msg)
{
  RPC_SWITCH_START(msg);
  RPC_DELEGATE(DxpsJoin, handleJoinCall);
  RPC_DELEGATE(DxpsPut, handlePutCall);
  RPC_DELEGATE(DxpsSub, handleSubCall);
  RPC_DELEGATE(DxpsPublish, handlePublishCall);
  RPC_SWITCH_END();
  return RPC_HANDLED;
}

void Dxps::handleRpcResponse(BaseResponseMessage* msg,
                             cPolymorphic* context, int rpcId,
                             simtime_t rtt)
{
  RPC_SWITCH_START(msg);
  RPC_ON_RESPONSE( DxpsJoin ) {
    handleJoinResponse( _DxpsJoinResponse );
    EV << "[Dxps::handleRpcResponse() @ " << overlay->getThisNode().getIp()
        << " (" << overlay->getThisNode().getKey().toString(16) << ")]\n"
        << "    Received a DxpsJoin RPC Response: id=" << rpcId << "\n"
        << "    msg=" << *_DxpsJoinResponse << " rtt=" << rtt
        << endl;
    break;
  }
  RPC_ON_RESPONSE( DxpsPublish ) {
    handlePublishResponse( _DxpsPublishResponse );
  }
  RPC_SWITCH_END( );
}

void Dxps::deliver(OverlayKey& key, cMessage* msg)
{
  //    if( DxpsSubscriptionRefreshMessage* refreshMsg =
  //            dynamic_cast<DxpsSubscriptionRefreshMessage*>(msg) ){
  //        // reset child timeout
  //        refreshChildTimer( refreshMsg->getSrc(), refreshMsg->getLogicalNodeKey() );
  //        delete refreshMsg;
  //    } else if( DxpsDataMessage* data = dynamic_cast<DxpsDataMessage*>(msg) ){
  //        deliverALMDataToGroup( data );
  //    } else if( DxpsLeaveMessage* leaveMsg = dynamic_cast<DxpsLeaveMessage*>(msg) ){
  //        handleLeaveMessage( leaveMsg );
  //    }
  if( DxpsDataMessage* data = dynamic_cast<DxpsDataMessage*>(msg) ){
    deliverALMDataToGroup( data );}
  else if( DxpsDataDeliverMessage* dataMsg = dynamic_cast<DxpsDataDeliverMessage*>(msg) ){
    ALMMulticastMessage* mcastMsg = new ALMMulticastMessage( dataMsg->getName() );
    mcastMsg->setGroupId(dataMsg->getLogicalNodeKey());//FIXME:Dose not reveal teh real Group, since I don't have group at all, this is just the parent(logical) nodes.
    DxpsDataMessage* tmpMsg=dynamic_cast<DxpsDataMessage*>(dataMsg->decapsulate());
    mcastMsg->encapsulate( tmpMsg->decapsulate());
    RECORD_STATS(++numReceived; receivedBytes += dataMsg->getByteLength());
    send( mcastMsg, "to_upperTier" );
    delete tmpMsg;
    delete dataMsg;
  }
}

void Dxps::handleUpperMessage( cMessage *msg )
{
  if( ALMSubscribeMessage* subscribeMsg = dynamic_cast<ALMSubscribeMessage*>(msg)){
    subscribeToGroup( subscribeMsg);
  } else if( ALMLeaveMessage* leaveMsg = dynamic_cast<ALMLeaveMessage*>(msg)){
    //leaveGroup( leaveMsg->getGroupId() );
    delete msg;
  } else if( ALMMulticastMessage* mcastMsg = dynamic_cast<ALMMulticastMessage*>(msg) ){
    deliverALMDataToRoot( mcastMsg );
  } else if( ALMAnycastMessage* acastMsg = dynamic_cast<ALMAnycastMessage*>(msg) ){
    // FIXME: anycast not implemented yet
    EV << "[Dxps::handleUpperMessage() @ " << overlay->getThisNode().getIp()
        << " (" << overlay->getThisNode().getKey().toString(16) << ")]\n"
        << "    Anycast message for group " << acastMsg->getGroupId() << "\n"
        << "    ignored: Not implemented yet!"
        << endl;
    delete msg;
  } else if( ALMCreateMessage* createMsg = dynamic_cast<ALMCreateMessage*>(msg) ){
    EV << "[Dxps::handleUpperMessage() @ " << overlay->getThisNode().getIp()
        << " (" << overlay->getThisNode().getKey().toString(16) << ")]\n"
        << "    Create message for group " << createMsg->getGroupId() << "\n"
        << "    ignored: Dxps has implicit create on Subscribe"
        << endl;
    delete msg;
  } else if( ALMDeleteMessage* deleteMsg = dynamic_cast<ALMDeleteMessage*>(msg) ){
    EV << "[Dxps::handleUpperMessage() @ " << overlay->getThisNode().getIp()
        << " (" << overlay->getThisNode().getKey().toString(16) << ")]\n"
        << "    Delete message for group " << deleteMsg->getGroupId() << "\n"
        << "    ignored: Dxps has implicit delete on LEAVE"
        << endl;
    delete msg;
  }
}

void Dxps::handleReadyMessage( CompReadyMessage* msg )
{
  // process only ready messages from the tier below
  if( (getThisCompType() - msg->getComp() == 1) && msg->getReady() ) {
    //        formHyperCube();
    //        if (isHyperCubeReady)
    //        {
    // Send a ready message to the tier above
    CompReadyMessage* readyMsg = new CompReadyMessage;
    readyMsg->setReady( true );
    readyMsg->setComp( getThisCompType() );

    send( readyMsg, "to_upperTier" );

    //        startTimer( subscriptionTimer );//TODO: really needed ?
    //        }
  }
  delete msg;
}
//void Dxps::formHyperCube(){   //TODO: add to .h
// getParents();
// getChildren(); //TODO: maybe not needed.
// isHyperCubeReady=true;
//}//Use Ondemand method, similar to original joincall handle method.
void Dxps::getParents(OverlayKey mykey, OverlayKey fromKey, DxpsSubscriptionMessage* DXPSsubMsg){
  //void Dxps::getParents(OverlayKey mykey, OverlayKey fromKey, ){//TODO: add to .h
  bool startGenerating = false;
  //TODO: only when empty routingtable
  //	OverlayKey mykey=overlay->getThisNode().getKey();
  //if (routingTable.getIsForwarder()) {
  //	return;
  //}
  for(uint32_t i=0;i<mykey.getLength();i++){
    if (fromKey.isUnspecified())
      startGenerating= true;

    else if (mykey.getBit(i)!=fromKey.getBit(i))
      startGenerating= true;
    if (startGenerating){
      if (!mykey.getBit(i)){
        OverlayKey tmpkey= mykey;
        tmpkey.setBit(i,true);
        DxpsJoinCall* newJoin = new DxpsJoinCall;
        newJoin->setDstLogicalNodeKey( tmpkey );//set dstLogicalNodeKey.
        newJoin->setSrcLogicalNodeKey( mykey );//set scrLogicalNodeKey.
        newJoin->setBitLength( DXPS_JOINCALL_L(newJoin) );
        DxpsSubscriptionMessage* NewsubMsg=new DxpsSubscriptionMessage(*DXPSsubMsg);//
        //	            Filter* fn=new Filter();
        //	            fn->setFilter(OverlayKey(1));
        //            NewsubMsg->encapsulate(DXPSsubMsg->getEncapsulatedPacket());
        //	            NewsubMsg->encapsulate(fn);
        newJoin->encapsulate(NewsubMsg);
        sendRouteRpcCall(TIER1_COMP, tmpkey, newJoin);
      }
    }

  }
}
//void getChildren(){
//}
void Dxps::handleTimerEvent( cMessage *msg )
{
  //    DxpsTimer* timer = dynamic_cast<DxpsTimer*>(msg);
  //    assert( timer );
  //    switch( timer->getTimerType() ) {
  //        case DXPS_SUBSCRIPTION_REFRESH:
  //            // renew subscriptions for all groups
  //            for( RoutingTableList::iterator it = routingTableList.begin(); it != routingTableList.end(); ++it ) {
  //                NodeHandle parent = it->second.getParent();
  //                if( !parent.isUnspecified() ){
  //                    DxpsSubscriptionRefreshMessage* refreshMsg = new DxpsSubscriptionRefreshMessage;
  //                    refreshMsg->setlogicalNodeKey( it->second.getLogicalNodeKey() );
  //                    refreshMsg->setSrc( overlay->getThisNode() );
  //
  //                    refreshMsg->setBitLength(DXPS_SUBSCRIPTIONREFRESH_L(refreshMsg));
  //                    RECORD_STATS(++numSubscriptionRefresh;
  //                            subscriptionRefreshBytes += refreshMsg->getByteLength()
  //                    );
  //                    callRoute( OverlayKey::UNSPECIFIED_KEY, refreshMsg, parent );
  //                }
  //            }
  //            startTimer( subscriptionTimer );
  //            break;
  //
  //        case DXPS_HEARTBEAT:
  //        {
  //            // Send heartbeat messages to all children in the group
  //            RoutingTableList::iterator groupIt = routingTableList.find( timer->getGroup() );
  //            if( groupIt == routingTableList.end() ) {
  //                // FIXME: should not happen
  //                delete timer;
  //                return;
  //            }
  //            for( set<NodeHandle>::iterator it = groupIt->second.getChildrenBegin();
  //                    it != groupIt->second.getChildrenEnd(); ++it ) {
  //                DxpsDataMessage* heartbeatMsg = new DxpsDataMessage("Heartbeat");
  //                heartbeatMsg->setEmpty( true );
  //                heartbeatMsg->setlogicalNodeKey( timer->getGroup() );
  //
  //                heartbeatMsg->setBitLength(DXPS_DATA_L(heartbeatMsg));
  //                RECORD_STATS(++numHeartbeat; heartbeatBytes += heartbeatMsg->getByteLength());
  //                callRoute( OverlayKey::UNSPECIFIED_KEY, heartbeatMsg, *it );
  //            }
  //            startTimer( timer );
  //            break;
  //        }
  //        case DXPS_CHILD_TIMEOUT:
  //            // Child failed, remove it from group
  //            RECORD_STATS(++numChildTimeout);
  //            removeChildFromGroup( timer );
  //            break;
  //
  //        case DXPS_PARENT_TIMEOUT:
  //            // Parent failed, send new join to rejoin group
  //            RECORD_STATS(++numParentTimeout);
  //            OverlayKey key = timer->getGroup();
  //            EV << "[Dxps::handleTimerEvent() @ " << overlay->getThisNode().getIp()
  //                << " (" << overlay->getThisNode().getKey().toString(16) << ")]\n"
  //                << "    Parent of group " << key << "\n"
  //                << "    failed to send heartbeat, trying to rejoin"
  //                << endl;
  //
  //            DxpsJoinCall* newJoin = new DxpsJoinCall;
  //            newJoin->setlogicalNodeKey( key );
  //            newJoin->setBitLength( DXPS_JOINCALL_L(newJoin) );
  //            sendRouteRpcCall(TIER1_COMP, key, newJoin);
  //
  //            RoutingTableList::iterator groupIt = routingTableList.find( timer->getGroup() );
  //            if( groupIt == routingTableList.end() ) {
  //                // FIXME: should not happen
  //                delete timer;
  //                return;
  //            }
  //            groupIt->second.setParentTimer( NULL );
  //            cancelAndDelete( timer );
  //            break;
  //    }
  //
}

void Dxps::handleSubCall( DxpsSubCall* subMsg)
{
  RECORD_STATS(++numJoins);
  OverlayKey key = subMsg->getDstLogicalNodeKey();
  DxpsSubscriptionMessage* dataMsg=dynamic_cast<DxpsSubscriptionMessage*>(subMsg->decapsulate());
  Filter* filter = dynamic_cast<Filter*>(dataMsg->getEncapsulatedPacket());
  FilterList filterlist;
  unsigned char  bltable[filter->getFilterArraySize()];
  for (size_t i = 0; i < filter->getFilterArraySize(); ++i)
  {
    bltable[i]=filter->getFilter(i);   
  }
  //bloom_filter FilterKey (1024,1);
  bloom_filter FilterKey (bltable,filter->getFilterSize());
  filterlist.insert(FilterKey);
  //test bloom filter defautl constructor. finally fixed with setting of a
  //8bits 0 bit_table_.
  //bloom_filter tmpfilter(FilterKey);
  //tmpfilter=FilterKey;
  //test end;
  EV << "[Dxps::handleSubCall() @ " << overlay->getThisNode().getIp()
      << " (" << overlay->getThisNode().getKey().toString(16) << ")]\n"
      << "    Received a SubMsg for child's  logical Key " << key << "\n"
      << "    msg=" << subMsg
      << endl; 
  // Insert group into RoutingTableList, if not already there
  std::pair<RoutingTableList::iterator, bool> routingInserter; //TODO: to check if it is a vitural node.
  routingInserter = routingTableList.insert( std::make_pair(key, DxpsRoutingTable(key)) );
  OverlayKey mykey=routingInserter.first->second.getLogicalNodeKey();
  //forward join request to parent//
  getParents(mykey, OverlayKey::UNSPECIFIED_KEY,dataMsg);//secondkey(fromkey in handleDxpsJoin) here should always be unspec, because this is the first forwarder
  //set forwarder, not used currently.
  routingInserter.first->second.setSubscription(true);
  routingInserter.first->second.setIsResponsible(true);
  // Add child to routingTable
  //check if I send request to myself --> this happens when I am the subscriber so I send myself a join request.
  //if (!(joinMsg->getSrcLogicalNodeKey()==overlay->getThisNode().getKey()))//since we have concept of virtual nodes, this is not correct way to identify a message send from it self.
  //it maybe a message aimed at a key who also charged by the same node.
  //if (!(joinMsg->getSrcLogicalNodeKey().isUnspecified()))
  addChildToSubRoutingTable( std::make_pair(subMsg->getSrcLogicalNodeKey(),std::make_pair(subMsg->getSrcNode(),filterlist)), routingInserter.first->second );

  notifySiblings();
  // Send joinResponse
  DxpsSubResponse* joinResponse = new DxpsSubResponse;
  joinResponse->setLogicalNodeKey( key ); //TODO: Maybe need logicalID of parents,
  //send it here.
  joinResponse->setBitLength( DXPS_JOINRESPONSE_L(joinResponse) );
  sendRpcResponse( subMsg, joinResponse );
  delete dataMsg;
}
void Dxps::handleJoinCall( DxpsJoinCall* joinMsg)
{

  OverlayKey key = joinMsg->getDstLogicalNodeKey();
  OverlayKey fromKey= joinMsg->getSrcLogicalNodeKey();
  DxpsSubscriptionMessage* dataMsg=dynamic_cast<DxpsSubscriptionMessage*>(joinMsg->decapsulate());
  Filter* filter = dynamic_cast<Filter*>(dataMsg->getEncapsulatedPacket());
  FilterList filterlist;
  unsigned char  bltable[filter->getFilterArraySize()];
  for (size_t i = 0; i < filter->getFilterArraySize(); ++i)
  {
    bltable[i]=filter->getFilter(i);   
  }
  //bloom_filter FilterKey (1024,1);
  bloom_filter FilterKey (bltable,filter->getFilterSize());
  filterlist.insert(FilterKey);
  //test bloom filter defautl constructor. finally fixed with setting of a
  //8bits 0 bit_table_.
  //bloom_filter tmpfilter(FilterKey);
  //tmpfilter=FilterKey;
  //test end;
  EV << "[Dxps::handleJoinCall() @ " << overlay->getThisNode().getIp()
      << " (" << overlay->getThisNode().getKey().toString(16) << ")]\n"
      << "    Received a JoinMsg for child's  logical Key " << key << "\n"
      << "    msg=" << joinMsg
      << endl; 
  // Insert group into RoutingTableList, if not already there
  std::pair<RoutingTableList::iterator, bool> routingInserter; //TODO: to check if it is a vitural node.
  routingInserter = routingTableList.insert( std::make_pair(key, DxpsRoutingTable(key)) );
  OverlayKey mykey=routingInserter.first->second.getLogicalNodeKey();
  //forward join request to parent
  getParents(mykey, fromKey,dataMsg);
  //set forwarder, not used currently.
  routingInserter.first->second.setForwarder(true);
  routingInserter.first->second.setIsResponsible(true);  
  // Add child to routingTable
  //check if I send request to myself --> this happens when I am the subscriber so I send myself a join request.
  //if (!(joinMsg->getSrcLogicalNodeKey()==overlay->getThisNode().getKey()))//since we have concept of virtual nodes, this is not correct way to identify a message send from it self.
  //it maybe a message aimed at a key who also charged by the same node.
  if (!(joinMsg->getSrcLogicalNodeKey().isUnspecified()))
  {
    addChildToRoutingTable( std::make_pair(joinMsg->getSrcLogicalNodeKey(),std::make_pair(joinMsg->getSrcNode(),filterlist)), routingInserter.first->second );
    notifySiblings();
  }
  // Send joinResponse
  DxpsJoinResponse* joinResponse = new DxpsJoinResponse;
  joinResponse->setLogicalNodeKey( key ); //TODO: Maybe need logicalID of parents,
  //send it here.
  joinResponse->setBitLength( DXPS_JOINRESPONSE_L(joinResponse) );
  sendRpcResponse( joinMsg, joinResponse );
  delete dataMsg;
}
//void Dxps::handleJoinMessage( DxpsJoinCall* joinMsg, bool amIRoot)
//{
//    RECORD_STATS(++numJoins);
//    OverlayKey key = joinMsg->getLogicalNodeKey();
//
//    EV << "[Dxps::handleJoinMessage() @ " << overlay->getThisNode().getIp()
//        << " (" << overlay->getThisNode().getKey().toString(16) << ")]\n"
//        << "    Received a DxpsJoin for group " << key << "\n"
//        << "    msg=" << joinMsg
//        << endl;
//
//    // Insert group into grouplist, if not already there
//    pair<RoutingTableList::iterator, bool> groupInserter;
//    groupInserter = routingTableList.insert( std::make_pair(key, DxpsGroup(key)) );
//
//    // If group is new or no parent is known, send join to parent (unless I am root, so there is no parent)
//    if ( !amIRoot && ( groupInserter.second || groupInserter.first->second.getParent().isUnspecified()) ) {
//        DxpsJoinCall* newJoin = new DxpsJoinCall;
//        newJoin->setlogicalNodeKey( key );
//        newJoin->setBitLength( DXPS_JOINCALL_L(newJoin) );
//        sendRouteRpcCall(TIER1_COMP, key, newJoin);
//    }
//
//    // If group had no children, start heartbeat timer for group
//    if( groupInserter.first->second.numChildren() == 0 ) {
//        DxpsTimer* heartbeat = new DxpsTimer("HeartbeatTimer");
//        heartbeat->setTimerType( DXPS_HEARTBEAT );
//        heartbeat->setGroup( groupInserter.first->second.getLogicalNodeKey() );
//        startTimer( heartbeat );
//        if( DxpsTimer* t = groupInserter.first->second.getHeartbeatTimer() ){
//            // delete old timer, if any
//            if( t ) cancelAndDelete( t );
//        }
//        groupInserter.first->second.setHeartbeatTimer( heartbeat );
//    }
//
//    // Add child to group
//    addChildToRoutingTable( joinMsg->getSrcNode(), groupInserter.first->second );
//
//    // Send joinResponse
//    DxpsJoinResponse* joinResponse = new DxpsJoinResponse;
//    joinResponse->setlogicalNodeKey( key );
//    joinResponse->setBitLength( DXPS_JOINRESPONSE_L(joinResponse) );
//    sendRpcResponse( joinMsg, joinResponse );
//}

void Dxps::handlePublishCall( DxpsPublishCall* publishCall )
{
  DxpsDataMessage* data = dynamic_cast<DxpsDataMessage*>(publishCall->decapsulate());//decapsulate thedata for later use.
  data->setDxpsMsgId(data->getId());//hack: to use a unique identifier at dxps routing layer, delete msg with same id at intermidiate nodes.
  //inform sender that  publish is successful.
  //TODO: need test here
  DxpsPublishResponse* msg = new DxpsPublishResponse("Publish Successful");
  msg->setLogicalNodeKey( publishCall->getLogicalNodeKey() );
  msg->setBitLength( DXPS_PUBLISHRESPONSE_L(msg) );
  sendRpcResponse( publishCall, msg );

  if( !data ) {
    // TODO: throw exception? this should never happen
    EV << "[Dxps::handlePublishCall() @ " << overlay->getThisNode().getIp()
        << " (" << overlay->getThisNode().getKey().toString(16) << ")]\n"
        << "    PublishCall for group " << msg->getLogicalNodeKey()
        << "    does not contain a valid ALM data message!\n"
        << endl;
    return;
  }
  deliverALMDataToGroup( data );
}

void Dxps::handleJoinResponse( DxpsJoinResponse* joinResponse )
{
}
void Dxps::handleSubResponse( DxpsSubResponse* joinResponse )
{
}

void Dxps::handlePublishResponse( DxpsPublishResponse* publishResponse )
{
  RoutingTableList::iterator it = routingTableList.find( publishResponse->getLogicalNodeKey() );
  if( it == routingTableList.end() ) {
    EV << "[Dxps::handlePublishResponse() @ " << overlay->getThisNode().getIp()
        << " (" << overlay->getThisNode().getKey().toString(16) << ")]\n"
        << "Getting publish response for an unknown RN!\n";
    return;
  }

  //    if( publishResponse->getWrongRoot() ) {
  //        it->second.setRendezvousPoint( NodeHandle::UNSPECIFIED_NODE );
  //    } else {
  //        it->second.setRendezvousPoint( publishResponse->getSrcNode() );
  //    } //Since we use
}

void Dxps::handlePutCall( DxpsPutCall* putMsg)
{
  //TODO: remove old entry, insert new entry, send response.
  DxpsRoutingTable entry=putMsg->getRoutingTableEntry();
  OverlayKey key=entry.getLogicalNodeKey();
  if (!entry.getIsResponsible())
  {
    routingTableList[key]=entry;
  }
  else{

    std::pair<RoutingTableList::iterator, bool> routingInserter; //TODO: to check if it is a vitural node.
    routingInserter = routingTableList.insert( std::make_pair(key, entry) );
    if (!routingInserter.second)
    {
      for (std::map<OverlayKey,NfPair>::iterator iter=entry.getChildrenBegin() ; iter != entry.getChildrenEnd(); ++iter)
      {
      addChildToRoutingTable(  *iter, routingInserter.first->second);
      }

      //throw new cRuntimeError("got an routing table entry renew request for an existing routing entry that is responsible");
    }
  }
  //send response, so far no feed back embeded.
  DxpsPutResponse* pRsp= new DxpsPutResponse;
  pRsp->setLogicalNodeKey(entry.getLogicalNodeKey());
  pRsp->setBitLength( DXPS_JOINRESPONSE_L(joinResponse) );
  sendRpcResponse(putMsg,pRsp);
}
void Dxps::handlePutResponse( DxpsPutResponse* putRsp)
{}
//void Dxps::handleLeaveMessage( DxpsLeaveMessage* leaveMsg )
//{
//    RoutingTableList::iterator it = routingTableList.find( leaveMsg->getLogicalNodeKey() );
//    if( it != routingTableList.end() ){
//        removeChildFromGroup( leaveMsg->getSrc(), it->second );
//    }
//    delete leaveMsg;
//}

void Dxps::subscribeToGroup( ALMSubscribeMessage* subMsg )
{   
  //decapsulate received upper layer message and recapsulate it in
  //Filter* testfilter = dynamic_cast<Filter*>(subMsg->getEncapsulatedPacket());
  //std::cout<<"test getencap inside"<<testfilter->getFilterArraySize();
  //DxpsSubscriptionMessage;
  DxpsSubscriptionMessage* dataMsg = new DxpsSubscriptionMessage( subMsg->getName() );//get the name of upper message and use it.
  dataMsg->setLogicalNodeKey(overlay->getThisNode().getKey());//For later User. use subscriber's key to add to its RN's routing table as a child.
  dataMsg->setBitLength( DXPS_SUBSCRIPTIONMESSAGE_L( subMsg ));
  dataMsg->encapsulate( subMsg->decapsulate() );
  //test purpose only;
  //Filter* filter = dynamic_cast<Filter*>(dataMsg->getEncapsulatedPacket());
  ////std::cout<<"test getencap inside"<<filter->getFilterArraySize();
  //std::cout<<"got sub filter \n";
  //unsigned char  bltable[filter->getFilterArraySize()];

  //for (size_t i = 0; i < filter->getFilterArraySize(); ++i)
  //{
  //bltable[i]=filter->getFilter(i);   
  //std::cout<<"bloom filter is:"<<(int)bltable[i];
  //}
  //std::cout<<"\n";
  ////std::cout<<"fitlersize is:"<<filter->getFilterSize();
  //bloom_filter FilterKey (bltable,filter->getFilterSize());

  //std::cout<< "I am here";

  // Using DxpsJoinCall (RPC) to send supscriptions in KBR layer. Uses KBR
  // routing.
  // test end!
  DxpsSubCall* msg = new DxpsSubCall;
  //msg->setSrcLogicalNodeKey( overlay->getThisNode().getKey());
  msg->setSrcLogicalNodeKey(overlay->getThisNode().getKey());//using unspecified key, needed for spanning tree generation.
  msg->setDstLogicalNodeKey(subMsg->getGroupId());
  msg->setBitLength(  DXPS_JOINCALL_L(msg) );
  msg->encapsulate( dataMsg );


  //    TODO: set subscription flag, create routingtable if not exists.
  //std::pair<RoutingTableList::iterator, bool> groupInserter;
  //OverlayKey mykey=overlay->getThisNode().getKey();
  //groupInserter = routingTableList.insert( std::make_pair(mykey, DxpsRoutingTable(mykey)) );
  //groupInserter.first->second.setSubscription(true);
  //will not use ownfilter as I have this handled by my RN node.I will say yes
  //to everything he send me.
  //groupInserter.first->second.insertToOwnFilterList(FilterKey);

  //    if( !groupInserter.first->second.getRendezvousPoint().isUnspecified() ) {
  //        // ... directly to the rendevouz point, if known ...
  ////        sendRouteRpcCall(TIER1_COMP, groupInserter.first->second.getRendezvousPoint(), msg);//TODO: maynot be considered, but maybe useful.
  //    } else {
  // ... else route it via KBR
  sendRouteRpcCall(TIER1_COMP, subMsg->getGroupId(), msg);
  //    }

  delete subMsg;
}

//void Dxps::leaveGroup( const OverlayKey& group )
//{
//    RoutingTableList::iterator it = routingTableList.find( group );
//    if( it != routingTableList.end() ){
//        it->second.setSubscription( false );
//        checkGroupEmpty( it->second );
//    }
//}

void Dxps::addChildToRoutingTable( const Children& child, DxpsRoutingTable& routingTable )
{
  //    if( child == overlay->getThisNode()) ) {
  //        // Join from ourself, ignore
  //        return;
  //    }

  // add child to group's children list
  std::pair<std::map<OverlayKey, NfPair>::iterator, bool> inserter = routingTable.addChild( child );
  if (!inserter.second){
    routingTable.modChild( child);
  }

  //    if( inserter.second ) {
  //        // if child has not been in the list, create new timeout msg
  //        DxpsTimer* timeoutMsg = new DxpsTimer;
  //        timeoutMsg->setTimerType( DXPS_CHILD_TIMEOUT );

  //        // Remember child and group
  //        timeoutMsg->setChild( *inserter.first );
  //        timeoutMsg->setGroup( group.getLogicalNodeKey() );
  //
  //        startTimer( timeoutMsg );
  //        childTimeoutList.insert( std::make_pair(child, timeoutMsg) );
  //    }
}
void Dxps::addChildToSubRoutingTable( const Children& child, DxpsRoutingTable& routingTable )
{
  //    if( child == overlay->getThisNode()) ) {
  //        // Join from ourself, ignore
  //        return;
  //    }

  // add child to group's children list
  std::pair<std::map<OverlayKey, NfPair>::iterator, bool> inserter = routingTable.addSubChild( child );
  if (!inserter.second){
    routingTable.modSubChild( child);
  }

  //    if( inserter.second ) {
  //        // if child has not been in the list, create new timeout msg
  //        DxpsTimer* timeoutMsg = new DxpsTimer;
  //        timeoutMsg->setTimerType( DXPS_CHILD_TIMEOUT );

  //        // Remember child and group
  //        timeoutMsg->setChild( *inserter.first );
  //        timeoutMsg->setGroup( group.getLogicalNodeKey() );
  //
  //        startTimer( timeoutMsg );
  //        childTimeoutList.insert( std::make_pair(child, timeoutMsg) );
  //    }
}
void Dxps::notifySiblings(){
  RoutingTableList::iterator it;
  for (it = routingTableList.begin(); it != routingTableList.end(); it++) {
    if (it->second.getIsResponsible()) {
      NodeVector* siblings = overlay->local_lookup(it->first, numReplica, false); 
      if (siblings->size() == 0) {
        delete siblings;
        continue;
      }
      for (size_t i = 1; i < siblings->size(); ++i)
      {

        sendPutReplicaCall((*siblings)[i],it->second);
      }
      delete siblings;
    }
  }
}
//void Dxps::removeChildFromGroup( const NodeHandle& child, DxpsRoutingTable& group )
//{
//    // find timer
//    DxpsTimer* timer = NULL;
//    pair<ChildTimeoutList::iterator, ChildTimeoutList::iterator> ret =
//        childTimeoutList.equal_range( child );
//    if( ret.first != childTimeoutList.end() ){
//        for( ChildTimeoutList::iterator it = ret.first; it!=ret.second; ++it) {
//            if( group == it->second->getLogicalNodeKey() ) {
//                timer = it->second;
//                childTimeoutList.erase( it );
//                cancelAndDelete( timer );
//                break;
//            }
//        }
//    }
//
//    // remove child from group's childrenlist
//    group.removeChild( child );
//
//    checkGroupEmpty( group );
//}
//
//void Dxps::removeChildFromGroup( DxpsTimer* timer )
//{
//    NodeHandle& child = timer->getChild();
//
//    RoutingTableList::iterator groupIt = routingTableList.find( timer->getLogicalNodeKey() );
//    if( groupIt != routingTableList.end() ) {
//        DxpsRoutingTable& group = groupIt->second;
//        // remove child from routing table's childrenlist
//        group.removeChild( child );
//
//        checkGroupEmpty( group );
//    }
//
//    // remove timer from timeoutlist
//    pair<ChildTimeoutList::iterator, ChildTimeoutList::iterator> ret =
//        childTimeoutList.equal_range( child );
//    if( ret.first != childTimeoutList.end() ) {
//        for( ChildTimeoutList::iterator it = ret.first; it!=ret.second; ++it) {
//            if( it->second == timer ) {
//                childTimeoutList.erase( it );
//                cancelAndDelete( timer );
//                break;
//            }
//        }
//    }
//}

//void Dxps::checkGroupEmpty( DxpsRoutingTable& group )
//{
//    if( !group.isForwarder() && !group.getSubscription() && !group.getAmISource()){
//
//        if( !group.getParent().isUnspecified() && group.getParent() != overlay->getThisNode() ) {
//
//            DxpsLeaveMessage* msg = new DxpsLeaveMessage("Leave");
//            msg->setlogicalNodeKey( group.getLogicalNodeKey() );
//            msg->setSrc( overlay->getThisNode() );
//            msg->setBitLength( DXPS_LEAVE_L(msg) );
//            callRoute( OverlayKey::UNSPECIFIED_KEY, msg, group.getParent() );
//        }
//
//        if( group.getParentTimer() ) cancelAndDelete( group.getParentTimer() );
//        if( group.getHeartbeatTimer() ) cancelAndDelete( group.getHeartbeatTimer() );
//        routingTableList.erase( group.getLogicalNodeKey() );
//    }
//}
//
//void Dxps::refreshChildTimer( NodeHandle& child, OverlayKey& groupId )
//{
//    // find timer
//    pair<ChildTimeoutList::iterator, ChildTimeoutList::iterator> ret =
//        childTimeoutList.equal_range( child );
//    // no timer yet?
//    if( ret.first == childTimeoutList.end() ) return;
//
//    // restart timer
//    for( ChildTimeoutList::iterator it = ret.first; it!=ret.second; ++it) {
//        if( it->first == child && it->second->getGroup() == groupId ) {
//            startTimer( it->second );
//        }
//    }
//}
//
//void Dxps::startTimer( DxpsTimer* timer )
//{
//    if( timer->isScheduled() ) {
//        cancelEvent( timer );
//    }
//
//    int duration = 0;
//    switch( timer->getTimerType() ) {
//        case DXPS_HEARTBEAT:
//            duration = parentTimeout/2;
//            break;
//        case DXPS_SUBSCRIPTION_REFRESH:
//            duration = childTimeout/2;
//            break;
//        case DXPS_PARENT_TIMEOUT:
//            duration = parentTimeout;
//            break;
//        case DXPS_CHILD_TIMEOUT:
//            duration = childTimeout;
//            break;
//    }
//    scheduleAt(simTime() + duration, timer );
//}

void Dxps::deliverALMDataToRoot( ALMMulticastMessage* mcastMsg )
{
  //    // find group
  //    pair<RoutingTableList::iterator, bool> groupInserter;
  //    groupInserter = routingTableList.insert( std::make_pair(mcastMsg->getLogicalNodeKey(), DxpsRoutingTable(mcastMsg->getLogicalNodeKey())) );
  //
  //    // Group is not known yet
  //    if( groupInserter.second ) {
  //        groupInserter.first->second.setAmISource( true );
  //        // TODO: Start/Restart timer to clean up cached groups
  //        // If the timer expires, the flag should be cleared and checkGroupEmpty should be called
  //        //
  //        // FIXME: amISource should be set allways if app publishes messages to the group
  //        // As the timer is not implemented yet, we only set the flag in "sender, but not receiver" mode
  //        // to reduce the amount of unneccessary cached groups
  //    }
  //above code is useless because we don't need to remember destination node(root node in this case).
  DxpsDataMessage* dataMsg = new DxpsDataMessage( mcastMsg->getName() );
  dataMsg->setLogicalNodeKey( mcastMsg->getGroupId() );//this is from upper layer mcastmsg, mcast use groupid as the multicast ovkey, equivlant to the RN(root in scribe) of a publisher.
  dataMsg->setBitLength( DXPS_DATA_L( dataMsg ));
  dataMsg->encapsulate( mcastMsg->decapsulate() );

  // Send publish ...
  DxpsPublishCall* msg = new DxpsPublishCall( "DxpsPublish" );
  msg->setLogicalNodeKey( dataMsg->getLogicalNodeKey() );
  msg->setBitLength( DXPS_PUBLISHCALL_L(msg) );
  msg->encapsulate( dataMsg );

  //    if( !groupInserter.first->second.getRendezvousPoint().isUnspecified() ) {
  //        // ... directly to the rendevouz point, if known ...
  ////        sendRouteRpcCall(TIER1_COMP, groupInserter.first->second.getRendezvousPoint(), msg);//TODO: maynot be considered, but maybe useful.
  //    } else {
  // ... else route it via KBR
  sendRouteRpcCall(TIER1_COMP, msg->getLogicalNodeKey(), msg);
  //    }

  delete mcastMsg;
}


void Dxps::deliverALMDataToGroup( DxpsDataMessage* dataMsg )
{

  // find logicalNodeKey.
  RoutingTableList::iterator it = routingTableList.find( dataMsg->getLogicalNodeKey() );
  if( it == routingTableList.end() ) {
    EV << "[Dxps::deliverALMDataToGroup() @ " << overlay->getThisNode().getIp()
        << "Getting publication message for an unknown group,maybe no subscriber yet!\n";
    delete dataMsg;
    //std::cout<<"deleted: no sub\n";
    return;
  }
  //TODO: when one of my logical node is the child of the other logical node. maybe do not need to send it to kbr.
  // FIXME: ignore message if not from designated parent to avoid duplicates

  // reset parent heartbeat Timer
  //TODO: not implemented , need to set a time for a datamsg as well.
  //and delete this msg after certain thresh hold, queue it before it timeout to check if the
  // after coming msg are duplicate.

  //    DxpsTimer *timer = it->second.getParentTimer();
  //    if( timer ) startTimer( timer );

  // Only empty heartbeat?
  if( dataMsg->getEmpty() ) {
    EV << "publication is empty(dxpsdata packet has no encapsulation)\n";
    delete dataMsg;
    return;
  }

  if(it->second.getIsResponsible())
  //if(0)
  {
    // deliver data to children TODO: LinkActivation only delliver to child that is "activated"
    for( std::map<OverlayKey, NfPair>::iterator cit = it->second.getChildrenBegin(); cit != it->second.getChildrenEnd(); ++cit ) 
    {
      bool ismatched=false; //reset evaluation result to false
      //do matching here!if subscriptionfilter is set to true;

      if (subscriptionfilter)
      {
        Filter* filter = dynamic_cast<Filter*>(dataMsg->getEncapsulatedPacket()->getEncapsulatedPacket());
        unsigned char  bltable[filter->getFilterArraySize()];
        for (size_t i = 0; i < filter->getFilterArraySize(); ++i) 
        {
          bltable[i]=filter->getFilter(i);   
        }
        ismatched=matchit(cit->second.second,bloom_filter(bltable,filter->getFilterSize()));
      }

      if(!subscriptionfilter || ismatched)
      {
        DxpsDataMessage* newMsg = new DxpsDataMessage( *dataMsg );
        newMsg->setDxpsMsgId(dataMsg->getId());//keep the same dxpsMsgId;
        newMsg->setLogicalNodeKey(cit->first);
        RECORD_STATS(++numForward; forwardBytes += newMsg->getByteLength());
        callRoute( cit->first, newMsg );//TODO: tweak this to route through KBR.
        //callRoute( OverlayKey::UNSPECIFIED_KEY, newMsg, cit->second.first );//TODO: tweak this to route through KBR.
      }
    }
    //deliver data to subscriber for each entry in subChildren list
    for( std::map<OverlayKey, NfPair>::iterator cit = it->second.getSubChildrenBegin(); cit != it->second.getSubChildrenEnd(); ++cit ) 
    {
      bool ismatched=false; //reset evaluation result to false
      //do matching here!if subscriptionfilter is set to true;

      if (subscriptionfilter)
      {
        Filter* filter = dynamic_cast<Filter*>(dataMsg->getEncapsulatedPacket()->getEncapsulatedPacket());
        unsigned char  bltable[filter->getFilterArraySize()];
        for (size_t i = 0; i < filter->getFilterArraySize(); ++i) {
          bltable[i]=filter->getFilter(i);   
        }
        ismatched=matchit(cit->second.second,bloom_filter(bltable,filter->getFilterSize()));
      }

      if(!subscriptionfilter || ismatched){
        DxpsDataDeliverMessage* newMsg = new DxpsDataDeliverMessage();
        DxpsDataMessage* tmpMsg = new DxpsDataMessage( *dataMsg );
        newMsg->setDxpsMsgId(dataMsg->getId());//keep the same dxpsMsgId;
        newMsg->setLogicalNodeKey(cit->first);
        newMsg->encapsulate(tmpMsg);
        callRoute( OverlayKey::UNSPECIFIED_KEY, newMsg, cit->second.first );//TODO: tweak this to route through KBR.
      }
    }
  }
  delete dataMsg;
}

    bool  Dxps::matchit(FilterList fromTable, bloom_filter pubKey)
    {
      FilterList::iterator Filter_it=fromTable.begin();
      for (size_t i = 0; i < fromTable.size(); ++i) {
        if (keycompare(*Filter_it,pubKey)) return true;    
        //start of debuging code
        //std::cout<<"subkey After to\n";
        //for (size_t ii = 0; ii < Filter_it->size()/bits_per_char; ++ii)
        //{
        ////std::cout<<std::hex<<(int) (Filter_it->table()[ii]);
        //}
        //std::cout<<"\n vs pub size:"<<pubKey.size()<<"\n";
        //for (size_t ij = 0; ij < pubKey.size()/bits_per_char; ++ij)
        //{
        //std::cout<<std::hex<<(int) (pubKey.table()[ij]);
        //}
        //std::cout<<"\n";
        //end of testing.
        Filter_it++;
      }
      //std::cout<<"EpicFailAll\n";
      return false;


      //this is the function to compare two filter(OverlayKey type)

    }  
    bool Dxps::keycompare(bloom_filter subKey,bloom_filter pubKey){
      //if (subKey.ZERO
      //for (size_t ii = 0; ii < pubKey.getLength(); ++ii)
      //{
      //if (subKey.getBit(i)==1 && pubKey(i)==1) return false;
      //}
      //return true;
      //std::cout<<"pubkeyafter:\n";
      //for (size_t ij = 0; ij < pubKey.size()/bits_per_char; ++ij)
      //{
      ////std::cout<<std::hex<<(int) (pubKey.table()[ij]);
      //}
      //std::cout<<"\n";
      //std::cout<<"matching result should be 128 0 \n";
      //for (size_t ii = 0; ii < pubKey.size()/bits_per_char; ++ii)
      //{

      ////std::cout<<std::hex<<(int) ((pubKey.table()[ii]&subKey.table()[ii])^subKey.table()[ii]);
      ////if ((pubKey.table()[ii]&subKey.table()[ii])^subKey.table()[ii]!=0) return false;
      //}
      //std::cout<<"\n";
      if ((pubKey & subKey ^ subKey).isZero()) return true;
      return false;
    }
