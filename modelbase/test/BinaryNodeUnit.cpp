/***********************************************************************************************************************
 * BinaryNodeUnit.cpp
 *
 *  Created on: Nov 25, 2010
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#include "BinaryNodeUnit.h"

namespace Model {

NODE_DEFINE_EMPTY_CONSTRUCTORS(BinaryNodeUnit, BinaryNode )
NODE_DEFINE_TYPE_REGISTRATION_METHODS(BinaryNodeUnit)

void BinaryNodeUnit::init()
{
	registerNodeConstructors();
}

NodeReadWriteLock* BinaryNodeUnit::getAccessLock() const
{
	return & (const_cast<BinaryNodeUnit*> (this) )->accessLock;
}

}
