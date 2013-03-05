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

typedef std::set <bloom_filter> FilterList;//OverlayKey type is used to represent the bit-array.
        typedef std::pair<NodeHandle, FilterList> NfPair;
        typedef std::pair<OverlayKey, NfPair> Children;
DxpsRoutingTable::DxpsRoutingTable(){
    logicalNodeKey = OverlayKey::UNSPECIFIED_KEY;
    rendezvousPoint = NodeHandle::UNSPECIFIED_NODE;
    subscription = false;
    amISource = false;
    isResponsible =false;
    isForwarder = false;
//    parentTimer = NULL;
}
DxpsRoutingTable::DxpsRoutingTable( OverlayKey id ) : logicalNodeKey(id)
{
//    parent = NodeHandle::UNSPECIFIED_NODE;
    rendezvousPoint = NodeHandle::UNSPECIFIED_NODE;
    subscription = false;
    amISource = false;
    isResponsible =false;
    isForwarder = false;
//    parentTimer = NULL;
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
std::pair<std::map<OverlayKey, NfPair>::iterator, bool> DxpsRoutingTable::addSubChild( const Children& nodepair )
{
    return subChildren.insert(nodepair);
}
//modify the childern list if the request indicates the insertion of an known child.
//only update the filter list/routing table.
void DxpsRoutingTable::modChild( const Children& nodepair )
{
   std::map<OverlayKey, NfPair>::iterator it;
   it=children.find(nodepair.first);
   it->second.second.insert(*(nodepair.second.second.begin()));

    return;
}
void DxpsRoutingTable::modSubChild( const Children& nodepair )
{
   std::map<OverlayKey, NfPair>::iterator it;
   it=subChildren.find(nodepair.first);
   it->second.second.insert(*(nodepair.second.second.begin()));

    return;
}

std::pair<std::set<bloom_filter>::iterator,bool> DxpsRoutingTable::insertToOwnFilterList(const bloom_filter& ft){
 return ownFilterList.insert(ft);
}
FilterList DxpsRoutingTable::getOwnFilterList(){
  return ownFilterList;
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
std::map<OverlayKey, NfPair>::iterator DxpsRoutingTable::getSubChildrenBegin()
{
    return subChildren.begin();
}

std::map<OverlayKey, NfPair>::iterator DxpsRoutingTable::getSubChildrenEnd()
{
    return subChildren.end();
}
 

