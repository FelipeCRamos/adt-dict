#include <iostream>
#include "dsal.hpp"
#include "dal.hpp"

#define dal_test false
#define dsal_test true

int main(void){

	std::pair<int, std::string> people[] = {
		std::pair<int, std::string> (1, "Felipe"),
		std::pair<int, std::string> (18, "Oziel Overwritted"),
		std::pair<int, std::string> (11, "Winne"),
		// std::pair<int, std::string> (18, "Oziel"),
		std::pair<int, std::string> (12, "Amanda"),
		std::pair<int, std::string> (90, "Paulo"),
		std::pair<int, std::string> (29, "Felps"),
		std::pair<int, std::string> (19, "Max"),
		std::pair<int, std::string> (122, "Daniel")
	};

	if(dal_test){
		// DAL Test
		DAL dicTest(3);

		for( auto &i : people ){
			std::cout << "Testing insert(" << i.first << ", " << i.second << ")\n";
			dicTest.insert( i.first, i.second );
		}

		std::cout << dicTest << std::endl;

		int c = 0;
		for( auto &i : people ){
			if( c++ % 2 != 0 ){
				std::cout << "Testing remove(" << i.first << ")\n";
				dicTest.remove( i.first );
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
	if(dsal_test){
		// DSAL TEST
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
	}

	std::cout << ">> Successful execution\n";
}
