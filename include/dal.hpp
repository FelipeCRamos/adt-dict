#ifndef _DAL_HPP_
#define _DAL_HPP_
#define debug false
#include <iostream>
#include <string>

class DAL{
	protected:
		using Key = int;			// Key alias
		// typedef int Key;
		using Data = std::string;	// Data Alias
		struct NodeAL{				// Node alias, containing the pair key-data
			Key id;
			Data info;
			NodeAL(Key _id = Key(), Data _info = Data()): id(_id), info(_info){};
		};

		static const int SIZE=50;	// Default size of the list
		int mi_Lenght;				// Actual size of the list
		int mi_Capacity;			// Actual capacity of the list
		NodeAL *mpt_Data;			// Data vector, dinamically allocated

		int _search( const Key & _x ) const;	// Auxiliar search method

	public:
		/** Default constructor of DAL class. */
		DAL( int _MaxSz = SIZE );
		virtual ~DAL(){ if(mpt_Data) delete [] mpt_Data; };

		/** Removes an item from the list. */
		bool remove( const Key & _x );

		/** Search for an item in the list. */
		bool search( const Key & _x, Data & _s ) const;

		/** Insert an item on the list. */
		bool insert( const Key & _newKey, const Data & _newInfo );

		/** Reserve _sizeNeeded elements */
		bool reserve( size_t _sizeNeeded );

		/** Retrieves the minimal key from the dictionary */
		Key min() const;

		/** Retrieves the maximum key from the dictionary */
		Key max() const;

		/** Retrieves on `_y` the next key to `_x`, if exists (true) */
		bool sucessor( const Key & _x, Key & _y ) const;

		/** Retrieves on `_y` the prev key to `_x`, if exists (true) */
		bool predecessor( const Key & _x, Key & _y ) const;

		// sends back to the output stream an ASCII representation for the list
		inline friend
			std::ostream &operator<<( std::ostream & _os, const DAL & _oList ){
				_os << "[\n";
				for( int i = 0; i < _oList.mi_Lenght; i++ ){
					_os << "\t{" << _oList.mpt_Data[i].id << ",\t'"
						<< _oList.mpt_Data[i].info << "'}\n";
				}
				_os << "]";
				return _os;
			}
};

#include "dal.inl"
#endif
