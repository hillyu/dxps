//
// Generated file, do not edit! Created by opp_msgc 4.1 from applications/dxps/DxpsMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "DxpsMessage_m.h"

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




EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("DxpsTimerType");
    if (!e) enums.getInstance()->add(e = new cEnum("DxpsTimerType"));
    e->insert(DXPS_HEARTBEAT, "DXPS_HEARTBEAT");
    e->insert(DXPS_SUBSCRIPTION_REFRESH, "DXPS_SUBSCRIPTION_REFRESH");
    e->insert(DXPS_PARENT_TIMEOUT, "DXPS_PARENT_TIMEOUT");
    e->insert(DXPS_CHILD_TIMEOUT, "DXPS_CHILD_TIMEOUT");
);

Register_Class(DxpsJoinCall);

DxpsJoinCall::DxpsJoinCall(const char *name, int kind) : BaseCallMessage(name,kind)
{
}

DxpsJoinCall::DxpsJoinCall(const DxpsJoinCall& other) : BaseCallMessage()
{
    setName(other.getName());
    operator=(other);
}

DxpsJoinCall::~DxpsJoinCall()
{
}

DxpsJoinCall& DxpsJoinCall::operator=(const DxpsJoinCall& other)
{
    if (this==&other) return *this;
    BaseCallMessage::operator=(other);
    this->srcLogicalNodeKey_var = other.srcLogicalNodeKey_var;
    this->dstLogicalNodeKey_var = other.dstLogicalNodeKey_var;
    return *this;
}

void DxpsJoinCall::parsimPack(cCommBuffer *b)
{
    BaseCallMessage::parsimPack(b);
    doPacking(b,this->srcLogicalNodeKey_var);
    doPacking(b,this->dstLogicalNodeKey_var);
}

void DxpsJoinCall::parsimUnpack(cCommBuffer *b)
{
    BaseCallMessage::parsimUnpack(b);
    doUnpacking(b,this->srcLogicalNodeKey_var);
    doUnpacking(b,this->dstLogicalNodeKey_var);
}

OverlayKey& DxpsJoinCall::getSrcLogicalNodeKey()
{
    return srcLogicalNodeKey_var;
}

void DxpsJoinCall::setSrcLogicalNodeKey(const OverlayKey& srcLogicalNodeKey_var)
{
    this->srcLogicalNodeKey_var = srcLogicalNodeKey_var;
}

OverlayKey& DxpsJoinCall::getDstLogicalNodeKey()
{
    return dstLogicalNodeKey_var;
}

void DxpsJoinCall::setDstLogicalNodeKey(const OverlayKey& dstLogicalNodeKey_var)
{
    this->dstLogicalNodeKey_var = dstLogicalNodeKey_var;
}

class DxpsJoinCallDescriptor : public cClassDescriptor
{
  public:
    DxpsJoinCallDescriptor();
    virtual ~DxpsJoinCallDescriptor();

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

Register_ClassDescriptor(DxpsJoinCallDescriptor);

DxpsJoinCallDescriptor::DxpsJoinCallDescriptor() : cClassDescriptor("DxpsJoinCall", "BaseCallMessage")
{
}

DxpsJoinCallDescriptor::~DxpsJoinCallDescriptor()
{
}

bool DxpsJoinCallDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DxpsJoinCall *>(obj)!=NULL;
}

const char *DxpsJoinCallDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DxpsJoinCallDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int DxpsJoinCallDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *DxpsJoinCallDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "srcLogicalNodeKey",
        "dstLogicalNodeKey",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int DxpsJoinCallDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcLogicalNodeKey")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dstLogicalNodeKey")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DxpsJoinCallDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "OverlayKey",
        "OverlayKey",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *DxpsJoinCallDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int DxpsJoinCallDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DxpsJoinCall *pp = (DxpsJoinCall *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DxpsJoinCallDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsJoinCall *pp = (DxpsJoinCall *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getSrcLogicalNodeKey(); return out.str();}
        case 1: {std::stringstream out; out << pp->getDstLogicalNodeKey(); return out.str();}
        default: return "";
    }
}

bool DxpsJoinCallDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DxpsJoinCall *pp = (DxpsJoinCall *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *DxpsJoinCallDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "OverlayKey",
        "OverlayKey",
    };
    return (field>=0 && field<2) ? fieldStructNames[field] : NULL;
}

void *DxpsJoinCallDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsJoinCall *pp = (DxpsJoinCall *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getSrcLogicalNodeKey()); break;
        case 1: return (void *)(&pp->getDstLogicalNodeKey()); break;
        default: return NULL;
    }
}

Register_Class(DxpsSubCall);

DxpsSubCall::DxpsSubCall(const char *name, int kind) : BaseCallMessage(name,kind)
{
}

DxpsSubCall::DxpsSubCall(const DxpsSubCall& other) : BaseCallMessage()
{
    setName(other.getName());
    operator=(other);
}

DxpsSubCall::~DxpsSubCall()
{
}

DxpsSubCall& DxpsSubCall::operator=(const DxpsSubCall& other)
{
    if (this==&other) return *this;
    BaseCallMessage::operator=(other);
    this->srcLogicalNodeKey_var = other.srcLogicalNodeKey_var;
    this->dstLogicalNodeKey_var = other.dstLogicalNodeKey_var;
    return *this;
}

void DxpsSubCall::parsimPack(cCommBuffer *b)
{
    BaseCallMessage::parsimPack(b);
    doPacking(b,this->srcLogicalNodeKey_var);
    doPacking(b,this->dstLogicalNodeKey_var);
}

void DxpsSubCall::parsimUnpack(cCommBuffer *b)
{
    BaseCallMessage::parsimUnpack(b);
    doUnpacking(b,this->srcLogicalNodeKey_var);
    doUnpacking(b,this->dstLogicalNodeKey_var);
}

OverlayKey& DxpsSubCall::getSrcLogicalNodeKey()
{
    return srcLogicalNodeKey_var;
}

void DxpsSubCall::setSrcLogicalNodeKey(const OverlayKey& srcLogicalNodeKey_var)
{
    this->srcLogicalNodeKey_var = srcLogicalNodeKey_var;
}

OverlayKey& DxpsSubCall::getDstLogicalNodeKey()
{
    return dstLogicalNodeKey_var;
}

void DxpsSubCall::setDstLogicalNodeKey(const OverlayKey& dstLogicalNodeKey_var)
{
    this->dstLogicalNodeKey_var = dstLogicalNodeKey_var;
}

class DxpsSubCallDescriptor : public cClassDescriptor
{
  public:
    DxpsSubCallDescriptor();
    virtual ~DxpsSubCallDescriptor();

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

Register_ClassDescriptor(DxpsSubCallDescriptor);

DxpsSubCallDescriptor::DxpsSubCallDescriptor() : cClassDescriptor("DxpsSubCall", "BaseCallMessage")
{
}

DxpsSubCallDescriptor::~DxpsSubCallDescriptor()
{
}

bool DxpsSubCallDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DxpsSubCall *>(obj)!=NULL;
}

const char *DxpsSubCallDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DxpsSubCallDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int DxpsSubCallDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *DxpsSubCallDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "srcLogicalNodeKey",
        "dstLogicalNodeKey",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int DxpsSubCallDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcLogicalNodeKey")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dstLogicalNodeKey")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DxpsSubCallDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "OverlayKey",
        "OverlayKey",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *DxpsSubCallDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int DxpsSubCallDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubCall *pp = (DxpsSubCall *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DxpsSubCallDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubCall *pp = (DxpsSubCall *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getSrcLogicalNodeKey(); return out.str();}
        case 1: {std::stringstream out; out << pp->getDstLogicalNodeKey(); return out.str();}
        default: return "";
    }
}

bool DxpsSubCallDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubCall *pp = (DxpsSubCall *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *DxpsSubCallDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "OverlayKey",
        "OverlayKey",
    };
    return (field>=0 && field<2) ? fieldStructNames[field] : NULL;
}

void *DxpsSubCallDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubCall *pp = (DxpsSubCall *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getSrcLogicalNodeKey()); break;
        case 1: return (void *)(&pp->getDstLogicalNodeKey()); break;
        default: return NULL;
    }
}

Register_Class(DxpsJoinResponse);

DxpsJoinResponse::DxpsJoinResponse(const char *name, int kind) : BaseResponseMessage(name,kind)
{
}

DxpsJoinResponse::DxpsJoinResponse(const DxpsJoinResponse& other) : BaseResponseMessage()
{
    setName(other.getName());
    operator=(other);
}

DxpsJoinResponse::~DxpsJoinResponse()
{
}

DxpsJoinResponse& DxpsJoinResponse::operator=(const DxpsJoinResponse& other)
{
    if (this==&other) return *this;
    BaseResponseMessage::operator=(other);
    this->logicalNodeKey_var = other.logicalNodeKey_var;
    return *this;
}

void DxpsJoinResponse::parsimPack(cCommBuffer *b)
{
    BaseResponseMessage::parsimPack(b);
    doPacking(b,this->logicalNodeKey_var);
}

void DxpsJoinResponse::parsimUnpack(cCommBuffer *b)
{
    BaseResponseMessage::parsimUnpack(b);
    doUnpacking(b,this->logicalNodeKey_var);
}

OverlayKey& DxpsJoinResponse::getLogicalNodeKey()
{
    return logicalNodeKey_var;
}

void DxpsJoinResponse::setLogicalNodeKey(const OverlayKey& logicalNodeKey_var)
{
    this->logicalNodeKey_var = logicalNodeKey_var;
}

class DxpsJoinResponseDescriptor : public cClassDescriptor
{
  public:
    DxpsJoinResponseDescriptor();
    virtual ~DxpsJoinResponseDescriptor();

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

Register_ClassDescriptor(DxpsJoinResponseDescriptor);

DxpsJoinResponseDescriptor::DxpsJoinResponseDescriptor() : cClassDescriptor("DxpsJoinResponse", "BaseResponseMessage")
{
}

DxpsJoinResponseDescriptor::~DxpsJoinResponseDescriptor()
{
}

bool DxpsJoinResponseDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DxpsJoinResponse *>(obj)!=NULL;
}

const char *DxpsJoinResponseDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DxpsJoinResponseDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int DxpsJoinResponseDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *DxpsJoinResponseDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "logicalNodeKey",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int DxpsJoinResponseDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='l' && strcmp(fieldName, "logicalNodeKey")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DxpsJoinResponseDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "OverlayKey",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *DxpsJoinResponseDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int DxpsJoinResponseDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DxpsJoinResponse *pp = (DxpsJoinResponse *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DxpsJoinResponseDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsJoinResponse *pp = (DxpsJoinResponse *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getLogicalNodeKey(); return out.str();}
        default: return "";
    }
}

bool DxpsJoinResponseDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DxpsJoinResponse *pp = (DxpsJoinResponse *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *DxpsJoinResponseDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "OverlayKey",
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *DxpsJoinResponseDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsJoinResponse *pp = (DxpsJoinResponse *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getLogicalNodeKey()); break;
        default: return NULL;
    }
}

Register_Class(DxpsSubResponse);

DxpsSubResponse::DxpsSubResponse(const char *name, int kind) : BaseResponseMessage(name,kind)
{
}

DxpsSubResponse::DxpsSubResponse(const DxpsSubResponse& other) : BaseResponseMessage()
{
    setName(other.getName());
    operator=(other);
}

DxpsSubResponse::~DxpsSubResponse()
{
}

DxpsSubResponse& DxpsSubResponse::operator=(const DxpsSubResponse& other)
{
    if (this==&other) return *this;
    BaseResponseMessage::operator=(other);
    this->logicalNodeKey_var = other.logicalNodeKey_var;
    return *this;
}

void DxpsSubResponse::parsimPack(cCommBuffer *b)
{
    BaseResponseMessage::parsimPack(b);
    doPacking(b,this->logicalNodeKey_var);
}

void DxpsSubResponse::parsimUnpack(cCommBuffer *b)
{
    BaseResponseMessage::parsimUnpack(b);
    doUnpacking(b,this->logicalNodeKey_var);
}

OverlayKey& DxpsSubResponse::getLogicalNodeKey()
{
    return logicalNodeKey_var;
}

void DxpsSubResponse::setLogicalNodeKey(const OverlayKey& logicalNodeKey_var)
{
    this->logicalNodeKey_var = logicalNodeKey_var;
}

class DxpsSubResponseDescriptor : public cClassDescriptor
{
  public:
    DxpsSubResponseDescriptor();
    virtual ~DxpsSubResponseDescriptor();

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

Register_ClassDescriptor(DxpsSubResponseDescriptor);

DxpsSubResponseDescriptor::DxpsSubResponseDescriptor() : cClassDescriptor("DxpsSubResponse", "BaseResponseMessage")
{
}

DxpsSubResponseDescriptor::~DxpsSubResponseDescriptor()
{
}

bool DxpsSubResponseDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DxpsSubResponse *>(obj)!=NULL;
}

const char *DxpsSubResponseDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DxpsSubResponseDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int DxpsSubResponseDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *DxpsSubResponseDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "logicalNodeKey",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int DxpsSubResponseDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='l' && strcmp(fieldName, "logicalNodeKey")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DxpsSubResponseDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "OverlayKey",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *DxpsSubResponseDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int DxpsSubResponseDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubResponse *pp = (DxpsSubResponse *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DxpsSubResponseDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubResponse *pp = (DxpsSubResponse *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getLogicalNodeKey(); return out.str();}
        default: return "";
    }
}

bool DxpsSubResponseDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubResponse *pp = (DxpsSubResponse *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *DxpsSubResponseDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "OverlayKey",
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *DxpsSubResponseDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubResponse *pp = (DxpsSubResponse *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getLogicalNodeKey()); break;
        default: return NULL;
    }
}

Register_Class(DxpsPublishCall);

DxpsPublishCall::DxpsPublishCall(const char *name, int kind) : BaseCallMessage(name,kind)
{
}

DxpsPublishCall::DxpsPublishCall(const DxpsPublishCall& other) : BaseCallMessage()
{
    setName(other.getName());
    operator=(other);
}

DxpsPublishCall::~DxpsPublishCall()
{
}

DxpsPublishCall& DxpsPublishCall::operator=(const DxpsPublishCall& other)
{
    if (this==&other) return *this;
    BaseCallMessage::operator=(other);
    this->logicalNodeKey_var = other.logicalNodeKey_var;
    return *this;
}

void DxpsPublishCall::parsimPack(cCommBuffer *b)
{
    BaseCallMessage::parsimPack(b);
    doPacking(b,this->logicalNodeKey_var);
}

void DxpsPublishCall::parsimUnpack(cCommBuffer *b)
{
    BaseCallMessage::parsimUnpack(b);
    doUnpacking(b,this->logicalNodeKey_var);
}

OverlayKey& DxpsPublishCall::getLogicalNodeKey()
{
    return logicalNodeKey_var;
}

void DxpsPublishCall::setLogicalNodeKey(const OverlayKey& logicalNodeKey_var)
{
    this->logicalNodeKey_var = logicalNodeKey_var;
}

class DxpsPublishCallDescriptor : public cClassDescriptor
{
  public:
    DxpsPublishCallDescriptor();
    virtual ~DxpsPublishCallDescriptor();

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

Register_ClassDescriptor(DxpsPublishCallDescriptor);

DxpsPublishCallDescriptor::DxpsPublishCallDescriptor() : cClassDescriptor("DxpsPublishCall", "BaseCallMessage")
{
}

DxpsPublishCallDescriptor::~DxpsPublishCallDescriptor()
{
}

bool DxpsPublishCallDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DxpsPublishCall *>(obj)!=NULL;
}

const char *DxpsPublishCallDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DxpsPublishCallDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int DxpsPublishCallDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *DxpsPublishCallDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "logicalNodeKey",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int DxpsPublishCallDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='l' && strcmp(fieldName, "logicalNodeKey")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DxpsPublishCallDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "OverlayKey",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *DxpsPublishCallDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int DxpsPublishCallDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DxpsPublishCall *pp = (DxpsPublishCall *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DxpsPublishCallDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsPublishCall *pp = (DxpsPublishCall *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getLogicalNodeKey(); return out.str();}
        default: return "";
    }
}

bool DxpsPublishCallDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DxpsPublishCall *pp = (DxpsPublishCall *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *DxpsPublishCallDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "OverlayKey",
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *DxpsPublishCallDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsPublishCall *pp = (DxpsPublishCall *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getLogicalNodeKey()); break;
        default: return NULL;
    }
}

Register_Class(DxpsPublishResponse);

DxpsPublishResponse::DxpsPublishResponse(const char *name, int kind) : BaseResponseMessage(name,kind)
{
    this->wrongRoot_var = false;
}

DxpsPublishResponse::DxpsPublishResponse(const DxpsPublishResponse& other) : BaseResponseMessage()
{
    setName(other.getName());
    operator=(other);
}

DxpsPublishResponse::~DxpsPublishResponse()
{
}

DxpsPublishResponse& DxpsPublishResponse::operator=(const DxpsPublishResponse& other)
{
    if (this==&other) return *this;
    BaseResponseMessage::operator=(other);
    this->logicalNodeKey_var = other.logicalNodeKey_var;
    this->wrongRoot_var = other.wrongRoot_var;
    return *this;
}

void DxpsPublishResponse::parsimPack(cCommBuffer *b)
{
    BaseResponseMessage::parsimPack(b);
    doPacking(b,this->logicalNodeKey_var);
    doPacking(b,this->wrongRoot_var);
}

void DxpsPublishResponse::parsimUnpack(cCommBuffer *b)
{
    BaseResponseMessage::parsimUnpack(b);
    doUnpacking(b,this->logicalNodeKey_var);
    doUnpacking(b,this->wrongRoot_var);
}

OverlayKey& DxpsPublishResponse::getLogicalNodeKey()
{
    return logicalNodeKey_var;
}

void DxpsPublishResponse::setLogicalNodeKey(const OverlayKey& logicalNodeKey_var)
{
    this->logicalNodeKey_var = logicalNodeKey_var;
}

bool DxpsPublishResponse::getWrongRoot() const
{
    return wrongRoot_var;
}

void DxpsPublishResponse::setWrongRoot(bool wrongRoot_var)
{
    this->wrongRoot_var = wrongRoot_var;
}

class DxpsPublishResponseDescriptor : public cClassDescriptor
{
  public:
    DxpsPublishResponseDescriptor();
    virtual ~DxpsPublishResponseDescriptor();

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

Register_ClassDescriptor(DxpsPublishResponseDescriptor);

DxpsPublishResponseDescriptor::DxpsPublishResponseDescriptor() : cClassDescriptor("DxpsPublishResponse", "BaseResponseMessage")
{
}

DxpsPublishResponseDescriptor::~DxpsPublishResponseDescriptor()
{
}

bool DxpsPublishResponseDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DxpsPublishResponse *>(obj)!=NULL;
}

const char *DxpsPublishResponseDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DxpsPublishResponseDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int DxpsPublishResponseDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *DxpsPublishResponseDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "logicalNodeKey",
        "wrongRoot",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int DxpsPublishResponseDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='l' && strcmp(fieldName, "logicalNodeKey")==0) return base+0;
    if (fieldName[0]=='w' && strcmp(fieldName, "wrongRoot")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DxpsPublishResponseDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "OverlayKey",
        "bool",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *DxpsPublishResponseDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int DxpsPublishResponseDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DxpsPublishResponse *pp = (DxpsPublishResponse *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DxpsPublishResponseDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsPublishResponse *pp = (DxpsPublishResponse *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getLogicalNodeKey(); return out.str();}
        case 1: return bool2string(pp->getWrongRoot());
        default: return "";
    }
}

bool DxpsPublishResponseDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DxpsPublishResponse *pp = (DxpsPublishResponse *)object; (void)pp;
    switch (field) {
        case 1: pp->setWrongRoot(string2bool(value)); return true;
        default: return false;
    }
}

const char *DxpsPublishResponseDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "OverlayKey",
        NULL,
    };
    return (field>=0 && field<2) ? fieldStructNames[field] : NULL;
}

void *DxpsPublishResponseDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsPublishResponse *pp = (DxpsPublishResponse *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getLogicalNodeKey()); break;
        default: return NULL;
    }
}

Register_Class(DxpsSubscribeCall);

DxpsSubscribeCall::DxpsSubscribeCall(const char *name, int kind) : BaseCallMessage(name,kind)
{
}

DxpsSubscribeCall::DxpsSubscribeCall(const DxpsSubscribeCall& other) : BaseCallMessage()
{
    setName(other.getName());
    operator=(other);
}

DxpsSubscribeCall::~DxpsSubscribeCall()
{
}

DxpsSubscribeCall& DxpsSubscribeCall::operator=(const DxpsSubscribeCall& other)
{
    if (this==&other) return *this;
    BaseCallMessage::operator=(other);
    this->logicalNodeKey_var = other.logicalNodeKey_var;
    return *this;
}

void DxpsSubscribeCall::parsimPack(cCommBuffer *b)
{
    BaseCallMessage::parsimPack(b);
    doPacking(b,this->logicalNodeKey_var);
}

void DxpsSubscribeCall::parsimUnpack(cCommBuffer *b)
{
    BaseCallMessage::parsimUnpack(b);
    doUnpacking(b,this->logicalNodeKey_var);
}

OverlayKey& DxpsSubscribeCall::getLogicalNodeKey()
{
    return logicalNodeKey_var;
}

void DxpsSubscribeCall::setLogicalNodeKey(const OverlayKey& logicalNodeKey_var)
{
    this->logicalNodeKey_var = logicalNodeKey_var;
}

class DxpsSubscribeCallDescriptor : public cClassDescriptor
{
  public:
    DxpsSubscribeCallDescriptor();
    virtual ~DxpsSubscribeCallDescriptor();

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

Register_ClassDescriptor(DxpsSubscribeCallDescriptor);

DxpsSubscribeCallDescriptor::DxpsSubscribeCallDescriptor() : cClassDescriptor("DxpsSubscribeCall", "BaseCallMessage")
{
}

DxpsSubscribeCallDescriptor::~DxpsSubscribeCallDescriptor()
{
}

bool DxpsSubscribeCallDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DxpsSubscribeCall *>(obj)!=NULL;
}

const char *DxpsSubscribeCallDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DxpsSubscribeCallDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int DxpsSubscribeCallDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *DxpsSubscribeCallDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "logicalNodeKey",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int DxpsSubscribeCallDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='l' && strcmp(fieldName, "logicalNodeKey")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DxpsSubscribeCallDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "OverlayKey",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *DxpsSubscribeCallDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int DxpsSubscribeCallDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubscribeCall *pp = (DxpsSubscribeCall *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DxpsSubscribeCallDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubscribeCall *pp = (DxpsSubscribeCall *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getLogicalNodeKey(); return out.str();}
        default: return "";
    }
}

bool DxpsSubscribeCallDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubscribeCall *pp = (DxpsSubscribeCall *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *DxpsSubscribeCallDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "OverlayKey",
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *DxpsSubscribeCallDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubscribeCall *pp = (DxpsSubscribeCall *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getLogicalNodeKey()); break;
        default: return NULL;
    }
}

Register_Class(DxpsSubscribeResponse);

DxpsSubscribeResponse::DxpsSubscribeResponse(const char *name, int kind) : BaseResponseMessage(name,kind)
{
    this->wrongRoot_var = false;
}

DxpsSubscribeResponse::DxpsSubscribeResponse(const DxpsSubscribeResponse& other) : BaseResponseMessage()
{
    setName(other.getName());
    operator=(other);
}

DxpsSubscribeResponse::~DxpsSubscribeResponse()
{
}

DxpsSubscribeResponse& DxpsSubscribeResponse::operator=(const DxpsSubscribeResponse& other)
{
    if (this==&other) return *this;
    BaseResponseMessage::operator=(other);
    this->logicalNodeKey_var = other.logicalNodeKey_var;
    this->wrongRoot_var = other.wrongRoot_var;
    return *this;
}

void DxpsSubscribeResponse::parsimPack(cCommBuffer *b)
{
    BaseResponseMessage::parsimPack(b);
    doPacking(b,this->logicalNodeKey_var);
    doPacking(b,this->wrongRoot_var);
}

void DxpsSubscribeResponse::parsimUnpack(cCommBuffer *b)
{
    BaseResponseMessage::parsimUnpack(b);
    doUnpacking(b,this->logicalNodeKey_var);
    doUnpacking(b,this->wrongRoot_var);
}

OverlayKey& DxpsSubscribeResponse::getLogicalNodeKey()
{
    return logicalNodeKey_var;
}

void DxpsSubscribeResponse::setLogicalNodeKey(const OverlayKey& logicalNodeKey_var)
{
    this->logicalNodeKey_var = logicalNodeKey_var;
}

bool DxpsSubscribeResponse::getWrongRoot() const
{
    return wrongRoot_var;
}

void DxpsSubscribeResponse::setWrongRoot(bool wrongRoot_var)
{
    this->wrongRoot_var = wrongRoot_var;
}

class DxpsSubscribeResponseDescriptor : public cClassDescriptor
{
  public:
    DxpsSubscribeResponseDescriptor();
    virtual ~DxpsSubscribeResponseDescriptor();

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

Register_ClassDescriptor(DxpsSubscribeResponseDescriptor);

DxpsSubscribeResponseDescriptor::DxpsSubscribeResponseDescriptor() : cClassDescriptor("DxpsSubscribeResponse", "BaseResponseMessage")
{
}

DxpsSubscribeResponseDescriptor::~DxpsSubscribeResponseDescriptor()
{
}

bool DxpsSubscribeResponseDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DxpsSubscribeResponse *>(obj)!=NULL;
}

const char *DxpsSubscribeResponseDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DxpsSubscribeResponseDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int DxpsSubscribeResponseDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *DxpsSubscribeResponseDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "logicalNodeKey",
        "wrongRoot",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int DxpsSubscribeResponseDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='l' && strcmp(fieldName, "logicalNodeKey")==0) return base+0;
    if (fieldName[0]=='w' && strcmp(fieldName, "wrongRoot")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DxpsSubscribeResponseDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "OverlayKey",
        "bool",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *DxpsSubscribeResponseDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int DxpsSubscribeResponseDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubscribeResponse *pp = (DxpsSubscribeResponse *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DxpsSubscribeResponseDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubscribeResponse *pp = (DxpsSubscribeResponse *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getLogicalNodeKey(); return out.str();}
        case 1: return bool2string(pp->getWrongRoot());
        default: return "";
    }
}

bool DxpsSubscribeResponseDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubscribeResponse *pp = (DxpsSubscribeResponse *)object; (void)pp;
    switch (field) {
        case 1: pp->setWrongRoot(string2bool(value)); return true;
        default: return false;
    }
}

const char *DxpsSubscribeResponseDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "OverlayKey",
        NULL,
    };
    return (field>=0 && field<2) ? fieldStructNames[field] : NULL;
}

void *DxpsSubscribeResponseDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubscribeResponse *pp = (DxpsSubscribeResponse *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getLogicalNodeKey()); break;
        default: return NULL;
    }
}

Register_Class(DxpsSubscriptionRefreshMessage);

DxpsSubscriptionRefreshMessage::DxpsSubscriptionRefreshMessage(const char *name, int kind) : cPacket(name,kind)
{
}

DxpsSubscriptionRefreshMessage::DxpsSubscriptionRefreshMessage(const DxpsSubscriptionRefreshMessage& other) : cPacket()
{
    setName(other.getName());
    operator=(other);
}

DxpsSubscriptionRefreshMessage::~DxpsSubscriptionRefreshMessage()
{
}

DxpsSubscriptionRefreshMessage& DxpsSubscriptionRefreshMessage::operator=(const DxpsSubscriptionRefreshMessage& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    this->src_var = other.src_var;
    this->logicalNodeKey_var = other.logicalNodeKey_var;
    return *this;
}

void DxpsSubscriptionRefreshMessage::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->src_var);
    doPacking(b,this->logicalNodeKey_var);
}

void DxpsSubscriptionRefreshMessage::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->src_var);
    doUnpacking(b,this->logicalNodeKey_var);
}

NodeHandle& DxpsSubscriptionRefreshMessage::getSrc()
{
    return src_var;
}

void DxpsSubscriptionRefreshMessage::setSrc(const NodeHandle& src_var)
{
    this->src_var = src_var;
}

OverlayKey& DxpsSubscriptionRefreshMessage::getLogicalNodeKey()
{
    return logicalNodeKey_var;
}

void DxpsSubscriptionRefreshMessage::setLogicalNodeKey(const OverlayKey& logicalNodeKey_var)
{
    this->logicalNodeKey_var = logicalNodeKey_var;
}

class DxpsSubscriptionRefreshMessageDescriptor : public cClassDescriptor
{
  public:
    DxpsSubscriptionRefreshMessageDescriptor();
    virtual ~DxpsSubscriptionRefreshMessageDescriptor();

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

Register_ClassDescriptor(DxpsSubscriptionRefreshMessageDescriptor);

DxpsSubscriptionRefreshMessageDescriptor::DxpsSubscriptionRefreshMessageDescriptor() : cClassDescriptor("DxpsSubscriptionRefreshMessage", "cPacket")
{
}

DxpsSubscriptionRefreshMessageDescriptor::~DxpsSubscriptionRefreshMessageDescriptor()
{
}

bool DxpsSubscriptionRefreshMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DxpsSubscriptionRefreshMessage *>(obj)!=NULL;
}

const char *DxpsSubscriptionRefreshMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DxpsSubscriptionRefreshMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int DxpsSubscriptionRefreshMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *DxpsSubscriptionRefreshMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "src",
        "logicalNodeKey",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int DxpsSubscriptionRefreshMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+0;
    if (fieldName[0]=='l' && strcmp(fieldName, "logicalNodeKey")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DxpsSubscriptionRefreshMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "NodeHandle",
        "OverlayKey",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *DxpsSubscriptionRefreshMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int DxpsSubscriptionRefreshMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubscriptionRefreshMessage *pp = (DxpsSubscriptionRefreshMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DxpsSubscriptionRefreshMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubscriptionRefreshMessage *pp = (DxpsSubscriptionRefreshMessage *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getSrc(); return out.str();}
        case 1: {std::stringstream out; out << pp->getLogicalNodeKey(); return out.str();}
        default: return "";
    }
}

bool DxpsSubscriptionRefreshMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubscriptionRefreshMessage *pp = (DxpsSubscriptionRefreshMessage *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *DxpsSubscriptionRefreshMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "NodeHandle",
        "OverlayKey",
    };
    return (field>=0 && field<2) ? fieldStructNames[field] : NULL;
}

void *DxpsSubscriptionRefreshMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubscriptionRefreshMessage *pp = (DxpsSubscriptionRefreshMessage *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getSrc()); break;
        case 1: return (void *)(&pp->getLogicalNodeKey()); break;
        default: return NULL;
    }
}

Register_Class(DxpsLeaveMessage);

DxpsLeaveMessage::DxpsLeaveMessage(const char *name, int kind) : cPacket(name,kind)
{
}

DxpsLeaveMessage::DxpsLeaveMessage(const DxpsLeaveMessage& other) : cPacket()
{
    setName(other.getName());
    operator=(other);
}

DxpsLeaveMessage::~DxpsLeaveMessage()
{
}

DxpsLeaveMessage& DxpsLeaveMessage::operator=(const DxpsLeaveMessage& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    this->src_var = other.src_var;
    this->logicalNodeKey_var = other.logicalNodeKey_var;
    return *this;
}

void DxpsLeaveMessage::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->src_var);
    doPacking(b,this->logicalNodeKey_var);
}

void DxpsLeaveMessage::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->src_var);
    doUnpacking(b,this->logicalNodeKey_var);
}

NodeHandle& DxpsLeaveMessage::getSrc()
{
    return src_var;
}

void DxpsLeaveMessage::setSrc(const NodeHandle& src_var)
{
    this->src_var = src_var;
}

OverlayKey& DxpsLeaveMessage::getLogicalNodeKey()
{
    return logicalNodeKey_var;
}

void DxpsLeaveMessage::setLogicalNodeKey(const OverlayKey& logicalNodeKey_var)
{
    this->logicalNodeKey_var = logicalNodeKey_var;
}

class DxpsLeaveMessageDescriptor : public cClassDescriptor
{
  public:
    DxpsLeaveMessageDescriptor();
    virtual ~DxpsLeaveMessageDescriptor();

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

Register_ClassDescriptor(DxpsLeaveMessageDescriptor);

DxpsLeaveMessageDescriptor::DxpsLeaveMessageDescriptor() : cClassDescriptor("DxpsLeaveMessage", "cPacket")
{
}

DxpsLeaveMessageDescriptor::~DxpsLeaveMessageDescriptor()
{
}

bool DxpsLeaveMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DxpsLeaveMessage *>(obj)!=NULL;
}

const char *DxpsLeaveMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DxpsLeaveMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int DxpsLeaveMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *DxpsLeaveMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "src",
        "logicalNodeKey",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int DxpsLeaveMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+0;
    if (fieldName[0]=='l' && strcmp(fieldName, "logicalNodeKey")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DxpsLeaveMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "NodeHandle",
        "OverlayKey",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *DxpsLeaveMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int DxpsLeaveMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DxpsLeaveMessage *pp = (DxpsLeaveMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DxpsLeaveMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsLeaveMessage *pp = (DxpsLeaveMessage *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getSrc(); return out.str();}
        case 1: {std::stringstream out; out << pp->getLogicalNodeKey(); return out.str();}
        default: return "";
    }
}

bool DxpsLeaveMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DxpsLeaveMessage *pp = (DxpsLeaveMessage *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *DxpsLeaveMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "NodeHandle",
        "OverlayKey",
    };
    return (field>=0 && field<2) ? fieldStructNames[field] : NULL;
}

void *DxpsLeaveMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsLeaveMessage *pp = (DxpsLeaveMessage *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getSrc()); break;
        case 1: return (void *)(&pp->getLogicalNodeKey()); break;
        default: return NULL;
    }
}

Register_Class(DxpsTimer);

DxpsTimer::DxpsTimer(const char *name, int kind) : cMessage(name,kind)
{
    this->timerType_var = 0;
}

DxpsTimer::DxpsTimer(const DxpsTimer& other) : cMessage()
{
    setName(other.getName());
    operator=(other);
}

DxpsTimer::~DxpsTimer()
{
}

DxpsTimer& DxpsTimer::operator=(const DxpsTimer& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    this->timerType_var = other.timerType_var;
    this->child_var = other.child_var;
    this->logicalNodeKey_var = other.logicalNodeKey_var;
    return *this;
}

void DxpsTimer::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->timerType_var);
    doPacking(b,this->child_var);
    doPacking(b,this->logicalNodeKey_var);
}

void DxpsTimer::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->timerType_var);
    doUnpacking(b,this->child_var);
    doUnpacking(b,this->logicalNodeKey_var);
}

int DxpsTimer::getTimerType() const
{
    return timerType_var;
}

void DxpsTimer::setTimerType(int timerType_var)
{
    this->timerType_var = timerType_var;
}

NodeHandle& DxpsTimer::getChild()
{
    return child_var;
}

void DxpsTimer::setChild(const NodeHandle& child_var)
{
    this->child_var = child_var;
}

OverlayKey& DxpsTimer::getLogicalNodeKey()
{
    return logicalNodeKey_var;
}

void DxpsTimer::setLogicalNodeKey(const OverlayKey& logicalNodeKey_var)
{
    this->logicalNodeKey_var = logicalNodeKey_var;
}

class DxpsTimerDescriptor : public cClassDescriptor
{
  public:
    DxpsTimerDescriptor();
    virtual ~DxpsTimerDescriptor();

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

Register_ClassDescriptor(DxpsTimerDescriptor);

DxpsTimerDescriptor::DxpsTimerDescriptor() : cClassDescriptor("DxpsTimer", "cMessage")
{
}

DxpsTimerDescriptor::~DxpsTimerDescriptor()
{
}

bool DxpsTimerDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DxpsTimer *>(obj)!=NULL;
}

const char *DxpsTimerDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DxpsTimerDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int DxpsTimerDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *DxpsTimerDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "timerType",
        "child",
        "logicalNodeKey",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int DxpsTimerDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "timerType")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "child")==0) return base+1;
    if (fieldName[0]=='l' && strcmp(fieldName, "logicalNodeKey")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DxpsTimerDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "NodeHandle",
        "OverlayKey",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *DxpsTimerDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "DxpsTimerType";
            return NULL;
        default: return NULL;
    }
}

int DxpsTimerDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DxpsTimer *pp = (DxpsTimer *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DxpsTimerDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsTimer *pp = (DxpsTimer *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getTimerType());
        case 1: {std::stringstream out; out << pp->getChild(); return out.str();}
        case 2: {std::stringstream out; out << pp->getLogicalNodeKey(); return out.str();}
        default: return "";
    }
}

bool DxpsTimerDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DxpsTimer *pp = (DxpsTimer *)object; (void)pp;
    switch (field) {
        case 0: pp->setTimerType(string2long(value)); return true;
        default: return false;
    }
}

const char *DxpsTimerDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        "NodeHandle",
        "OverlayKey",
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *DxpsTimerDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsTimer *pp = (DxpsTimer *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getChild()); break;
        case 2: return (void *)(&pp->getLogicalNodeKey()); break;
        default: return NULL;
    }
}

Register_Class(DxpsDataMessage);

DxpsDataMessage::DxpsDataMessage(const char *name, int kind) : cPacket(name,kind)
{
    this->dxpsMsgId_var = 0;
    this->empty_var = false;
}

DxpsDataMessage::DxpsDataMessage(const DxpsDataMessage& other) : cPacket()
{
    setName(other.getName());
    operator=(other);
}

DxpsDataMessage::~DxpsDataMessage()
{
}

DxpsDataMessage& DxpsDataMessage::operator=(const DxpsDataMessage& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    this->logicalNodeKey_var = other.logicalNodeKey_var;
    this->dxpsMsgId_var = other.dxpsMsgId_var;
    this->empty_var = other.empty_var;
    return *this;
}

void DxpsDataMessage::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->logicalNodeKey_var);
    doPacking(b,this->dxpsMsgId_var);
    doPacking(b,this->empty_var);
}

void DxpsDataMessage::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->logicalNodeKey_var);
    doUnpacking(b,this->dxpsMsgId_var);
    doUnpacking(b,this->empty_var);
}

OverlayKey& DxpsDataMessage::getLogicalNodeKey()
{
    return logicalNodeKey_var;
}

void DxpsDataMessage::setLogicalNodeKey(const OverlayKey& logicalNodeKey_var)
{
    this->logicalNodeKey_var = logicalNodeKey_var;
}

long DxpsDataMessage::getDxpsMsgId() const
{
    return dxpsMsgId_var;
}

void DxpsDataMessage::setDxpsMsgId(long dxpsMsgId_var)
{
    this->dxpsMsgId_var = dxpsMsgId_var;
}

bool DxpsDataMessage::getEmpty() const
{
    return empty_var;
}

void DxpsDataMessage::setEmpty(bool empty_var)
{
    this->empty_var = empty_var;
}

class DxpsDataMessageDescriptor : public cClassDescriptor
{
  public:
    DxpsDataMessageDescriptor();
    virtual ~DxpsDataMessageDescriptor();

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

Register_ClassDescriptor(DxpsDataMessageDescriptor);

DxpsDataMessageDescriptor::DxpsDataMessageDescriptor() : cClassDescriptor("DxpsDataMessage", "cPacket")
{
}

DxpsDataMessageDescriptor::~DxpsDataMessageDescriptor()
{
}

bool DxpsDataMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DxpsDataMessage *>(obj)!=NULL;
}

const char *DxpsDataMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DxpsDataMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int DxpsDataMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *DxpsDataMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "logicalNodeKey",
        "dxpsMsgId",
        "empty",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int DxpsDataMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='l' && strcmp(fieldName, "logicalNodeKey")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dxpsMsgId")==0) return base+1;
    if (fieldName[0]=='e' && strcmp(fieldName, "empty")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DxpsDataMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "OverlayKey",
        "long",
        "bool",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *DxpsDataMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int DxpsDataMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DxpsDataMessage *pp = (DxpsDataMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DxpsDataMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsDataMessage *pp = (DxpsDataMessage *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getLogicalNodeKey(); return out.str();}
        case 1: return long2string(pp->getDxpsMsgId());
        case 2: return bool2string(pp->getEmpty());
        default: return "";
    }
}

bool DxpsDataMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DxpsDataMessage *pp = (DxpsDataMessage *)object; (void)pp;
    switch (field) {
        case 1: pp->setDxpsMsgId(string2long(value)); return true;
        case 2: pp->setEmpty(string2bool(value)); return true;
        default: return false;
    }
}

const char *DxpsDataMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "OverlayKey",
        NULL,
        NULL,
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *DxpsDataMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsDataMessage *pp = (DxpsDataMessage *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getLogicalNodeKey()); break;
        default: return NULL;
    }
}

Register_Class(DxpsDataDeliverMessage);

DxpsDataDeliverMessage::DxpsDataDeliverMessage(const char *name, int kind) : cPacket(name,kind)
{
    this->dxpsMsgId_var = 0;
    this->empty_var = false;
}

DxpsDataDeliverMessage::DxpsDataDeliverMessage(const DxpsDataDeliverMessage& other) : cPacket()
{
    setName(other.getName());
    operator=(other);
}

DxpsDataDeliverMessage::~DxpsDataDeliverMessage()
{
}

DxpsDataDeliverMessage& DxpsDataDeliverMessage::operator=(const DxpsDataDeliverMessage& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    this->logicalNodeKey_var = other.logicalNodeKey_var;
    this->dxpsMsgId_var = other.dxpsMsgId_var;
    this->empty_var = other.empty_var;
    return *this;
}

void DxpsDataDeliverMessage::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->logicalNodeKey_var);
    doPacking(b,this->dxpsMsgId_var);
    doPacking(b,this->empty_var);
}

void DxpsDataDeliverMessage::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->logicalNodeKey_var);
    doUnpacking(b,this->dxpsMsgId_var);
    doUnpacking(b,this->empty_var);
}

OverlayKey& DxpsDataDeliverMessage::getLogicalNodeKey()
{
    return logicalNodeKey_var;
}

void DxpsDataDeliverMessage::setLogicalNodeKey(const OverlayKey& logicalNodeKey_var)
{
    this->logicalNodeKey_var = logicalNodeKey_var;
}

long DxpsDataDeliverMessage::getDxpsMsgId() const
{
    return dxpsMsgId_var;
}

void DxpsDataDeliverMessage::setDxpsMsgId(long dxpsMsgId_var)
{
    this->dxpsMsgId_var = dxpsMsgId_var;
}

bool DxpsDataDeliverMessage::getEmpty() const
{
    return empty_var;
}

void DxpsDataDeliverMessage::setEmpty(bool empty_var)
{
    this->empty_var = empty_var;
}

class DxpsDataDeliverMessageDescriptor : public cClassDescriptor
{
  public:
    DxpsDataDeliverMessageDescriptor();
    virtual ~DxpsDataDeliverMessageDescriptor();

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

Register_ClassDescriptor(DxpsDataDeliverMessageDescriptor);

DxpsDataDeliverMessageDescriptor::DxpsDataDeliverMessageDescriptor() : cClassDescriptor("DxpsDataDeliverMessage", "cPacket")
{
}

DxpsDataDeliverMessageDescriptor::~DxpsDataDeliverMessageDescriptor()
{
}

bool DxpsDataDeliverMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DxpsDataDeliverMessage *>(obj)!=NULL;
}

const char *DxpsDataDeliverMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DxpsDataDeliverMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int DxpsDataDeliverMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *DxpsDataDeliverMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "logicalNodeKey",
        "dxpsMsgId",
        "empty",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int DxpsDataDeliverMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='l' && strcmp(fieldName, "logicalNodeKey")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dxpsMsgId")==0) return base+1;
    if (fieldName[0]=='e' && strcmp(fieldName, "empty")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DxpsDataDeliverMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "OverlayKey",
        "long",
        "bool",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *DxpsDataDeliverMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int DxpsDataDeliverMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DxpsDataDeliverMessage *pp = (DxpsDataDeliverMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DxpsDataDeliverMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsDataDeliverMessage *pp = (DxpsDataDeliverMessage *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getLogicalNodeKey(); return out.str();}
        case 1: return long2string(pp->getDxpsMsgId());
        case 2: return bool2string(pp->getEmpty());
        default: return "";
    }
}

bool DxpsDataDeliverMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DxpsDataDeliverMessage *pp = (DxpsDataDeliverMessage *)object; (void)pp;
    switch (field) {
        case 1: pp->setDxpsMsgId(string2long(value)); return true;
        case 2: pp->setEmpty(string2bool(value)); return true;
        default: return false;
    }
}

const char *DxpsDataDeliverMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "OverlayKey",
        NULL,
        NULL,
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *DxpsDataDeliverMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsDataDeliverMessage *pp = (DxpsDataDeliverMessage *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getLogicalNodeKey()); break;
        default: return NULL;
    }
}

Register_Class(DxpsSubscriptionMessage);

DxpsSubscriptionMessage::DxpsSubscriptionMessage(const char *name, int kind) : cPacket(name,kind)
{
    this->dxpsMsgId_var = 0;
    this->empty_var = false;
}

DxpsSubscriptionMessage::DxpsSubscriptionMessage(const DxpsSubscriptionMessage& other) : cPacket()
{
    setName(other.getName());
    operator=(other);
}

DxpsSubscriptionMessage::~DxpsSubscriptionMessage()
{
}

DxpsSubscriptionMessage& DxpsSubscriptionMessage::operator=(const DxpsSubscriptionMessage& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    this->logicalNodeKey_var = other.logicalNodeKey_var;
    this->dxpsMsgId_var = other.dxpsMsgId_var;
    this->empty_var = other.empty_var;
    return *this;
}

void DxpsSubscriptionMessage::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->logicalNodeKey_var);
    doPacking(b,this->dxpsMsgId_var);
    doPacking(b,this->empty_var);
}

void DxpsSubscriptionMessage::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->logicalNodeKey_var);
    doUnpacking(b,this->dxpsMsgId_var);
    doUnpacking(b,this->empty_var);
}

OverlayKey& DxpsSubscriptionMessage::getLogicalNodeKey()
{
    return logicalNodeKey_var;
}

void DxpsSubscriptionMessage::setLogicalNodeKey(const OverlayKey& logicalNodeKey_var)
{
    this->logicalNodeKey_var = logicalNodeKey_var;
}

long DxpsSubscriptionMessage::getDxpsMsgId() const
{
    return dxpsMsgId_var;
}

void DxpsSubscriptionMessage::setDxpsMsgId(long dxpsMsgId_var)
{
    this->dxpsMsgId_var = dxpsMsgId_var;
}

bool DxpsSubscriptionMessage::getEmpty() const
{
    return empty_var;
}

void DxpsSubscriptionMessage::setEmpty(bool empty_var)
{
    this->empty_var = empty_var;
}

class DxpsSubscriptionMessageDescriptor : public cClassDescriptor
{
  public:
    DxpsSubscriptionMessageDescriptor();
    virtual ~DxpsSubscriptionMessageDescriptor();

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

Register_ClassDescriptor(DxpsSubscriptionMessageDescriptor);

DxpsSubscriptionMessageDescriptor::DxpsSubscriptionMessageDescriptor() : cClassDescriptor("DxpsSubscriptionMessage", "cPacket")
{
}

DxpsSubscriptionMessageDescriptor::~DxpsSubscriptionMessageDescriptor()
{
}

bool DxpsSubscriptionMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DxpsSubscriptionMessage *>(obj)!=NULL;
}

const char *DxpsSubscriptionMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DxpsSubscriptionMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int DxpsSubscriptionMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *DxpsSubscriptionMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "logicalNodeKey",
        "dxpsMsgId",
        "empty",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int DxpsSubscriptionMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='l' && strcmp(fieldName, "logicalNodeKey")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dxpsMsgId")==0) return base+1;
    if (fieldName[0]=='e' && strcmp(fieldName, "empty")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DxpsSubscriptionMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "OverlayKey",
        "long",
        "bool",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *DxpsSubscriptionMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int DxpsSubscriptionMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubscriptionMessage *pp = (DxpsSubscriptionMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DxpsSubscriptionMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubscriptionMessage *pp = (DxpsSubscriptionMessage *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getLogicalNodeKey(); return out.str();}
        case 1: return long2string(pp->getDxpsMsgId());
        case 2: return bool2string(pp->getEmpty());
        default: return "";
    }
}

bool DxpsSubscriptionMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubscriptionMessage *pp = (DxpsSubscriptionMessage *)object; (void)pp;
    switch (field) {
        case 1: pp->setDxpsMsgId(string2long(value)); return true;
        case 2: pp->setEmpty(string2bool(value)); return true;
        default: return false;
    }
}

const char *DxpsSubscriptionMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "OverlayKey",
        NULL,
        NULL,
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *DxpsSubscriptionMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DxpsSubscriptionMessage *pp = (DxpsSubscriptionMessage *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getLogicalNodeKey()); break;
        default: return NULL;
    }
}


