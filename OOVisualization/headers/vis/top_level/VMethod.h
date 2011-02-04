/***********************************************************************************************************************
 * VMethod.h
 *
 *  Created on: Feb 4, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#ifndef VMETHOD_H_
#define VMETHOD_H_

#include "../../oovisualization_api.h"
#include "VMethodStyle.h"

#include "VisualizationBase/headers/items/ModelItem.h"
#include "VisualizationBase/headers/Styles.h"

namespace Visualization {
	class VText;
	class PanelBorderLayout;
	class SequentialLayout;
}

namespace OOModel {
	class Method;
}

namespace OOVisualization {

class VVisibility;

class OOVISUALIZATION_API VMethod : public Visualization::ModelItem
{
	ITEM_COMMON(VMethod, Visualization::ModelItem)

	public:
		VMethod(Item* parent, OOModel::Method* node, const VMethodStyle* style = Visualization::Styles::item<VMethod>("default"));
		virtual ~VMethod();

		virtual bool focusChild(FocusTarget location);

	protected:
		void determineChildren();
		void updateGeometry(int availableWidth, int availableHeight);

	private:
		Visualization::PanelBorderLayout* layout_;
		Visualization::VText* name_;
		VVisibility* visibility_;
		Visualization::SequentialLayout* header_;
		Visualization::SequentialLayout* nameContainer_;
		Visualization::SequentialLayout* content_;
		Visualization::SequentialLayout* arguments_;
		Visualization::SequentialLayout* results_;
};

}

#endif /* VMETHOD_H_ */
