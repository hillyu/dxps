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

//
// @file DxpsMessage.msg
// @author Stephan Krause
//

cplusplus {{
#include <CommonMessages_m.h>

class DxpsTimer;

#include "DxpsRoutingTable.h"

// Length definition
static const int DXPS_WRONGROOT_L = 8;
static const int DXPS_EMPTYFLAG_L = 8;
static const int DXPS_FILTER_L = 8;//TODO: should be bloom filter lenght

// HACK: logicalNodeKey field nor counted in length calculation (see message definition)
#define DXPS_JOINCALL_L(msg) (2*KEY_L+BASECALL_L(msg))
#define DXPS_JOINRESPONSE_L(msg) (BASECALL_L(msg))
#define DXPS_PUBLISHCALL_L(msg) (BASECALL_L(msg))
#define DXPS_PUBLISHRESPONSE_L(msg) (BASECALL_L(msg) + DXPS_WRONGROOT_L)

#define DXPS_SUBSCRIPTIONREFRESH_L(msg) (NODEHANDLE_L + KEY_L)
#define DXPS_LEAVE_L(msg) (NODEHANDLE_L + KEY_L)
#define DXPS_DATA_L(msg) (KEY_L + DXPS_EMPTYFLAG_L)
#define DXPS_SUBSCRIPTIONMESSAGE_L(msg) (KEY_L+DXPS_FILTER_L)
}}



class noncobject DxpsGroupPointer;

class noncobject ChildPointer;

class noncobject NodeHandle;

class noncobject OverlayKey;

class BaseCallMessage;


class BaseResponseMessage;



enum DxpsTimerType 
{

    DXPS_HEARTBEAT = 0; // Send heartbeat to all children of a group
    DXPS_SUBSCRIPTION_REFRESH = 1; // refresh subscriptions for all groups
    DXPS_PARENT_TIMEOUT = 2; // Parent failed to send heartbeat
    DXPS_CHILD_TIMEOUT = 3; // Child faild to refresh subscription
}

packet DxpsJoinCall extends BaseCallMessage
{
        OverlayKey srcLogicalNodeKey;
        OverlayKey dstLogicalNodeKey;// HACK. The key is already included in BaseRouteMessage,
                            //   but it gets lost in handleRpc
}

packet DxpsJoinResponse extends BaseResponseMessage
{
        OverlayKey logicalNodeKey; // HACK. The key is already included in BaseRouteMessage,
                            //   but it gets lost in handleRpc
}

packet DxpsPublishCall extends BaseCallMessage
{
        OverlayKey logicalNodeKey; // HACK. The key is already included in BaseRouteMessage,
                            //   but it gets lost in handleRpc
}

packet DxpsPublishResponse extends BaseResponseMessage
{
        OverlayKey logicalNodeKey; // HACK. The key is already included in BaseRouteMessage,
                            //   but it gets lost in handleRpc
        bool wrongRoot = false;
}
packet DxpsSubscribeCall extends BaseCallMessage
{
        OverlayKey logicalNodeKey; // HACK. The key is already included in BaseRouteMessage,
                            //   but it gets lost in handleRpc
}

packet DxpsSubscribeResponse extends BaseResponseMessage
{
        OverlayKey logicalNodeKey; // HACK. The key is already included in BaseRouteMessage,
                            //   but it gets lost in handleRpc
        bool wrongRoot = false;
}
packet DxpsSubscriptionRefreshMessage
{
        NodeHandle src;
        OverlayKey logicalNodeKey;
}

packet DxpsLeaveMessage
{
        NodeHandle src;
        OverlayKey logicalNodeKey;
}

message DxpsTimer
{
        int timerType enum(DxpsTimerType);
        NodeHandle child;
        OverlayKey logicalNodeKey;
}

packet DxpsDataMessage
{
        OverlayKey logicalNodeKey;
        long dxpsMsgId =0;
        bool empty = false;
}
packet DxpsSubscriptionMessage
{
        OverlayKey logicalNodeKey;
        long dxpsMsgId =0;
        bool empty = false;
}
