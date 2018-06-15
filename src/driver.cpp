#include <iostream>
#include "dsal.hpp"
#include "dal.hpp"

#define dal_test true 
#define dsal_test false
#define remove_func_test false

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
	/* DAL TEST {{{*/
		DAL dicTest(3);
		std::cout << "Testing DAL\n";

		for( auto &i : people ){
			std::cout << "Testing insert(" << i.first << ", " << i.second << ")\n";
			dicTest.insert( i.first, i.second );
		}

		std::cout << dicTest << std::endl;

		int c = 0;
		if( remove_func_test ){
			for( auto &i : people ){
				if( c++ % 2 != 0 ){
					std::cout << "Testing remove(" << i.first << ")\n";
					dicTest.remove( i.first );
				}
			}
			std::cout << dicTest << std::endl;
		}

		std::cout << "Minimal Key: " << dicTest.min() << std::endl;
		{
			int _key_f = 90;
			std::cout << _key_f << " sucessor:\n";
			int nextKey;
			bool _flag_suc = dicTest.sucessor( _key_f, nextKey );
			if( _flag_suc ){
				std::cout << "Success! Key: ";
				std::cout << nextKey << std::endl;
			} else {
				std::cout << "ERROR: Key not found! (or something went wrong)\n";
			}
		}

		std::cout << "Maximum Key: " << dicTest.max() << std::endl;
		{
			int _key_f = 122;
			std::cout << _key_f << " predecessor:\n";
			int prevKey;
			bool _flag_suc = dicTest.predecessor( _key_f, prevKey );
			if( _flag_suc ){
				std::cout << "Success! Key: ";
				std::cout << prevKey << std::endl;
			} else {
				std::cout << "ERROR: Key not found! (or something went wrong)\n";
			}
		}

		// std::cout << "Maximum Key: " << dicTest.max() << std::endl;
//
		// std::cout << "Maximum Key Predecessor: ";
		// int prevKey;
		// dicTest.predecessor( dicTest.max(), prevKey );
		// std::cout << prevKey << std::endl;
	}
	/*}}}*/
	if(dsal_test){
	/* DSAL TEST {{{*/
		DSAL dicTest(3);
		for( auto &i : people ){
			std::cout << "Testing insert(" << i.first << ", " << i.second << ")\n";
			dicTest.insert( i.first, i.second );
			// std::cout << dicTest << std::endl;

			std::cout << "Success!\n";
		}

		std::cout << dicTest << std::endl;

		int c = 0;
		for( auto &i : people ){
			if( c++ % 2 == 0 ){
				std::cout << "Testing remove(" << i.first << ")\n";
				std::string stub;
				bool status = dicTest.remove( i.first, stub );
				// std::cout << dicTest << std::endl;
				if( status ) std::cout << "Success!\n";
				else std::cout << "ERROR: Key not found!\n";
			}
		}
		std::cout << dicTest << std::endl;

		std::cout << "Minimal Key: " << dicTest.min() << std::endl;

		std::cout << "Minimal Key sucessor: ";
		int nextKey;
		dicTest.sucessor( dicTest.min(), nextKey );
		std::cout << nextKey << std::endl;


		std::cout << "Maximum Key: " << dicTest.max() << std::endl;

		std::cout << "Maximum Key Predecessor: ";
		int prevKey;
		dicTest.predecessor( dicTest.max(), prevKey );
		std::cout << prevKey << std::endl;
	}
	/*}}}*/

	std::cout << ">> Successful execution\n";
	return 0;
}
