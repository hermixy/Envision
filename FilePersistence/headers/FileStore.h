/***********************************************************************************************************************
 * FileStore.h
 *
 *  Created on: Dec 2, 2010
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#ifndef FILESTORE_H_
#define FILESTORE_H_

#include "filepersistence_api.h"

#include "ModelBase/headers/PersistentStore.h"

#include <QtXml/QDomDocument>
#include <QtCore/QDir>
#include <QtCore/QMutex>

namespace FilePersistence {

class FILEPERSISTENCE_API FileStore: public Model::PersistentStore
{
	private:

		/** The folder where all models are stored. Each model is a separate sub folder in the base folder. */
		QDir baseFolder;

		/** A mutex that assures exclusive model saving and loading operations. */
		QMutex storeAccess;

		/** A flag that indicates if the store is currently in the middle of saving or loading a model. */
		bool working;

		/**
		 * This is the folder where the current model is being saved to or loaded from. This is only valid if working is
		 * true.
		 */
		QDir modelDir;

		/**
		 * This is the XML DOM document that corresponds to the current persistence unit that is being saved or loaded. Note
		 * that this changes every time when a new persistence unit is saved/loaded.
		 */
		QDomDocument* currentDoc;

		/**
		 * This is the parent element where all other saved/load elements and text should go. This changes every time a
		 * new node is saved or loaded.
		 */
		QDomElement* currentParent;

		void saveNewPersistenceUnit(const Model::Node *node, const QString &name, bool partialLoadHint);
		Model::LoadedNode loadNewPersistenceUnit(const QString& name, Model::Node* parent);
		Model::LoadedNode loadNode(QDomElement& nodeElement, Model::Node* parent);

		/**
		 * When started with -1 it searches through the entire tree. Otherwise expects to find before or at the specified
		 * depth. Depth = 0 checks just the root element.
		 */
		QDomElement* findElementById(QDomElement* root, const QString& id, int depthLimit);
		void checkIsWorking();

	public:
		FileStore();
		virtual ~FileStore();

		void setBaseFolder(const QString& baseFolder);

		// Methods from Persistent Store
		virtual void saveModel(Model::Model& model, const QString &name);

		virtual void saveStringValue(const QString &value);
		virtual void saveIntValue(int value);
		virtual void saveFloatValue(double value);
		virtual void saveNode(const Model::Node *node, const QString &name, bool partialLoadHint);

		virtual Model::Node* loadRootNode(const QString &name);
		virtual QList<Model::LoadedNode> loadAllSubNodes(Model::Node* parent);
		virtual Model::Node* loadSubNode(Model::Node* parent, const QString& name);
		virtual QList<Model::LoadedNode> loadPartialNode(Model::Node* partialNode);
		virtual int loadIntValue();
		virtual QString loadStringValue();
		virtual double loadFloatValue();
};

}

#endif /* FILESTORE_H_ */
