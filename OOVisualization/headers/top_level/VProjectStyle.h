/***********************************************************************************************************************
 * VProjectStyle.h
 *
 *  Created on: Feb 2, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#ifndef VPROJECTSTYLE_H_
#define VPROJECTSTYLE_H_

#include "../oovisualization_api.h"

#include "VisualizationBase/headers/items/TextStyle.h"
#include "VisualizationBase/headers/items/StaticStyle.h"
#include "VisualizationBase/headers/layouts/PanelBorderLayoutStyle.h"
#include "VisualizationBase/headers/layouts/PositionLayoutStyle.h"
#include "VisualizationBase/headers/layouts/SequentialLayoutStyle.h"

namespace OOVisualization {

class OOVISUALIZATION_API VProjectStyle : public Visualization::ItemStyle
{
	private:
		Visualization::PanelBorderLayoutStyle layout_;
		Visualization::SequentialLayoutStyle header_;
		Visualization::TextStyle name_;
		Visualization::StaticStyle icon_;
		Visualization::PositionLayoutStyle content_;

	public:
		void load(Visualization::StyleLoader& sl);

		const Visualization::PanelBorderLayoutStyle& layout() const;
		const Visualization::SequentialLayoutStyle&  header() const;
		const Visualization::TextStyle&  name() const;
		const Visualization::StaticStyle&  icon() const;
		const Visualization::PositionLayoutStyle&  content() const;
};

inline const Visualization::PanelBorderLayoutStyle& VProjectStyle::layout() const {return layout_; }
inline const Visualization::SequentialLayoutStyle& VProjectStyle::header() const {return header_; }
inline const Visualization::TextStyle& VProjectStyle::name() const {return name_; }
inline const Visualization::StaticStyle& VProjectStyle::icon() const {return icon_; }
inline const Visualization::PositionLayoutStyle& VProjectStyle::content() const {return content_; }

}

#endif /* VPROJECTSTYLE_H_ */
