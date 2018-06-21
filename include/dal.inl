#include "dal.hpp"
// template <class Key, class Data, class KeyComparator>
// DAL<Key, Data, KeyComparator>::DAL( void ){
	// this->mi_Lenght = 0;
	// this->mi_Capacity = 50;
	// this->mpt_Data = new NodeAL[this->mi_Capacity];
// }

template <class Key, class Data, class KeyComparator>
DAL<Key, Data, KeyComparator>::DAL( int _MaxSz ){
	this->mi_Lenght = 0;
	this->mi_Capacity = _MaxSz;
	this->mpt_Data = new NodeAL[this->mi_Capacity];
}

/** Inside function, to check if already has a Key `_x` */
template <class Key, class Data, class KeyComparator>
int DAL<Key, Data, KeyComparator>::_search( const Key & _x ) const{
	if(debug){
		std::cout << ">> Inside _search(" << _x << "): ";
		std::cout << "mi_Capacity = " << mi_Capacity << "\n";
	}

	for( int i = 0; i < this->mi_Capacity; i++ ){
		if(debug)
			std::cout << "\tmpt_Data[i].id = " << mpt_Data[i].id << std::endl;
		if( _x == mpt_Data[i].id ){
			if(debug) std::cout << "\t\t>> FOUND! ( " << i << " )\n";
			return i;
		}
	}	
	return -1;
}

template <class Key, class Data, class KeyComparator>
bool DAL<Key, Data, KeyComparator>::search( const Key & _x, Data & _s ) const{
	for( int i = 0; i < this->mi_Capacity; i++ ){
		if( _x == this->mpt_Data[i].id ){
			_s = mpt_Data[i].info;
			return true;
		}
	}
	return false;
}

template <class Key, class Data, class KeyComparator>
bool DAL<Key, Data, KeyComparator>::insert( const Key & _newKey, const Data & _newInfo ){
	// search for a key, if exists: substitute
	int keyIndex = _search( _newKey );	// returns -1 if already exists
	
	if( keyIndex == -1 ){
		// Check if has space for another key
		if( !(mi_Lenght < mi_Capacity) ){
			reserve( mi_Lenght + 1 );
		}
		this->mpt_Data[mi_Lenght].id = _newKey;
		this->mpt_Data[mi_Lenght].info = _newInfo;
		mi_Lenght++;

	} else {
		// it means that the key is already on the mpt_Data
		return false;
		// this->mpt_Data[keyIndex].id = _newKey;
		// this->mpt_Data[keyIndex].info = _newInfo;
	}

	return true;	// stub
}

template <class Key, class Data, class KeyComparator>
bool DAL<Key, Data, KeyComparator>::remove( const Key & _x, Data & _s ){		// Why Data & _s?
	int keyIndex = _search( _x );
	if(debug) std::cout << "_search( _x ) = " << keyIndex << std::endl;

	if( keyIndex == -1 or mi_Capacity == 0 )
		return false;

	_s = this->mpt_Data[keyIndex].info;
	NodeAL * _temp = new NodeAL[this->mi_Capacity-1];
	int _tempIndex = 0;

	for( int i = 0; i < this->mi_Capacity; i++ ){
		if( mpt_Data[i].id == _x ){
		}
		else{
			_temp[_tempIndex].id = mpt_Data[i].id;
			_temp[_tempIndex].info = mpt_Data[i].info;
			_tempIndex++;
		}
	}
	delete [] this->mpt_Data;
	this->mpt_Data = _temp;

	mi_Capacity--;
	mi_Lenght--;

	return true;
}

template <class Key, class Data, class KeyComparator>
bool DAL<Key, Data, KeyComparator>::reserve( size_t _sizeNeeded ){
	if(debug){
		std::cout << "Entered on reserve(" << _sizeNeeded << ")\n";
	}

	NodeAL * _temp = new NodeAL[_sizeNeeded];	
	
	for( int i = 0; i < mi_Capacity; i++ ){
		_temp[i].id = this->mpt_Data[i].id;
		_temp[i].info = this->mpt_Data[i].info;
	}

	delete [] mpt_Data;
	this->mpt_Data = _temp;
	
	this->mi_Capacity = _sizeNeeded;
	return true;
}

template <class Key, class Data, class KeyComparator>
Key DAL<Key, Data, KeyComparator>::min() const{
	if( this->mi_Lenght == 0 ){
		throw std::out_of_range("ERROR: Dictionary is empty!\n");
	}

	Key _min = this->mpt_Data[0].id;
	for( int i = 1; i < this->mi_Lenght; i++ ){
		if( _min > mpt_Data[i].id ){
			_min = mpt_Data[i].id;
		}
	}
	return _min;
}

template <class Key, class Data, class KeyComparator>
Key DAL<Key, Data, KeyComparator>::max() const{
	if( this->mi_Lenght == 0 ){
		throw std::out_of_range("ERROR: Dictionary is empty!\n");
	}
	Key _max= this->mpt_Data[0].id;
	for( int i = 1; i < this->mi_Lenght; i++ ){
		if( _max < mpt_Data[i].id ){
			_max = mpt_Data[i].id;
		}
	}
	return _max;
}

template <class Key, class Data, class KeyComparator>
bool DAL<Key, Data, KeyComparator>::successor( const Key & _x, Key &_y ) const{
	int keyIndex = _search( _x );		// discover current index of the key

	/* Optimizations */
	if( keyIndex == -1 ) 			return false;	// it's not even a key
	if( keyIndex + 1 == mi_Lenght )	return false;	// it's the last element
	if( _x == max() ) 				return false;	// it's already the maximum
	if( keyIndex + 1 == mi_Lenght and this->mpt_Data[mi_Lenght-1].id > _x ){
		_y = this->mpt_Data[keyIndex+1].id;
	} else if ( keyIndex + 1 == mi_Lenght ){
		return false;
	}

	/* Begin the real search for the next key */
	/* Basically, get the minimal in the range (keyIndex, mi_Lenght] */

	Key _buf = this->mpt_Data[keyIndex+1].id;
	bool flag_tripped = true;

	for( long int i = 0; i < mi_Lenght; i++ ){
		bool _min_max = (this->mpt_Data[i].id < _buf or flag_tripped);
		if( this->mpt_Data[i].id > _x and _min_max ){
			flag_tripped = false;
			_buf = this->mpt_Data[i].id;
		}
	}
	_y = _buf;
	return true;
}

template <class Key, class Data, class KeyComparator>
bool DAL<Key, Data, KeyComparator>::predecessor( const Key & _x, Key &_y ) const{
	int keyIndex = _search( _x );
	if(debug)
		std::cout << ">> keyIndex = " << keyIndex << std::endl;

	if( _x == min() )			return false;	// it's the min() element

	Key _buf = this->mpt_Data[keyIndex-1].id;
	bool flag_tripped = true;
	
	for( long int i = mi_Lenght-1; i >= 0; i-- ){
		bool _max_min = (this->mpt_Data[i].id > _buf or flag_tripped);
		if( this->mpt_Data[i].id < _x and _max_min ){
			flag_tripped = false;
			_buf = this->mpt_Data[i].id;
		}
	}
	_y = _buf;
	return true;
}
