#ifndef INCLUDE_SUBGEN_H
#define INCLUDE_SUBGEN_H
#include "bloom_filter.hpp"
#include <iostream>
#include <fstream>
class SubGen {
public:
     SubGen(bloom_filter& filter);
     //TODO SubGen(string xpe)
     OverlayKey getBloom() const {return bloom;}
     std::string getXpe(){return xpe;}
     uint32_t  getSize(){return size;}
private:
      //unsigned char bloom[];
     OverlayKey bloom;
     std::string xpe;
     void parseXpe(std::string xpe,bloom_filter* b,std::string parent, int& i);
     std::string random_line( std::string filepath );
     uint32_t size;
};
#endif
