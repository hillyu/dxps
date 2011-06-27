#include <iostream>
#include "bloom_filter.hpp"
#include <bitset>
int main(int argc, const char *argv[])
{
	
   bloom_filter filter(0x08,0x01);
	   filter.insert("test");
	   std::cout <<"the bloom filter is"<< "\n"<< *(const int*)filter.table()<<"\n";
	   filter.insert("what");
	   std::cout <<"the bloom filter is"<< "\n"<< *(const unsigned short*)filter.table()<<"\n";
	   filter.insert("is");
	   //const unsigned char* i=filter.table();
	   std::size_t i=filter.size();
	   std::cout <<"contains what?" << filter.contains("what"); 
	   std::cout <<"contains is?" << filter.contains("is"); 
	   std::cout <<"contains no?" << filter.contains("no"); 
	   std::cout <<"the bloom filter is"<< i<<"\n"<< *(const unsigned short*)filter.table()<<"\n";
	   std::bitset<10> b (*(const unsigned long*)filter.table());
	   std::cout << b[1];
	   std::cout << b[2];
	   std::cout << b[3];
	   std::cout << b[4];
	   std::cout << b[5];
	   std::cout << b[6];
	   std::cout << b[7];
	   std::cout << b[8];
	return 0;
}
