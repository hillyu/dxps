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
 * @file XmlPsAppXmlPsAppMessageObserver.cc
 * @author Dimitar Toshev
 */

#include <assert.h>
#include <sstream>
#include <omnetpp.h>
#include <GlobalStatisticsAccess.h>
#include "XmlPsAppMessageObserver.h"
#include "XmlPsAppTracedMessage_m.h"

Define_Module(XmlPsAppMessageObserver);

XmlPsAppMessageObserver::XmlPsAppMessageObserver() {
    gcTimer = new cMessage("garbage_collection");
    gcInterval = 1.0;
    cacheMaxAge = 10.0;
    numLooped = 0;
}

XmlPsAppMessageObserver::~XmlPsAppMessageObserver() {
    cancelAndDelete(gcTimer);
}

void XmlPsAppMessageObserver::initialize() {
    WATCH_MAP(subList);
    WATCH_MAP(pubList);
    WATCH_MAP(joinedAt);
    WATCH_MAP(sendAt);
    WATCH_MAP(receivedAt);
    WATCH(numLooped);

    numLooped = 0;
    gcInterval = par("gcInterval");
    cacheMaxAge = par("cacheMaxAge");

    if (gcInterval > 0.0)
        scheduleAt(OPP::simTime() + gcInterval, gcTimer);

    creationTime = OPP::simTime();
    globalStatistics = GlobalStatisticsAccess().get();
}

void XmlPsAppMessageObserver::finish() { //TODO:need to rewrite the scalar generator.
    uint64_t totalSent = 0;
    uint64_t totalReceived = 0;
    for (std::map<int, Subscription>::iterator i = subList.begin(); i != subList.end(); ++i) {
        std::stringstream message;
        message << "XmlPsAppMessageObserver: Node " << i->first;
        std::string name;

        //name = message.str() + " Sent Messages";
        //recordScalar(name.c_str(), (double)i->second.sent);

        name = message.str() + " Received Messages";
        recordScalar(name.c_str(), (double)i->second.received);

        //name = message.str() + " Delivered Percentage";
        //recordScalar(name.c_str(), ((double)i->second.received * 100.0) / (double)i->second.sent);

        //totalSent += i->second.sent;
        totalReceived += i->second.received;
    }

    //recordScalar("XmlPsAppMessageObserver: Total Sent Messages", (double)totalSent);
    recordScalar("XmlPsAppMessageObserver: Total Received Messages", (double)totalReceived);
    recordScalar("XmlPsAppMessageObserver: Total Delivered Percentage", ((double)totalReceived * 100.0) / (double)totalSent);

    simtime_t time = globalStatistics->calcMeasuredLifetime(creationTime);
    if ( time >= GlobalStatistics::MIN_MEASURED ) {
        globalStatistics->addStdDev("XmlPsAppMessageObserver: Looped messages/s", (double)numLooped / time);
    }
}

void XmlPsAppMessageObserver::handleMessage(cMessage* msg) {
    if (msg == gcTimer) {
        simtime_t now = OPP::simTime();
        std::map<NodeMessagePair, simtime_t>::iterator i, iPrev;
        i = receivedAt.begin();
        while (i != receivedAt.end()) {
            if (now - i->second >= cacheMaxAge) {
                iPrev = i;
                ++i;
                receivedAt.erase(iPrev);
            }
            else {
                ++i;
            }
        }
        scheduleAt(OPP::simTime() + gcInterval, gcTimer);
    }
}

/**
 * Adds one to node count for group.
 */
void XmlPsAppMessageObserver::joinedGroup(int moduleId, OverlayKey subBloom) {
    subList[moduleId].size += 1;
    joinedAt[NodeKeyPair(moduleId, subBloom)] = OPP::simTime();
}

/**
 * Subtracts one from node count for group.
 */
void XmlPsAppMessageObserver::leftGroup(int moduleId, OverlayKey groupId) {
    //std::map<OverlayKey, Subscription>::iterator iter = subList.find(groupId);
    //if (iter == subList.end()) {
        //EV << "Warning: XmlPsAppMessageObserver asked to remove node from nonexistent group " << groupId.toString();
    //}
    //else if (iter->second.size == 0) {
        //EV << "Warning: XmlPsAppMessageObserver asked to remove node from empty group " << groupId.toString();
    //}
    //else {
        //iter->second.size -= 1;
    //}
    //joinedAt.erase(NodeSubPair(moduleId, groupId));
}

/**
 * Counts n - 1 messages pending reception, where n is the
 * size of the group.
 */
void XmlPsAppMessageObserver::sentMessage(XmlPsAppTracedMessage* msg) {
    if (msg == NULL) {
        error("%s called with null message.", __PRETTY_FUNCTION__);
    }         
    int moduleId=(msg->getSenderId());
     pubList[moduleId].size += 1;
     pubList[moduleId].sent +=1;
    sendAt[NodeKeyPair(moduleId, msg->getGroupId())] = OPP::simTime();
//    pubList[msg->getSenderModuleId()].size += 1;//TODO: Create a publist in .h
    
}

/**
 * Counts one received message for group
 */
void XmlPsAppMessageObserver::receivedMessage(XmlPsAppTracedMessage* msg) {
  if (msg->getSenderId() != msg->getReceiverId()) {//TODO: test if this is useful. normally should consider self publication.

    std::map<int, Subscription>::iterator iSubList;
    iSubList = subList.find(msg->getReceiverId());
            NodeMessagePair nmp = NodeMessagePair(msg->getReceiverId(), msg->getMcastId());
            if (receivedAt.find(nmp) == receivedAt.end()) {
                iSubList->second.received += 1;
                if (msg->getFalse_positive()) {
                	iSubList->second.false_positive += 1;
				}


                receivedAt[nmp] = msg->getTimestamp();
            }
    }
    else {
        RECORD_STATS(++numLooped);
    }
}

/**
 * Notifies the observer that the node doesn't exist anymore.
 */
void XmlPsAppMessageObserver::nodeDead(int moduleId) {
    // For each group, if node has joined group, decrease group member count by one
    // and clear joined info.
    //for (std::map<OverlayKey, Subscription>::iterator ig = subList.begin(); ig != subList.end(); ++ig) {
        //NodeSubPair ngp = NodeSubPair(moduleId, ig->first);
        //if (joinedAt.find(ngp) != joinedAt.end()) {
            //ig->second.size--;
            //joinedAt.erase(ngp);
        //}
    //}
}

std::ostream& operator<< (std::ostream& os, XmlPsAppMessageObserver::Subscription const & sub) {
    return os << "Num(Nodes): " << sub.size << "; Messages Received: " << sub.received << ", Fase Possitive rate: "<<(double)sub.false_positive/(double)sub.received;
}
std::ostream& operator<< (std::ostream& os, XmlPsAppMessageObserver::Publication const & pub) {
    return os << "Num(Nodes): " << pub.size << "; Messages Sent: " << pub.sent;
}
//this has been defined in MessageObserver Module so do not overwrite it unless you changed the type of nodeGroupPair.
//std::ostream& operator<< (std::ostream& os, XmlPsAppMessageObserver::NodeSubPair const & ngp) {
//    cModule* module = OPP::cSimulation::getActiveSimulation()->getModule(ngp.first);
//    return os << "(" << (module != NULL ? module->getFullPath() : "Deleted node")
//        << ", " << ngp.second << ")";
//}

