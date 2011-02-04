/***********************************************************************************************************************
 * TypedList.h
 *
 *  Created on: Jan 28, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#ifndef TYPEDLIST_H_
#define TYPEDLIST_H_

#include "List.h"

namespace Model {

template <class T>
class TypedList: public List
{
	NODE_DECLARE_STANDARD_METHODS(TypedList)

	public:
		T* first();
		T* last();
		T* at(int i);
};

}

#endif /* TYPEDLIST_H_ */