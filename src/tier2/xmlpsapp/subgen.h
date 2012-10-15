#ifndef INCLUDE_SUBGEN_H
#define INCLUDE_SUBGEN_H
#include "bloom_filter.hpp"
#include <iostream>
#include <fstream>
#include "OverlayKey.h"
class SubGen {
public:
	SubGen();
	SubGen(bloom_filter& filter);
  SubGen(int l,int k, OverlayKey mykey);
	//TODO SubGen(string xpe)
	OverlayKey getBloom() const {return bloom;}
	std::string getXpe() const {return xpe;}
	uint32_t  getSize(){return size;}
inline bool operator== ( const SubGen &other) const
{
      return (this->getBloom() == other.getBloom() && this->getXpe() == other.getXpe());
}
bool operator!= ( const SubGen &other) const
{
      return !(*this == other);
}
static std::string random_line( std::string filepath );
private:
	//unsigned char bloom[];
	OverlayKey bloom;
	std::string xpe;
	void parseXpe(std::string xpe,bloom_filter* b,std::string parent, int& i);

	uint32_t size;
};

 

#endif
