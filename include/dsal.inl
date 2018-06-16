#include "dsal.hpp"

long int DSAL::_search( const Key & _x ) const{
	long int first = 0;
	long int last = this->mi_Lenght;

	while(first != last){
		long int middle = first + (last - first)/2;
		if( this->mpt_Data[middle].id == _x ){
			// if _x *is* middle
			return middle;
		}else{
			if( this->mpt_Data[middle].id > _x )
				last = middle; 			// if the _x is in smaller than middle
			else
				first = middle + 1; 	// if the _x is bigger than middle
		}
	}
	return -1;
}

size_t DSAL::where( const Key & _x ) const{
	if( this->mi_Lenght == 0 or this->mi_Capacity == 0 )
		return 0;		// error

	long int _ipos = 0;		// insert position

	/* After this for-loop, the _prev should have the bigger smallest value
	 * before the Key _x */
	for( long int i = 0; i < this->mi_Lenght; i++ ){

		if(where_debug) std::cout << "\t\ti = " << i << ", _x = " << _x
			<< ", mpt_Data[i].id = " << this->mpt_Data[i].id << "\n";

		if( _x < this->mpt_Data[i].id ){
			if(where_debug) std::cout << "\t\t\t_x < mpt_Data[i]\n";
			_ipos = i;
			break;
		} else {
			if(where_debug) std::cout << "\t\t\t_x > mpt_Data[i]\n";
			_ipos = i;
		}
	}

	if(where_debug) std::cout << "\t\t>> where() = " << _ipos << std::endl;

	return _ipos;	
}

size_t DSAL::reserve( const size_t _size, const Key & _x ){
	NodeAL * _temp = new NodeAL[_size];		// the new mpt_Data

	/* Copies all the mpt_Data to the _temp, leaving a blank space where the
	 * NodeAL element will be */

	size_t _newKeyIndex = where( _x );	// index where the _x will be 

	for( long int i = 0, ri = 0; i < this->mi_Lenght; i++ ){
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

	delete [] this->mpt_Data;

	this->mpt_Data = _temp;
	this->mi_Capacity = _size;

	return _newKeyIndex;
}

bool DSAL::remove( const Key & _x, Data & _s ){
	long int keyIndex = _search( _x );

	if( keyIndex == -1 ){
		return false;	// The key doesn't exist
	}

	NodeAL * _temp = new NodeAL[this->mi_Capacity];

	// if( keyIndex == this->mi_Lenght ) this->mi_Lenght -= 1;

	for( long int i = 0; i <= this->mi_Lenght; i++ ){
		if(debug)
			std::cout << "> mi_Capacity = " << this->mi_Capacity << std::endl;
		if( i >= keyIndex and i < this->mi_Capacity - 1 ){
			if(debug)
				std::cout << ">> _temp["<<i<<"] = mpt_Data["<< i + 1 <<"]\n";
			_temp[i].id = this->mpt_Data[i+1].id;	
			_temp[i].info = this->mpt_Data[i+1].info;	
		} else if( i < this->mi_Capacity ){
			if(debug)std::cout << ">> _temp["<<i<<"] = mpt_Data["<< i <<"]\n";
			_temp[i].id = this->mpt_Data[i].id;	
			_temp[i].info = this->mpt_Data[i].info;	
		}
	}
	if( this->mi_Lenght > 0 ){
		this->mi_Lenght -= 1;
		if(debug) std::cout << "this->mi_Lenght-- (" << mi_Lenght << ")\n";
	}

	delete [] this->mpt_Data;
	this->mpt_Data = _temp;

	return true;
}

bool DSAL::insert( const Key & _newKey, const Data & _newInfo ){
	/* Returns a index if the _newKey already exists, -1 if not */
	long int keyIndex = _search( _newKey );
	if( insert_debug ){
		std::cout << ">> keyIndex found: " << keyIndex << std::endl;
		std::cout << "\t~ Current dictionary:\n";
		std::cout << *this << std::endl;
	}


	if( keyIndex == -1 ){
		if( !(this->mi_Lenght < this->mi_Capacity) ){

			if( insert_debug ){
				std::cout << "\t> Entered on reserve() if...\n";
			}
			
			/* it means it needs more space */
			size_t ins_keyIndex = reserve( mi_Lenght + 1, _newKey );
			if( insert_debug ){
				std::cout << "\t~ Dictionary after reserve() function:\n";
				std::cout << *this << std::endl;
			}

			/* Inserts the new element on the correct position */
			this->mpt_Data[ins_keyIndex].id = _newKey;
			this->mpt_Data[ins_keyIndex].info = _newInfo;

		} else {

			if( insert_debug ){
				std::cout << "\t> Entered on reserve() ELSE...\n";
			}

			/* doesnt need more space, we just need to find where to put */
			size_t ins_keyIndex = where( _newKey );

			if( insert_debug ){
				std::cout << "\t>> where( _newKey ) = " << ins_keyIndex << "\n";
			}

			/* shift all elements after ins_keyIndex to right */
			NodeAL * _temp = new NodeAL[this->mi_Capacity];

			bool ins_flag = false; 			// control boolean for insertion

			for(
					long int i=0, ri=0;
					i < this->mi_Lenght + 1 and ri < this->mi_Capacity;
					/**/
				){
				if( i == ins_keyIndex and !ins_flag ){
					_temp[ri].id = _newKey;
					_temp[ri].info = _newInfo;
					ins_flag = true;
					ri++;
				} else {
					_temp[ri].id = mpt_Data[i].id;
					_temp[ri].info = mpt_Data[i].info;
					ri++, i++;
				}
			}

			/* _temp will be the new mpt_Data */
			delete [] this->mpt_Data;
			this->mpt_Data = _temp;

		}
		this->mi_Lenght++;
	} else {
		/* the key already exists, so we can overwrite */
		this->mpt_Data[keyIndex].id = _newKey;
		this->mpt_Data[keyIndex].info = _newInfo;
	}

	if( insert_debug ){
		std::cout << "\t~ Insert() finished, dictionary now:\n";
		std::cout << *this << std::endl;
	}

	return true;
}

DSAL::Key DSAL::min() const{
	return this->mpt_Data[0].id;
}

DSAL::Key DSAL::max() const{
	return this->mpt_Data[mi_Lenght - 1].id;
}

bool DSAL::sucessor( const Key & _x, Key & _y ) const{
	long int keyIndex = _search(_x);
	if( keyIndex + 1 < this->mi_Capacity and keyIndex != -1 ){
		_y = this->mpt_Data[keyIndex + 1].id;
		return true;
	}
	return false;
}

bool DSAL::predecessor( const Key & _x, Key & _y ) const{
	long int keyIndex = _search(_x);
	if( keyIndex - 1 >= 0 and keyIndex != -1 ){
		_y = this->mpt_Data[keyIndex - 1].id;
		return true;
	}
	return false;
}
