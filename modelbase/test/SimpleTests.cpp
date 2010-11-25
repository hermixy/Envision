/***********************************************************************************************************************
 * SimpleTests.cpp
 *
 *  Created on: Nov 10, 2010
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#include "modelbase.h"
#include "selftest/headers/SelfTestSuite.h"
#include "BinaryNode.h"
#include "Model.h"
#include "nodes/Text.h"

namespace Model {

TEST(ModelBase, SimpleModelCreation)
{
	Model model;
	CHECK_CONDITION( model.getRoot() == NULL );

	BinaryNode* root = dynamic_cast<BinaryNode*> (model.createRoot("BinaryNode"));
	CHECK_CONDITION( model.getRoot() == root );

	CHECK_CONDITION( root->getModel() == &model );

	CHECK_CONDITION( root->text()->getModel() == &model );
}

TEST(ModelBase, RemoveOptional)
{
	Model model;
	BinaryNode* root = dynamic_cast<BinaryNode*> (model.createRoot("BinaryNode"));

	model.beginModification(root, "Making left node");
	BinaryNode* left = root->makeLeftNode();
	model.endModification();
	CHECK_CONDITION( root->left() == left );
	CHECK_CONDITION( root->left() != NULL );


	model.beginModification(root, "Removing left node");
	root->removeLeftNode();
	model.endModification();
	CHECK_CONDITION( root->left() == NULL);


	model.beginModification(root, "Making left node");
	root->makeLeftNode();
	model.endModification();
	CHECK_CONDITION( root->left() != left );
	CHECK_CONDITION( root->left() != NULL );
}

TEST(ModelBase, ChildNodeRetrieval)
{
	Model model;
	BinaryNode* root = dynamic_cast<BinaryNode*> (model.createRoot("BinaryNode"));

	model.beginModification(root, "Making nodes");
	BinaryNode* left = root->makeLeftNode();
	BinaryNode* right = root->makeRightNode();
	model.endModification();

	CHECK_INT_EQUAL(0, root->getId());
	CHECK_INT_EQUAL(4, left->getId());
	CHECK_INT_EQUAL(8, right->getId());

	CHECK_CONDITION(root->getChild(1) == root->text());
	CHECK_CONDITION(root->getChild(4) == left);
	CHECK_CONDITION(root->getChild(8) == right);

	CHECK_CONDITION(root->hasAttribute("text"));
	CHECK_CONDITION(root->hasAttribute("left"));
	CHECK_CONDITION(root->hasAttribute("right"));

	CHECK_CONDITION(root->hasAttribute("another") == false);

	CHECK_CONDITION(root->get("text") == root->text());
	CHECK_CONDITION(root->get("left") == left);
	CHECK_CONDITION(root->get("right") == right);
}

}
