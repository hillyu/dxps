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
    this->groupId_var = other.groupId_var;
    return *this;
}

void DxpsJoinCall::parsimPack(cCommBuffer *b)
{
    BaseCallMessage::parsimPack(b);
    doPacking(b,this->groupId_var);
}

void DxpsJoinCall::parsimUnpack(cCommBuffer *b)
{
    BaseCallMessage::parsimUnpack(b);
    doUnpacking(b,this->groupId_var);
}

OverlayKey& DxpsJoinCall::getGroupId()
{
    return groupId_var;
}

void DxpsJoinCall::setGroupId(const OverlayKey& groupId_var)
{
    this->groupId_var = groupId_var;
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
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
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
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
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
        "groupId",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int DxpsJoinCallDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='g' && strcmp(fieldName, "groupId")==0) return base+0;
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
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
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
        case 0: {std::stringstream out; out << pp->getGroupId(); return out.str();}
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
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
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
        case 0: return (void *)(&pp->getGroupId()); break;
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
    this->groupId_var = other.groupId_var;
    return *this;
}

void DxpsJoinResponse::parsimPack(cCommBuffer *b)
{
    BaseResponseMessage::parsimPack(b);
    doPacking(b,this->groupId_var);
}

void DxpsJoinResponse::parsimUnpack(cCommBuffer *b)
{
    BaseResponseMessage::parsimUnpack(b);
    doUnpacking(b,this->groupId_var);
}

OverlayKey& DxpsJoinResponse::getGroupId()
{
    return groupId_var;
}

void DxpsJoinResponse::setGroupId(const OverlayKey& groupId_var)
{
    this->groupId_var = groupId_var;
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
        "groupId",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int DxpsJoinResponseDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='g' && strcmp(fieldName, "groupId")==0) return base+0;
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
        case 0: {std::stringstream out; out << pp->getGroupId(); return out.str();}
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
        case 0: return (void *)(&pp->getGroupId()); break;
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
    this->groupId_var = other.groupId_var;
    return *this;
}

void DxpsPublishCall::parsimPack(cCommBuffer *b)
{
    BaseCallMessage::parsimPack(b);
    doPacking(b,this->groupId_var);
}

void DxpsPublishCall::parsimUnpack(cCommBuffer *b)
{
    BaseCallMessage::parsimUnpack(b);
    doUnpacking(b,this->groupId_var);
}

OverlayKey& DxpsPublishCall::getGroupId()
{
    return groupId_var;
}

void DxpsPublishCall::setGroupId(const OverlayKey& groupId_var)
{
    this->groupId_var = groupId_var;
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
        "groupId",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int DxpsPublishCallDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='g' && strcmp(fieldName, "groupId")==0) return base+0;
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
        case 0: {std::stringstream out; out << pp->getGroupId(); return out.str();}
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
        case 0: return (void *)(&pp->getGroupId()); break;
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
    this->groupId_var = other.groupId_var;
    this->wrongRoot_var = other.wrongRoot_var;
    return *this;
}

void DxpsPublishResponse::parsimPack(cCommBuffer *b)
{
    BaseResponseMessage::parsimPack(b);
    doPacking(b,this->groupId_var);
    doPacking(b,this->wrongRoot_var);
}

void DxpsPublishResponse::parsimUnpack(cCommBuffer *b)
{
    BaseResponseMessage::parsimUnpack(b);
    doUnpacking(b,this->groupId_var);
    doUnpacking(b,this->wrongRoot_var);
}

OverlayKey& DxpsPublishResponse::getGroupId()
{
    return groupId_var;
}

void DxpsPublishResponse::setGroupId(const OverlayKey& groupId_var)
{
    this->groupId_var = groupId_var;
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
        "groupId",
        "wrongRoot",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int DxpsPublishResponseDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='g' && strcmp(fieldName, "groupId")==0) return base+0;
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
        case 0: {std::stringstream out; out << pp->getGroupId(); return out.str();}
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
        case 0: return (void *)(&pp->getGroupId()); break;
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
    this->groupId_var = other.groupId_var;
    return *this;
}

void DxpsSubscriptionRefreshMessage::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->src_var);
    doPacking(b,this->groupId_var);
}

void DxpsSubscriptionRefreshMessage::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->src_var);
    doUnpacking(b,this->groupId_var);
}

NodeHandle& DxpsSubscriptionRefreshMessage::getSrc()
{
    return src_var;
}

void DxpsSubscriptionRefreshMessage::setSrc(const NodeHandle& src_var)
{
    this->src_var = src_var;
}

OverlayKey& DxpsSubscriptionRefreshMessage::getGroupId()
{
    return groupId_var;
}

void DxpsSubscriptionRefreshMessage::setGroupId(const OverlayKey& groupId_var)
{
    this->groupId_var = groupId_var;
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
        "groupId",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int DxpsSubscriptionRefreshMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+0;
    if (fieldName[0]=='g' && strcmp(fieldName, "groupId")==0) return base+1;
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
        case 1: {std::stringstream out; out << pp->getGroupId(); return out.str();}
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
        case 1: return (void *)(&pp->getGroupId()); break;
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
    this->groupId_var = other.groupId_var;
    return *this;
}

void DxpsLeaveMessage::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->src_var);
    doPacking(b,this->groupId_var);
}

void DxpsLeaveMessage::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->src_var);
    doUnpacking(b,this->groupId_var);
}

NodeHandle& DxpsLeaveMessage::getSrc()
{
    return src_var;
}

void DxpsLeaveMessage::setSrc(const NodeHandle& src_var)
{
    this->src_var = src_var;
}

OverlayKey& DxpsLeaveMessage::getGroupId()
{
    return groupId_var;
}

void DxpsLeaveMessage::setGroupId(const OverlayKey& groupId_var)
{
    this->groupId_var = groupId_var;
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
        "groupId",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int DxpsLeaveMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+0;
    if (fieldName[0]=='g' && strcmp(fieldName, "groupId")==0) return base+1;
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
        case 1: {std::stringstream out; out << pp->getGroupId(); return out.str();}
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
        case 1: return (void *)(&pp->getGroupId()); break;
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
    this->group_var = other.group_var;
    return *this;
}

void DxpsTimer::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
    doPacking(b,this->timerType_var);
    doPacking(b,this->child_var);
    doPacking(b,this->group_var);
}

void DxpsTimer::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
    doUnpacking(b,this->timerType_var);
    doUnpacking(b,this->child_var);
    doUnpacking(b,this->group_var);
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

OverlayKey& DxpsTimer::getGroup()
{
    return group_var;
}

void DxpsTimer::setGroup(const OverlayKey& group_var)
{
    this->group_var = group_var;
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
        "group",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int DxpsTimerDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "timerType")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "child")==0) return base+1;
    if (fieldName[0]=='g' && strcmp(fieldName, "group")==0) return base+2;
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
        case 2: {std::stringstream out; out << pp->getGroup(); return out.str();}
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
        case 2: return (void *)(&pp->getGroup()); break;
        default: return NULL;
    }
}

Register_Class(DxpsDataMessage);

DxpsDataMessage::DxpsDataMessage(const char *name, int kind) : cPacket(name,kind)
{
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
    this->groupId_var = other.groupId_var;
    this->empty_var = other.empty_var;
    return *this;
}

void DxpsDataMessage::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->groupId_var);
    doPacking(b,this->empty_var);
}

void DxpsDataMessage::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->groupId_var);
    doUnpacking(b,this->empty_var);
}

OverlayKey& DxpsDataMessage::getGroupId()
{
    return groupId_var;
}

void DxpsDataMessage::setGroupId(const OverlayKey& groupId_var)
{
    this->groupId_var = groupId_var;
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
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
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
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
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
        "groupId",
        "empty",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int DxpsDataMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='g' && strcmp(fieldName, "groupId")==0) return base+0;
    if (fieldName[0]=='e' && strcmp(fieldName, "empty")==0) return base+1;
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
        "bool",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
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
        case 0: {std::stringstream out; out << pp->getGroupId(); return out.str();}
        case 1: return bool2string(pp->getEmpty());
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
        case 1: pp->setEmpty(string2bool(value)); return true;
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
    };
    return (field>=0 && field<2) ? fieldStructNames[field] : NULL;
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
        case 0: return (void *)(&pp->getGroupId()); break;
        default: return NULL;
    }
}


