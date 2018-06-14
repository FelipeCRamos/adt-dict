#include "dal.hpp"

DAL::DAL( int _MaxSz ){
	this->mi_Lenght = 0;
	this->mi_Capacity = _MaxSz;
	this->mpt_Data = new NodeAL[_MaxSz];
}

/** Inside function, to check if already has a Key `_x` */
int DAL::_search( const Key & _x ) const{
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

bool DAL::search( const Key & _x, Data & _s ) const{
	for( int i = 0; i < this->mi_Capacity; i++ ){
		if( _x == this->mpt_Data[i].id ){
			_s = mpt_Data[i].info;
			return true;
		}
	}
	return false;
}

bool DAL::insert( const Key & _newKey, const Data & _newInfo ){
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
		this->mpt_Data[keyIndex].id = _newKey;
		this->mpt_Data[keyIndex].info = _newInfo;
	}

	return true;	// stub
}

bool DAL::remove( const Key & _x ){		// Why Data & _s?
	int keyIndex = _search( _x );
	if(debug) std::cout << "_search( _x ) = " << keyIndex << std::endl;

	if( keyIndex == -1 or mi_Capacity == 0 )
		return false;

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

bool DAL::reserve( size_t _sizeNeeded ){
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

DAL::Key DAL::min() const{
	Key _min = this->mpt_Data[0].id;
	for( int i = 1; i < mi_Capacity; i++ ){
		if( _min > mpt_Data[i].id ){
			_min = mpt_Data[i].id;
		}
	}
	return _min;
}

DAL::Key DAL::max() const{
	Key _max= this->mpt_Data[0].id;
	for( int i = 1; i < mi_Capacity; i++ ){
		if( _max < mpt_Data[i].id ){
			_max = mpt_Data[i].id;
		}
	}
	return _max;
}

bool DAL::sucessor( const Key & _x, Key &_y ) const{
	int keyIndex = _search( _x );
	if( keyIndex == -1 ) return false;
	if( keyIndex + 1 < mi_Capacity ){
		_y = this->mpt_Data[keyIndex+1].id;
		return true;
	}
	return false;
}

bool DAL::predecessor( const Key & _x, Key &_y ) const{
	int keyIndex = _search( _x );
	if( keyIndex == -1 ) return false;
	if( keyIndex - 1 >= 0 ){
		_y = this->mpt_Data[keyIndex-1].id;
		return true;
	}
	return false;
}
