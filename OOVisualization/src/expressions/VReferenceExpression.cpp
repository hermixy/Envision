/***********************************************************************************************************************
 * VReferenceExpression.cpp
 *
 *  Created on: Feb 8, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#include "expressions/VReferenceExpression.h"

#include "VisualizationBase/headers/items/Text.h"
#include "VisualizationBase/headers/items/Symbol.h"

using namespace Visualization;
using namespace OOModel;

namespace OOVisualization {

ITEM_COMMON_DEFINITIONS(VReferenceExpression, "item")

VReferenceExpression::VReferenceExpression(Item* parent, NodeType* node, const StyleType* style) :
	ItemWithNode<LayoutProvider<>, ReferenceExpression>(parent, node, style),
	name_(new Text(NULL, &style->name()) ),
	separator_(NULL),
	prefix_(NULL)
{
	layout()->append(name_);
}

VReferenceExpression::~VReferenceExpression()
{
	// These were automatically deleted by LayoutProvider's destructor
	name_ = NULL;
	separator_ = NULL;
	prefix_ = NULL;
}

void VReferenceExpression::determineChildren()
{
	layout()->synchronizeFirst(prefix_, node()->prefix());
	layout()->synchronizeMid(separator_, node()->prefix() != NULL, &style()->separator(), 1);

	// TODO: find a better way and place to determine the style of children. Is doing this causing too many updates?
	// TODO: consider the performance of this. Possibly introduce a style updated boolean for all items so that they know
	//			what's the reason they are being updated.
	// The style needs to be updated every time since if our own style changes, so will that of the children.
	layout()->setStyle( &style()->layout());
	name_->setStyle( &style()->name());
	if (prefix_) separator_->setStyle( &style()->separator());

	name_->setText(node()->ref()->path().split(',').last().split(':').last());
}

}
