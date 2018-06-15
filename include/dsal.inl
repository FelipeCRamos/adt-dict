#include "dsal.hpp"

int DSAL::_search( const Key & _x ) const{
	// TODO: Binary search
	if( mi_Capacity == 0 ){
		return -1;
	}

	for( int i = 0; i < this->mi_Capacity; i++ ){
		if( _x == mpt_Data[i].id ){
			return i;
		}
	}	
	return -1;
}

size_t DSAL::where( const Key & _x, const bool _flag ) const{
	if( mi_Lenght == 0 or mi_Capacity == 0 ) return 0;		// error

	size_t maxi = 0;

	std::pair<size_t, Key> _prev( 0, this->mpt_Data[0].id );
	if( mi_Lenght == 1 ){
		if( mpt_Data[0].id > _x ){
			_prev.first = 0;
		} else {
			_prev.first = 1;
		}
	} else {
		/* After this for-loop, the _prev should have the bigger smallest value
		 * before the Key _x */
		for( int i = 0; i < mi_Capacity; i++ ){
			if( _x > mpt_Data[i].id ){
				maxi++;
				_prev.first = i;
			} else {
				_prev.first += 1;
				break;
			}
		}
	}
	if( maxi == mi_Lenght ){
		_prev.first = mi_Lenght;
	}

	return _prev.first;	
}

size_t DSAL::reserve( const size_t _size, const Key & _x ){
	NodeAL * _temp = new NodeAL[_size];		// the new mpt_Data

	/* Copies all the mpt_Data to the _temp, leaving a blank space where the
	 * NodeAL element will be */

	size_t _newKeyIndex = where( _x, true );	// index where the _x will be 

	for( int i = 0, ri = 0; i < mi_Capacity; i++ ){
		if( i != _newKeyIndex ){
			_temp[ri].id = this->mpt_Data[i].id;
			_temp[ri].info = this->mpt_Data[i].info;
			ri += 1;
		} else {
			ri += 1;	// Leaves a blank space 

			/* put the current i on the next space */
			_temp[ri].id = this->mpt_Data[i].id;
			_temp[ri].info = this->mpt_Data[i].info;
			ri += 1;	// update the ri
		}
	}

	delete [] mpt_Data;

	this->mpt_Data = _temp;
	this->mi_Capacity = _size;

	return _newKeyIndex;
}

bool DSAL::remove( const Key & _x, Data & _s ){
	// TODO
	return true;	// stub
}

bool DSAL::insert( const Key & _newKey, const Data & _newInfo ){
	int keyIndex = _search( _newKey );
	// //std::cout << ">> insert_debug: entered, _search(" << _newKey << ")="
		// << keyIndex << std::endl;
	if( keyIndex == -1 ){
		if( !(mi_Lenght < mi_Capacity) ){
			/* it means it needs more space */
			size_t ins_keyIndex = reserve( mi_Lenght + 1, _newKey );

			/* Inserts the new element on the correct position */
			this->mpt_Data[ins_keyIndex].id = _newKey;
			this->mpt_Data[ins_keyIndex].info = _newInfo;

		} else {

			/* doesnt need more space, we just need to find where to put */
			size_t ins_keyIndex = where( _newKey, false );


			/* shift all elements after ins_keyIndex to right */
			NodeAL * _temp = new NodeAL[mi_Capacity];

			bool ins_flag = false; 			// control boolean for insertion

			for(int i=0, ri=0; i < mi_Lenght+1 and ri < mi_Capacity; /**/){
				if( i == ins_keyIndex and !ins_flag ){
					ins_flag = true;
					_temp[ri].id = _newKey;
					_temp[ri].info = _newInfo;
					ri++;
				} else {
					_temp[ri].id = mpt_Data[i].id;
					_temp[ri].info = mpt_Data[i].info;
					ri++, i++;
				}
			}

			/* _temp will be the new mpt_Data */
			delete [] mpt_Data;
			this->mpt_Data = _temp;

		}
		this->mi_Lenght++;
	} else {
		/* the key already exists, so we can overwrite */
		this->mpt_Data[keyIndex].id = _newKey;
		this->mpt_Data[keyIndex].info = _newInfo;
	}

	return true;	// stub
}

DSAL::Key DSAL::min() const{
	return this->mpt_Data[0].id;
}

DSAL::Key DSAL::max() const{
	return this->mpt_Data[mi_Lenght].id;
}

bool DSAL::sucessor( const Key & _x, Key & _y ) const{
	int keyIndex = _search(_x);
	if( keyIndex + 1 < mi_Capacity and keyIndex != -1 ){
		_y = this->mpt_Data[keyIndex + 1].id;
		return true;
	}
	return false;
}

bool DSAL::predecessor( const Key & _x, Key & _y ) const{
	int keyIndex = _search(_x);
	if( keyIndex - 1 >= 0 and keyIndex != -1 ){
		_y = this->mpt_Data[keyIndex + 1].id;
		return true;
	}
	return false;
}
