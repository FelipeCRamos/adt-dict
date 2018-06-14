#include <iostream>
#include "dsal.hpp"
#include "dal.hpp"

int main(void){
	// Constructor test
	DAL dicTest(3);

	std::pair<int, std::string> people[] = {
		std::pair<int, std::string> (1, "Felipe"),
		std::pair<int, std::string> (11, "Winne"),
		std::pair<int, std::string> (12, "Amanda"),
		std::pair<int, std::string> (13, "Paulo"),
		std::pair<int, std::string> (19, "Max"),
		std::pair<int, std::string> (122, "Daniel"),
		std::pair<int, std::string> (64, "Oziel"),
		std::pair<int, std::string> (29, "Felps"),
		std::pair<int, std::string> (64, "Oziel Overwritted")
	};

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

	std::cout << ">> Successful execution\n";
}
