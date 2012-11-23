#ifndef INCLUDE_SUBGEN_H
#define INCLUDE_SUBGEN_H
#include "bloom_filter.h"
#include <iostream>
#include <fstream>
#include "OverlayKey.h"
class SubGen {
public:
	SubGen();
  SubGen(OverlayKey key, std::string myxpe);
	SubGen(bloom_filter& filter);
  SubGen(int l,int k, OverlayKey mykey, std::string xpelist);
   //    std::ifstream file (filepath.c_str());
	OverlayKey getBloom() const {return bloom;}
  static std::vector<SubGen> getPool(int l, int k,OverlayKey mykey, std::string  xpelist); 
	std::string getXpe() const {return xpe;}
	uint32_t  getSize(){return size;}
	static void parseXpe(std::string xpe,bloom_filter* b,std::string parent, int& i);
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

	uint32_t size;
};

 

#endif
