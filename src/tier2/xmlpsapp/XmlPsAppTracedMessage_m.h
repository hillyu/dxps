//
// Generated file, do not edit! Created by opp_msgc 4.1 from tier2/xmlpsapp/XmlPsAppTracedMessage.msg.
//

#ifndef _XMLPSAPPTRACEDMESSAGE_M_H_
#define _XMLPSAPPTRACEDMESSAGE_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0401
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#include "ALMTestTracedMessage_m.h"
// }}



/**
 * Class generated from <tt>tier2/xmlpsapp/XmlPsAppTracedMessage.msg</tt> by opp_msgc.
 * <pre>
 * packet XmlPsAppTracedMessage extends ALMTestTracedMessage {
 *     string xmlFileName;
 * }
 * </pre>
 */
class XmlPsAppTracedMessage : public ::ALMTestTracedMessage
{
  protected:
    opp_string xmlFileName_var;

    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const XmlPsAppTracedMessage&);

  public:
    XmlPsAppTracedMessage(const char *name=NULL, int kind=0);
    XmlPsAppTracedMessage(const XmlPsAppTracedMessage& other);
    virtual ~XmlPsAppTracedMessage();
    XmlPsAppTracedMessage& operator=(const XmlPsAppTracedMessage& other);
    virtual XmlPsAppTracedMessage *dup() const {return new XmlPsAppTracedMessage(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual const char * getXmlFileName() const;
    virtual void setXmlFileName(const char * xmlFileName_var);
};

inline void doPacking(cCommBuffer *b, XmlPsAppTracedMessage& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, XmlPsAppTracedMessage& obj) {obj.parsimUnpack(b);}


#endif // _XMLPSAPPTRACEDMESSAGE_M_H_
