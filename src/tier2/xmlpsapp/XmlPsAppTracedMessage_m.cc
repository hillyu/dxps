//
// Generated file, do not edit! Created by opp_msgc 4.1 from tier2/xmlpsapp/XmlPsAppTracedMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "XmlPsAppTracedMessage_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




Register_Class(XmlPsAppTracedMessage);

XmlPsAppTracedMessage::XmlPsAppTracedMessage(const char *name, int kind) : ALMTestTracedMessage(name,kind)
{
    this->xmlFileName_var = 0;
    this->false_positive_var = 0;
}

XmlPsAppTracedMessage::XmlPsAppTracedMessage(const XmlPsAppTracedMessage& other) : ALMTestTracedMessage()
{
    setName(other.getName());
    operator=(other);
}

XmlPsAppTracedMessage::~XmlPsAppTracedMessage()
{
}

XmlPsAppTracedMessage& XmlPsAppTracedMessage::operator=(const XmlPsAppTracedMessage& other)
{
    if (this==&other) return *this;
    ALMTestTracedMessage::operator=(other);
    this->xmlFileName_var = other.xmlFileName_var;
    this->false_positive_var = other.false_positive_var;
    return *this;
}

void XmlPsAppTracedMessage::parsimPack(cCommBuffer *b)
{
    ALMTestTracedMessage::parsimPack(b);
    doPacking(b,this->xmlFileName_var);
    doPacking(b,this->false_positive_var);
}

void XmlPsAppTracedMessage::parsimUnpack(cCommBuffer *b)
{
    ALMTestTracedMessage::parsimUnpack(b);
    doUnpacking(b,this->xmlFileName_var);
    doUnpacking(b,this->false_positive_var);
}

const char * XmlPsAppTracedMessage::getXmlFileName() const
{
    return xmlFileName_var.c_str();
}

void XmlPsAppTracedMessage::setXmlFileName(const char * xmlFileName_var)
{
    this->xmlFileName_var = xmlFileName_var;
}

bool XmlPsAppTracedMessage::getFalse_positive() const
{
    return false_positive_var;
}

void XmlPsAppTracedMessage::setFalse_positive(bool false_positive_var)
{
    this->false_positive_var = false_positive_var;
}

class XmlPsAppTracedMessageDescriptor : public cClassDescriptor
{
  public:
    XmlPsAppTracedMessageDescriptor();
    virtual ~XmlPsAppTracedMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(XmlPsAppTracedMessageDescriptor);

XmlPsAppTracedMessageDescriptor::XmlPsAppTracedMessageDescriptor() : cClassDescriptor("XmlPsAppTracedMessage", "ALMTestTracedMessage")
{
}

XmlPsAppTracedMessageDescriptor::~XmlPsAppTracedMessageDescriptor()
{
}

bool XmlPsAppTracedMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<XmlPsAppTracedMessage *>(obj)!=NULL;
}

const char *XmlPsAppTracedMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int XmlPsAppTracedMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int XmlPsAppTracedMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *XmlPsAppTracedMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "xmlFileName",
        "false_positive",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int XmlPsAppTracedMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='x' && strcmp(fieldName, "xmlFileName")==0) return base+0;
    if (fieldName[0]=='f' && strcmp(fieldName, "false_positive")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *XmlPsAppTracedMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "bool",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *XmlPsAppTracedMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int XmlPsAppTracedMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    XmlPsAppTracedMessage *pp = (XmlPsAppTracedMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string XmlPsAppTracedMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    XmlPsAppTracedMessage *pp = (XmlPsAppTracedMessage *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getXmlFileName());
        case 1: return bool2string(pp->getFalse_positive());
        default: return "";
    }
}

bool XmlPsAppTracedMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    XmlPsAppTracedMessage *pp = (XmlPsAppTracedMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setXmlFileName((value)); return true;
        case 1: pp->setFalse_positive(string2bool(value)); return true;
        default: return false;
    }
}

const char *XmlPsAppTracedMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
    };
    return (field>=0 && field<2) ? fieldStructNames[field] : NULL;
}

void *XmlPsAppTracedMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    XmlPsAppTracedMessage *pp = (XmlPsAppTracedMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


