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

#include "Comparator.h"

Define_Module(Dxps);

using namespace std;

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

}

void Dxps::finishApp()
{
    simtime_t time = globalStatistics->calcMeasuredLifetime(creationTime);
    if (time < GlobalStatistics::MIN_MEASURED) return;

    globalStatistics->addStdDev("Dxps: Received JOIN Messages/s",
            numJoins / time);
    globalStatistics->addStdDev("Dxps: Forwarded Multicast Messages/s",
            numForward / time);
    globalStatistics->addStdDev("Dxps: Forwarded Multicast Bytes/s",
            forwardBytes / time);
    globalStatistics->addStdDev("Dxps: Received Multicast Messages/s (subscribed groups only)",
            numReceived / time);
    globalStatistics->addStdDev("Dxps: Received Multicast Bytes/s (subscribed groups only)",
            receivedBytes / time);
    globalStatistics->addStdDev("Dxps: Send Heartbeat Messages/s",
            numHeartbeat / time);
    globalStatistics->addStdDev("Dxps: Send Heartbeat Bytes/s",
            heartbeatBytes / time);
    globalStatistics->addStdDev("Dxps: Send Subscription Refresh Messages/s",
            numSubscriptionRefresh / time);
    globalStatistics->addStdDev("Dxps: Send Subscription Refresh Bytes/s",
            subscriptionRefreshBytes / time);
    globalStatistics->addStdDev("Dxps: Number of Child Timeouts/s",
            numChildTimeout / time);
    globalStatistics->addStdDev("Dxps: Number of Parent Timeouts/s",
            numParentTimeout / time);
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
void Dxps::forward(OverlayKey* key, cPacket** msg,
		NodeHandle* nextHopNode){}
void Dxps::update(NodeHandle const&, bool){}



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
void Dxps::getParents(DxpsRoutingTable& routingTable){  //TODO: add to .h

//TODO: only when empty routingtable
//	OverlayKey mykey=overlay->getThisNode().getKey();
	OverlayKey mykey=routingTable.getLogicalNodeKey();
if (routingTable.getIsForwarder()) {//TODO: make it in specific table
	return;
}
  for(uint32_t i=0;i<mykey.getLength();i++){
    if (!mykey.getBit(i)){
      OverlayKey tmpkey= mykey;
    tmpkey.setBit(i,true);
    DxpsJoinCall* newJoin = new DxpsJoinCall;
        newJoin->setDstLogicalNodeKey( tmpkey );//set dstLogicalNodeKey.
        newJoin->setSrcLogicalNodeKey( mykey );//set scrLogicalNodeKey.
        newJoin->setBitLength( DXPS_JOINCALL_L(newJoin) );
        sendRouteRpcCall(TIER1_COMP, tmpkey, newJoin);
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

//void Dxps::handleJoinCall( DxpsJoinCall* joinMsg)
//{
//    handleJoinMessage( joinMsg, true );
//}
void Dxps::handleJoinCall( DxpsJoinCall* joinMsg)
{

    RECORD_STATS(++numJoins);//TODO: need to tweak all RECORD_STATS;
    OverlayKey key = joinMsg->getDstLogicalNodeKey();
    EV << "[Dxps::handleJoinCall() @ " << overlay->getThisNode().getIp()
        << " (" << overlay->getThisNode().getKey().toString(16) << ")]\n"
        << "    Received a JoinMsg for child's  logical Key " << key << "\n"
        << "    msg=" << joinMsg
        << endl; 
    // Insert group into RoutingTableList, if not already there
    pair<RoutingTableList::iterator, bool> routingInserter; //TODO: to check if it is a vitural node.
    routingInserter = routingTableList.insert( make_pair(key, DxpsRoutingTable(key)) );
    //TODO start heartbeat
    //forward join request to parent
    getParents(routingInserter.first->second);
    //set forwarder
    routingInserter.first->second.setForwarder(true);
    // Add child to routingTable
    //check if I send request to myself --> this happens when I am the subscriber so I send myself a join request.
    if (!(joinMsg->getSrcLogicalNodeKey()==overlay->getThisNode().getKey()))
    addChildToRoutingTable( make_pair(joinMsg->getSrcLogicalNodeKey(),joinMsg->getSrcNode()), routingInserter.first->second );

    // Send joinResponse
    DxpsJoinResponse* joinResponse = new DxpsJoinResponse;
    joinResponse->setLogicalNodeKey( key ); //TODO: Maybe need logicalID of parents,
    //send it here.
    joinResponse->setBitLength( DXPS_JOINRESPONSE_L(joinResponse) );
    sendRpcResponse( joinMsg, joinResponse ); 
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
//    groupInserter = routingTableList.insert( make_pair(key, DxpsGroup(key)) );
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
    // find logicalnodekey and according table.
    RoutingTableList::iterator it = routingTableList.find( publishCall->getLogicalNodeKey() );
    // if I don't know this logicalnodekey (because no subscriber yet) inform sender I am wrong root.
    if( it == routingTableList.end()){

        // TODO: low priority: forward message when I'm not root but know the rendevous point?
        DxpsPublishResponse* msg = new DxpsPublishResponse("Wrong Root");
        msg->setLogicalNodeKey( publishCall->getLogicalNodeKey() );
        msg->setWrongRoot( true );
        msg->setBitLength( DXPS_PUBLISHRESPONSE_L(msg) );
        sendRpcResponse( publishCall, msg );
    } else {
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
}

void Dxps::handleJoinResponse( DxpsJoinResponse* joinResponse )
{
//    RoutingTableList::iterator it = routingTableList.find( joinResponse->getLogicalNodeKey() );
//    if( it == routingTableList.end() ) {
//        EV << "[Dxps::handleJoinResponse() @ " << overlay->getThisNode().getIp()
//            << " (" << overlay->getThisNode().getKey().toString(16) << ")]\n"
//            << "Getting join response for an unknown group!\n";
//        return;
//    }
//    it->second.setParent( joinResponse->getSrcNode() );
//
//    // Create new heartbeat timer
//    DxpsTimer* parentTimeout = new DxpsTimer("ParentTimeoutTimer");
//    parentTimeout->setTimerType( DXPS_PARENT_TIMEOUT );
//    parentTimeout->setGroup( it->second.getLogicalNodeKey() );
//    startTimer( parentTimeout );
//    if( DxpsTimer* t = it->second.getParentTimer() ){
//        // delete old timer, if any
//        if( t ) cancelAndDelete( t );
//    }
//    it->second.setParentTimer( parentTimeout );
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
	DxpsSubscriptionMessage* dataMsg = new DxpsSubscriptionMessage( subMsg->getName() );//TODO: edit application subpacket
	    dataMsg->setLogicalNodeKey(overlay->getThisNode().getKey());//For later User. use subscriber's key to add to its RN's routing table as a child.
	    //dataMsg->setDstLogicalNodeKey(subMsg->getGroupId());
	    dataMsg->setBitLength( DXPS_SUBSCRIPTIONMESSAGE_L( dataMsg ));
	    dataMsg->encapsulate( subMsg->decapsulate() );//FIXME:this should be empty by now

	    // Send subscribe ...
	    DxpsJoinCall* msg = new DxpsJoinCall;
	    msg->setSrcLogicalNodeKey( overlay->getThisNode().getKey());
	    msg->setDstLogicalNodeKey(subMsg->getGroupId());
	    msg->setBitLength( DXPS_PUBLISHCALL_L(msg) );
	    msg->encapsulate( dataMsg );

	//    TODO: set subscription flag, create routingtable if not exists.
	    pair<RoutingTableList::iterator, bool> groupInserter;
	    OverlayKey mykey=overlay->getThisNode().getKey();
	    groupInserter = routingTableList.insert( make_pair(mykey, DxpsRoutingTable(mykey)) );
	    groupInserter.first->second.setSubscription(true);

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
    pair<set<Children>::iterator, bool> inserter =
        routingTable.addChild( child );

//    if( inserter.second ) {
//        // if child has not been in the list, create new timeout msg
//        DxpsTimer* timeoutMsg = new DxpsTimer;
//        timeoutMsg->setTimerType( DXPS_CHILD_TIMEOUT );

//        // Remember child and group
//        timeoutMsg->setChild( *inserter.first );
//        timeoutMsg->setGroup( group.getLogicalNodeKey() );
//
//        startTimer( timeoutMsg );
//        childTimeoutList.insert( make_pair(child, timeoutMsg) );
//    }
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
//    groupInserter = routingTableList.insert( make_pair(mcastMsg->getLogicalNodeKey(), DxpsRoutingTable(mcastMsg->getLogicalNodeKey())) );
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
	//Important to delete duplicate msg and avoid osilicate.

//	for ( size_t i = 0;  i < msgLog.size(); ++ i) {
//		if (msgLog[i]==dataMsg->getDxpsMsgId()) {
//			delete dataMsg;
//			return;
//		}
//	}

    // find logicalNodeKey.
    RoutingTableList::iterator it = routingTableList.find( dataMsg->getLogicalNodeKey() );
    if( it == routingTableList.end() ) {
        EV << "[Dxps::deliverALMDataToGroup() @ " << overlay->getThisNode().getIp()
            << "Getting ALM data message response for an unknown group!\n";
        delete dataMsg;
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
        delete dataMsg;
        return;
    }

    // deliver data to children TODO: LinkActivation only delliver to child that is "activated"
    for( set<Children>::iterator cit = it->second.getChildrenBegin();
            cit != it->second.getChildrenEnd(); ++cit ) {
        DxpsDataMessage* newMsg = new DxpsDataMessage( *dataMsg );
        newMsg->setDxpsMsgId(dataMsg->getId());//keep the same dxpsMsgId;
        newMsg->setLogicalNodeKey(cit->first);
        RECORD_STATS(++numForward; forwardBytes += newMsg->getByteLength());
        callRoute( OverlayKey::UNSPECIFIED_KEY, newMsg, cit->second );
    }

    // deliver to myself if I'm subscribed to that group //TODO: create a new talbe for subscribers and check that talbe here. and deliver.
    if( it->second.getSubscription() ) {
        ALMMulticastMessage* mcastMsg = new ALMMulticastMessage( dataMsg->getName() );
        mcastMsg->setGroupId(dataMsg->getLogicalNodeKey());//FIXME:Dose not reveal teh real Group, since I don't have group at all, this is just the parent(logical) nodes.
        mcastMsg->encapsulate( dataMsg->decapsulate() );
        RECORD_STATS(++numReceived; receivedBytes += dataMsg->getByteLength());
        send( mcastMsg, "to_upperTier" );
    }

    delete dataMsg;
}

