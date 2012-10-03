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
 * @file DxpsRoutingTable.cc
 * @author Stephan Krause
 */



#include "DxpsRoutingTable.h"

typedef std::set <OverlayKey> FilterList;//OverlayKey type is used to represent the bit-array.
        typedef std::pair<NodeHandle, FilterList> NfPair;
        typedef std::pair<OverlayKey, NfPair> Children;
DxpsRoutingTable::DxpsRoutingTable( OverlayKey id ) : logicalNodeKey(id)
{
//    parent = NodeHandle::UNSPECIFIED_NODE;
    rendezvousPoint = NodeHandle::UNSPECIFIED_NODE;
    subscription = false;
    amISource = false;
    isForwarder = false;
//    parentTimer = NULL;
    heartbeatTimer = NULL;
}

DxpsRoutingTable::~DxpsRoutingTable( )
{
    children.clear();
}

//bool DxpsRoutingTable::isForwarder() const
//{
//    return !children.empty();
//}

std::pair<std::map<OverlayKey, NfPair>::iterator, bool> DxpsRoutingTable::addChild( const Children& nodepair )
{
    return children.insert(nodepair);
}
//modify the childern list if the request indicates the insertion of an known child.
//only update the filter list/routing table.
std::pair<std::map<OverlayKey, NfPair>::iterator, bool> DxpsRoutingTable::modChild( const Children& nodepair )
{
   std::map<OverlayKey, NfPair>::iterator it;
   it=children.find(nodepair.first);
   it->second.second.insert(*(nodepair.second.second.begin()));

    return children.insert(nodepair);
}

void DxpsRoutingTable::removeChild( const Children& nodepair )
{
   // children.erase(nodepair);
}


std::map<OverlayKey, NfPair>::iterator DxpsRoutingTable::getChildrenBegin()
{
    return children.begin();
}

std::map<OverlayKey, NfPair>::iterator DxpsRoutingTable::getChildrenEnd()
{
    return children.end();
}

