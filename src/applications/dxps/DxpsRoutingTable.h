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
 * @file RoutingTable.h
 * @author Stephan Krause
 */


#ifndef __DXPSROUTINGTABLE_H_
#define __DXPSROUTINGTABLE_H_

#include <set>
#include "OverlayKey.h"
#include "NodeHandle.h"
#include "../../tier2/xmlpsapp/bloom_filter.h"
class DxpsRoutingTable;

#include "DxpsMessage_m.h"

/**
 * Capsulates the informations of a dxps multicast group
 */

class DxpsRoutingTable
{
    private:
        OverlayKey logicalNodeKey;
        NodeHandle rendezvousPoint;

//        std::map<OverlayKey, NfPair> parents;
        typedef std::set <bloom_filter> FilterList;//OverlayKey type is used to represent the bit-array.
        typedef std::pair<NodeHandle, FilterList> NfPair;
        typedef std::pair<OverlayKey, NfPair> Children;
        std::map<OverlayKey, NfPair> children;
        std::map<OverlayKey, NfPair> subChildren;//used for subscription, like children list
        bool subscription;
        bool amISource;
        bool isForwarder;
        FilterList ownFilterList;//TODO: put this in side sublist

        

//        DxpsTimer* parentTimer;
        DxpsTimer* heartbeatTimer;

    public:
        /**
         * Creates a new RoutingTable
         *
         * @param id The group ID of the new group
         */
        DxpsRoutingTable( OverlayKey id );
        ~DxpsRoutingTable( );

        /**
         * Adds a new child to the multicast tree
         *
         * @param node The nodeHandle of the child
         * @return An iterator to the inserted child and a boolean value (true = new child, false = child was already present)
         */
//        std::pair<std::map<OverlayKey, NfPair>::iterator, bool> addParent( const Children& node );
        std::pair<std::map<OverlayKey, NfPair>::iterator, bool> addChild( const Children& node );
        void modChild( const Children& node );
        std::pair<std::map<OverlayKey, NfPair>::iterator, bool> addSubChild( const Children& node );
        void modSubChild( const Children& node );
        std::pair<std::set<bloom_filter>::iterator,bool> insertToOwnFilterList(const bloom_filter& ft);

        FilterList getOwnFilterList();
        /**
         * Removes a child from the multicast tree
         *
         * @param node The nodeHandle of the child
         */
//        void removeParent( const Children& node );
        void removeChild( const Children& node );

        /**
         * Returns an iterator to the begin of the children list
         *
         * @return the iterator
         */
//        std::map<OverlayKey, NfPair>::iterator getParentsBegin();
        std::map<OverlayKey, NfPair>::iterator getChildrenBegin();
        std::map<OverlayKey, NfPair>::iterator getSubChildrenBegin();

        /**
         * Returns an iterator to the end of the children list
         *
         * @return the iterator
         */
//        std::map<OverlayKey, NfPair>::iterator getParentsEnd();
        std::map<OverlayKey, NfPair>::iterator getChildrenEnd();
        std::map<OverlayKey, NfPair>::iterator getSubChildrenEnd();

        /**
         * Get the number of children
         *
         * @return The number of children
         */
//        int numParents() const { return parents.size(); }
        int numChildren() const { return children.size(); }

        /**
         * Return whether the node is forwarder for a group.
         *
         * @return True if there are any children, false else.
         */
        bool getIsForwarder() const {return isForwarder;}
        void setForwarder( bool forwarder ) { isForwarder = forwarder; }

        /**
         * Returns the amISource status
         *
         * This status indicates if the node is a source of the multicastgroup
         * FIXME: currently the flag is only be set to true if the node is not
         * also a member (i.e. subscribe)  of the group
         *
         * @return True if the node is sending in multicast messages to the group
         */
        bool getAmISource() const { return amISource; }

        /**
         * Set the amISource status
         *
         * This status indicates if the node is a source of the multicastgroup
         * FIXME: currently the flag is only be set to true if the node is not
         * also a member (i.e. subscribe)  of the group
         *
         * @param source True if the node is sending in multicast messages to the group
         */
        void setAmISource( bool source ) { amISource = source; }

        /**
         * Returns whether the local node is subscribe of the group
         *
         * @return True if the local node is interested in multicast messages for the group, false else
         */
        bool getSubscription() const { return subscription; }

        /**
         * Set the subscription status
         *
         * @param subscribe True if the node is interested in multicast messages for the group, false else
         */
        void setSubscription( bool subscribe ) { subscription = subscribe; }

        /**
         * Return the parent in the multicast tree
         *
         * @return The parent. thisNode if the node is root of the tree
         */

        /**
         * Sets a new parent for the multicast tree
         *
         * @param _parent The new Parent. Set to thisNode if node should be root of the tree
         */

        /**
         * Returns the rendevouzPoint (root) of the multicast tree for the group
         *
         * @return The root of the multicast tree if known. UNSPECIFIED_NODE else
         */
        NodeHandle getRendezvousPoint() const { return rendezvousPoint; }

        /**
         * Sets the rendevouzPoint (root) of the multicast tree for the group
         *
         * @param _rendezvousPoint The root of the tree
         */
        void setRendezvousPoint( const NodeHandle& _rendezvousPoint ) { rendezvousPoint = _rendezvousPoint; }

        /**
         * Returns the logicalNodeKey of the node
         *
         * @return The group ID
         */
        OverlayKey getLogicalNodeKey() const { return logicalNodeKey; }

        /**
         * Returns the parent timer.
         *
         * The parent timer is supposed to expire if the parent
         * fails to send heartbeat messages.
         *
         * @return The parentTimer
         */
//        DxpsTimer* getParentTimer() { return parentTimer; }

        /**
         * Sets the parent timer.
         *
         * The parent timer is supposed to expire if the parent
         * fails to send heartbeat messages.
         *
         * @param t The parentTimer
         */
//        void setParentTimer(DxpsTimer* t ) { parentTimer = t; }

        /**
         * Returns the heartbeat timer.
         *
         * If the timer expires, the node is supposed to send
         * heartbeat messages to all children.
         *
         * @return The heratbetTimer
         */
        DxpsTimer* getHeartbeatTimer() { return heartbeatTimer; }

        /**
         * Sets the heartbeat timer.
         *
         * If the timer expires, the node is supposed to send
         * heartbeat messages to all children.
         *
         * @param t The heartbeatTimer
         */
        void setHeartbeatTimer(DxpsTimer* t ) { heartbeatTimer = t; }

        /**
         * Checks whether the group has a certain logicalNodeKey
         *
         * @param id The logicalNodeKey to check
         * @return True if id == logicalNodeKey, false else
         */
        bool operator== (const OverlayKey& id) const { return id == logicalNodeKey; };

        /**
         * Checks whether two groups have the same ID
         *
         * @param a The group to compare
         * @return True if the groups have the same ID, false else.
         */
        bool operator== (const DxpsRoutingTable& a) const { return a.getLogicalNodeKey() == logicalNodeKey; };

        /**
         * Checks whether the group has a smaller ID than the given key
         *
         * @param id The key to compare
         * @return True if the group id is smaller than the key, false else.
         */
        bool operator< (const OverlayKey& id) const { return id < logicalNodeKey; };

        /**
         * Checks whether the group has a smaller ID than another group
         *
         * @param a the group to compare
         * @return True if the (local) group id is smaller than the a's logicalNodeKey, false else.
         *
         */
        bool operator< (const DxpsRoutingTable& a) const { return logicalNodeKey < a.getLogicalNodeKey(); };
};

#endif
