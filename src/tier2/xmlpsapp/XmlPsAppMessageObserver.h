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
 * @file XmlPsAppMessageObserver.h
 * @author Dimitar Toshev
 */

#ifndef __XMLPSAPPMESSAGEOBSERVER_H__
#define __XMLPSAPPMESSAGEOBSERVER_H__

#include <stdint.h>
#include <time.h>
#include <ostream>
#include <omnetpp.h>
#include "OverlayKey.h"

class XmlPsAppTracedMessage;

class XmlPsAppMessageObserver : public cSimpleModule {

    public:

        XmlPsAppMessageObserver();
        ~XmlPsAppMessageObserver();

        void initialize();

        void finish();

        void handleMessage(cMessage* msg);

        /**
         * Adds one to node count for group.
         */
        void joinedGroup(int moduleId, OverlayKey groupId);

        /**
         * Subtracts one from node count for group.
         */
        void leftGroup(int moduleId, OverlayKey groupId);

        /**
         * Counts n - 1 messages pending reception, where n is the
         * size of the group to which the message is sent.
         */
        void sentMessage(XmlPsAppTracedMessage* msg);

        /**
         * Counts one received message for group.
         */
         void receivedMessage(XmlPsAppTracedMessage* msg);

        /**
         * Notifies the observer that the node doesn't exist anymore.
         */
        void nodeDead(int moduleId);

    private:

        /*
         * Tracks data related to a single group
         */
        struct Subscription {
            Subscription() : size(0), sent(0), received(0),false_positive(0) {}

            // Number of nodes in the group
            uint32_t size;
            // Number of messges sent total by certain nodes
            uint64_t sent;

            // Number of messages recieved total by certain nodes
            uint64_t received;

            //number of messages receibed that is false positive error.
            long false_positive;

        }; 
        //struct Publication {
            //Publication() : size(0), sent(0) {}
////add delay.
            //// Number of nodes in the group
            //uint32_t size;

            //// Number of messages that should have been received
            //uint64_t sent;

        //};
        struct MsgInfo {
        MsgInfo() : key(OverlayKey::UNSPECIFIED_KEY),subSize(0),subscriber() {}
        OverlayKey key;
        uint32_t subSize;
        std::set<int> subscriber;
        };

        simtime_t creationTime;

        typedef std::pair<int, OverlayKey> NodeKeyPair;

        //typedef std::pair<int, long> NodeMessagePair
        typedef std::pair<long, int>NodeMessagePair;

        // Info about a specific subscriptions
        std::map<int, Subscription> subList;
        // Info about a specific publications
        //std::map<int, Publication> pubList;

        // When a node subscribed with certain subscription.
        std::map<NodeKeyPair, simtime_t> joinedAt;
        std::map<NodeMessagePair, simtime_t> sendAt;

        // When a node received a given message
        std::map<NodeMessagePair, simtime_t> receivedAt;

        std::map<NodeMessagePair, MsgInfo> msgList;
        // Periodically clean up the above map. Set to 0 to disable(--by hill: maybe the following parameter, tried to set to 0, but the simulation crashed).
        cMessage* gcTimer;

        // How often to clean up
        double gcInterval;

        // How long data will be kept in the received cache
        double cacheMaxAge;

        // How many messages have been received by their sender (have looped)
        int numLooped;

        GlobalStatistics* globalStatistics;

        friend std::ostream& operator<< (std::ostream& os, XmlPsAppMessageObserver::Subscription const & mg);
        //friend std::ostream& operator<< (std::ostream& os, XmlPsAppMessageObserver::Publication const & mg);
        friend std::ostream& operator<< (std::ostream& os, XmlPsAppMessageObserver::MsgInfo const & msgInfo);
        friend std::ostream& operator<< (std::ostream& os, XmlPsAppMessageObserver::NodeKeyPair const & ngp);
        friend std::ostream& operator<< (std::ostream& os, XmlPsAppMessageObserver::NodeMessagePair const & nmp);
};

std::ostream& operator<< (std::ostream& os, XmlPsAppMessageObserver::Subscription const & sub);
//std::ostream& operator<< (std::ostream& os, XmlPsAppMessageObserver::Publication const & pub);
std::ostream& operator<< (std::ostream& os, XmlPsAppMessageObserver::MsgInfo const & msgInfo);
std::ostream& operator<< (std::ostream& os, XmlPsAppMessageObserver::NodeKeyPair const & ngp);
std::ostream& operator<< (std::ostream& os, XmlPsAppMessageObserver::NodeMessagePair const & nmp);

#endif
