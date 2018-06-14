#ifndef _DSAL_HPP_
#define _DSAL_HPP_
#include "dal.hpp"

class DSAL : public DAL{
	public:
		/** Default constructor of DSAL class. */
		DSAL( int _MaxSz ) : DAL( _MaxSz ){ /* empty */ };
		virtual ~DSAL(){ /* Empty */ };

		/** Removes an item from the list. */
		bool remove( const Key & _x, Data & _s );

		/** Insert a item on the list. */
		bool insert( const Key & _newKey, const Data & _newInfo );

		/** Retrieves the minimal key from the dictionary. */
		Key min() const;

		/** Retrieves the maximum key from the dictionary. */
		Key max() const;

		/** Retrieves on `_y` the next key to `_x`, if exists (true) */
		bool sucessor( const Key & _x, Key & _y ) const;

		/** Retrieves on `_y` the prev key to `_x`, if exists (true) */
		bool predecessor( const Key & _x, Key & _y ) const;
	private:
		int _search( const Key & _x ) const;
};

#include "dsal.inl"
#endif
