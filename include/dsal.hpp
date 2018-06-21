#ifndef _DSAL_HPP_
#define _DSAL_HPP_

#include "dal.hpp"

#define insert_debug false
#define where_debug false
#define reserve_debug false

template <class Key, class Data, class KeyComparator = std::less<int>>
class DSAL : public DAL<Key, Data, KeyComparator>{

		// using Key = int;
		using NodeAL = typename DAL<Key, Data, KeyComparator>::NodeAL;

	public:
		/** Default constructor of DSAL class. */
		// DSAL( void ) : DAL<Key, Data, KeyComparator>( void ){  };

		DSAL( int _MaxSz = DAL<Key, Data, KeyComparator>::SIZE ) : DAL<Key, Data, KeyComparator>( _MaxSz ){};
		virtual ~DSAL(){ /* Empty */ };

		/** Removes an item from the list. */
		bool remove( const Key & _x, Data & _s );

		/** Insert a item on the list. */
		bool insert( const Key & _newKey, const Data & _newInfo );

		/** Retrieves the minimal key from the dictionary. */
		Key min() const;

		/** Retrieves the maximum key from the dictionary. */
		Key max() const;

		/** Retrieves on `_y` the next key to `_x`, if exists (true). */
		bool successor( const Key & _x, Key & _y ) const;

		/** Retrieves on `_y` the prev key to `_x`, if exists (true). */
		bool predecessor( const Key & _x, Key & _y ) const;

		/** Discover the index of the Key & _x (if exists), returns -1 otherwise. */
		long int _search( const Key & _x ) const;

	private:
		/** Returns where the Key & _x should be inserted. */
		size_t where( const Key & _x ) const;

		/** Increase the array mpt_Data size by _size, and find an index for
		 * `_key` to be, leaving a blank space on there. 
		 * \return	The recommended index for `_key` to be inserted */
		size_t reserve( const size_t _size, const Key & _x );
};

#include "dsal.inl"
#endif
