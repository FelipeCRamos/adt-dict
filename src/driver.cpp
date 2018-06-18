#include <iostream>
#include "dsal.hpp"
#include "dal.hpp"

#define debug_mode false
#define dal_test true
#define dsal_test true
#define remove_func_test true

class MyKeyComparator {
	public:
		bool operator()( const int & lhs, const int & rhs ) const{
			return lhs < rhs;
		}
};

int main(void){

	std::pair<int, std::string> people[] = {
		std::pair<int, std::string> (122, "Felipe"),
		std::pair<int, std::string> (18, "Oziel Overwritted"),
		std::pair<int, std::string> (11, "Winne"),
		std::pair<int, std::string> (18, "Oziel"),
		std::pair<int, std::string> (12, "Amanda"),
		std::pair<int, std::string> (90, "Paulo"),
		std::pair<int, std::string> (29, "Felps"),
		std::pair<int, std::string> (19, "Max"),
		std::pair<int, std::string> (28, "Daniel"),
		std::pair<int, std::string> (14, "Bola")
	};


	
	if(dal_test){
		if(!debug_mode) std::cout << "-----------TESTING DAL-----------------------------\n";
	/* DAL TEST {{{*/
		DAL<int,std::string,MyKeyComparator> dicTest(3);

		for( auto &i : people ){
			if(!debug_mode) std::cout << "Testing insert(" << i.first << ", " << i.second << ")\n";
			dicTest.insert( i.first, i.second );
		}

		if(!debug_mode) std::cout << dicTest << std::endl;

		int c = 0;
		if( remove_func_test ){
			for( auto &i : people ){
				if( c++ % 2 != 0 ){
					if(!debug_mode) std::cout << "Testing remove(" << i.first << ")\n";
					dicTest.remove( i.first );
				}
			}
			if(!debug_mode) std::cout << dicTest << std::endl;
		}

		if(!debug_mode) std::cout << "Minimal Key: " << dicTest.min() << std::endl;
		{
			int _key_f = 19;
			if(!debug_mode) std::cout << _key_f << " sucessor:\n";
			int nextKey;
			bool _flag_suc = dicTest.sucessor( _key_f, nextKey );
			if( _flag_suc ){
				if(!debug_mode) std::cout << "Success! Key: ";
				if(!debug_mode) std::cout << nextKey << std::endl;
			} else {
				if(!debug_mode) std::cout << "ERROR: Key not found! (or something went wrong)\n";
			}
		}

		if(!debug_mode) std::cout << "Maximum Key: " << dicTest.max() << std::endl;
		{
			int _key_f = 12;
			if(!debug_mode) std::cout << _key_f << " predecessor:\n";
			int prevKey;
			bool _flag_suc = dicTest.predecessor( _key_f, prevKey );
			if( _flag_suc ){
				if(!debug_mode) std::cout << "Success! Key: ";
				if(!debug_mode) std::cout << prevKey << std::endl;
			} else {
				if(!debug_mode) std::cout << "ERROR: Key not found! (or something went wrong)\n";
			}
		}
	}
	/*}}}*/
	if(dsal_test){
		if(!debug_mode) std::cout << "-----------TESTING DSAL----------------------------\n";
	/* DSAL TEST {{{*/
		DSAL<int, std::string, MyKeyComparator> dicTest(3);
		for( auto &i : people ){
			if(!debug_mode) std::cout << "Testing insert(" << i.first << ", " << i.second << ")\n";
			dicTest.insert( i.first, i.second );
			// if(!debug_mode) std::cout << dicTest << std::endl;

			if(!debug_mode) std::cout << "Success!\n";
		}

		if(!debug_mode) std::cout << dicTest << std::endl;

		int c = 0;
		for( auto &i : people ){
			if( c++ % 2 == 0 ){
				if(!debug_mode) std::cout << "Testing remove(" << i.first << ")\n";
				std::string stub;
				bool status = dicTest.remove( i.first, stub );
				// if(!debug_mode) std::cout << dicTest << std::endl;
				if( status ){if(!debug_mode) std::cout << "Success!\n";}
				else{if(!debug_mode) std::cout << "ERROR: Key not found!\n";}
			}
		}
		if(!debug_mode) std::cout << dicTest << std::endl;

		if(!debug_mode) std::cout << "Minimal Key: " << dicTest.min() << std::endl;

		if(!debug_mode) std::cout << "Minimal Key sucessor: ";
		int nextKey;
		dicTest.sucessor( dicTest.min(), nextKey );
		if(!debug_mode) std::cout << nextKey << std::endl;


		if(!debug_mode) std::cout << "Maximum Key: " << dicTest.max() << std::endl;

		if(!debug_mode) std::cout << "Maximum Key Predecessor: ";
		int prevKey;
		dicTest.predecessor( dicTest.max(), prevKey );
		if(!debug_mode) std::cout << prevKey << std::endl;
	}
	/*}}}*/

	if(!debug_mode) std::cout << ">> Successful execution\n";
	return 0;
}
