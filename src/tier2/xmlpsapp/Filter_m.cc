//
// Generated file, do not edit! Created by opp_msgc 4.1 from applications/dxps/../../tier2/xmlpsapp/Filter.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "Filter_m.h"

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




Register_Class(Filter);

Filter::Filter(const char *name, int kind) : cPacket(name,kind)
{
    filter_arraysize = 0;
    this->filter_var = 0;
    this->filterSize_var = 0;
}

Filter::Filter(const Filter& other) : cPacket()
{
    setName(other.getName());
    filter_arraysize = 0;
    this->filter_var = 0;
    operator=(other);
}

Filter::~Filter()
{
    delete [] filter_var;
}

Filter& Filter::operator=(const Filter& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    delete [] this->filter_var;
    this->filter_var = (other.filter_arraysize==0) ? NULL : new unsigned char[other.filter_arraysize];
    filter_arraysize = other.filter_arraysize;
    for (unsigned int i=0; i<filter_arraysize; i++)
        this->filter_var[i] = other.filter_var[i];
    this->filterSize_var = other.filterSize_var;
    return *this;
}

void Filter::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    b->pack(filter_arraysize);
    doPacking(b,this->filter_var,filter_arraysize);
    doPacking(b,this->filterSize_var);
}

void Filter::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    delete [] this->filter_var;
    b->unpack(filter_arraysize);
    if (filter_arraysize==0) {
        this->filter_var = 0;
    } else {
        this->filter_var = new unsigned char[filter_arraysize];
        doUnpacking(b,this->filter_var,filter_arraysize);
    }
    doUnpacking(b,this->filterSize_var);
}

void Filter::setFilterArraySize(unsigned int size)
{
    unsigned char *filter_var2 = (size==0) ? NULL : new unsigned char[size];
    unsigned int sz = filter_arraysize < size ? filter_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        filter_var2[i] = this->filter_var[i];
    for (unsigned int i=sz; i<size; i++)
        filter_var2[i] = 0;
    filter_arraysize = size;
    delete [] this->filter_var;
    this->filter_var = filter_var2;
}

unsigned int Filter::getFilterArraySize() const
{
    return filter_arraysize;
}

unsigned char Filter::getFilter(unsigned int k) const
{
    if (k>=filter_arraysize) throw cRuntimeError("Array of size %d indexed by %d", filter_arraysize, k);
    return filter_var[k];
}

void Filter::setFilter(unsigned int k, unsigned char filter_var)
{
    if (k>=filter_arraysize) throw cRuntimeError("Array of size %d indexed by %d", filter_arraysize, k);
    this->filter_var[k]=filter_var;
}

int Filter::getFilterSize() const
{
    return filterSize_var;
}

void Filter::setFilterSize(int filterSize_var)
{
    this->filterSize_var = filterSize_var;
}

class FilterDescriptor : public cClassDescriptor
{
  public:
    FilterDescriptor();
    virtual ~FilterDescriptor();

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

Register_ClassDescriptor(FilterDescriptor);

FilterDescriptor::FilterDescriptor() : cClassDescriptor("Filter", "cPacket")
{
}

FilterDescriptor::~FilterDescriptor()
{
}

bool FilterDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Filter *>(obj)!=NULL;
}

const char *FilterDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int FilterDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int FilterDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *FilterDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "filter",
        "filterSize",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int FilterDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "filter")==0) return base+0;
    if (fieldName[0]=='f' && strcmp(fieldName, "filterSize")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *FilterDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *FilterDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int FilterDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Filter *pp = (Filter *)object; (void)pp;
    switch (field) {
        case 0: return pp->getFilterArraySize();
        default: return 0;
    }
}

std::string FilterDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Filter *pp = (Filter *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getFilter(i));
        case 1: return long2string(pp->getFilterSize());
        default: return "";
    }
}

bool FilterDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Filter *pp = (Filter *)object; (void)pp;
    switch (field) {
        case 0: pp->setFilter(i,string2ulong(value)); return true;
        case 1: pp->setFilterSize(string2long(value)); return true;
        default: return false;
    }
}

const char *FilterDescriptor::getFieldStructName(void *object, int field) const
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

void *FilterDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Filter *pp = (Filter *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


