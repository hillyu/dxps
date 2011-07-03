
#ifndef INCLUDE_SUBGEN_H
#define INCLUDE_SUBGEN_H
#include "bloom_filter.hpp"
#include <iostream>
#include <fstream>
class SubGen {
public:
     SubGen(bloom_filter& filter);
     //TODO SubGen(string xpe)
     int getBloom(){return bloom;}//TODO change the return type to bloom_filter
     std::string getXpe(){return xpe;}
 private:
     unsigned int bloom;
     std::string xpe;
     void parseXpe(std::string xpe,bloom_filter* b,std::string parent, int& i);
     std::string random_line( std::string filepath );

};
#endif
