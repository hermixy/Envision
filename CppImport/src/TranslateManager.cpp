#include "TranslateManager.h"

TranslateManager::TranslateManager(Model::Model* model, OOModel::Project* project) :
    model_(model), project_(project)
{
}

OOModel::Class* TranslateManager::insertClass(clang::CXXRecordDecl* rDecl)
{
    OOModel::Class* ooClass = nullptr;
    // if rdecl is not managed yet add it:
    if(!classMap_.contains(rDecl))
    {
        ooClass = new OOModel::Class();
            ooClass->setName(QString::fromStdString(rDecl->getNameAsString()));
        classMap_.insert(rDecl,ooClass);
    }
    else
        std::cout << "ERROR TRANSLATEMNGR: CLASS"<< rDecl->getNameAsString() << " ALREADY IN MAP" << std::endl;
    return ooClass;
}

OOModel::Method* TranslateManager::insertMethodDecl(clang::CXXMethodDecl* mDecl)
{
    OOModel::Method* method = nullptr;
    if(!methodMap_.contains(mDecl))
    {
        // Look if there is a function with same name in map
        QMap<clang::CXXMethodDecl*,OOModel::Method*>::iterator it = methodMap_.begin();
        for(;it!=methodMap_.end();++it)
        {
            clang::CXXMethodDecl* inMapDecl = it.key();
            if(!mDecl->getNameAsString().compare(inMapDecl->getNameAsString()) &&
                    !inMapDecl->isThisDeclarationADefinition() && mDecl->isThisDeclarationADefinition())
            {
                // found a pair with same name and only one is defined
                if((mDecl->getResultType() == inMapDecl->getResultType()) &&
                        (mDecl->param_size() == inMapDecl->param_size()))
                {
                    bool matching = true;
                    for(unsigned i = 0; i < mDecl->param_size(); i++)
                    {
                        if(mDecl->getParamDecl(i)->getType() != inMapDecl->getParamDecl(i)->getType())
                            matching = false;
                    }
                    if(matching)
                    {
                        method = it.value();
                        break;
                    }
                }
            }
        }
        // check if method node exists or else create one
        method = method ? method : addNewMethod(mDecl);
    }
    return method;
}

OOModel::Field* TranslateManager::insertField(clang::FieldDecl* fDecl)
{
    clang::CXXRecordDecl* parentClass = llvm::dyn_cast<clang::CXXRecordDecl>(fDecl->getParent());
    if(parentClass && classMap_.contains(parentClass))
    {
        OOModel::Field* field = new OOModel::Field();
        OOModel::Expression* type = CppImportUtilities::convertClangType(fDecl->getType());
        if(type) field->setTypeExpression(type);
        field->setName(QString::fromStdString(fDecl->getNameAsString()));
        classMap_.value(parentClass)->fields()->append(field);
        return field;
    }
    return nullptr;
}

OOModel::VariableDeclaration* TranslateManager::insertVar(clang::VarDecl* vDecl)
{
    OOModel::VariableDeclaration* ooVarDecl = nullptr;
    if(!varMap_.contains(vDecl))
    {
        ooVarDecl = new OOModel::VariableDeclaration();
        ooVarDecl->setName(QString::fromStdString(vDecl->getNameAsString()));
        varMap_.insert(vDecl,ooVarDecl);
    }
    else
        std::cout << "ERROR TRANSLATEMNGR: ---------->VAR : " << vDecl->getNameAsString() << " IS ALREADY IN THE MAP" << std::endl;
    return ooVarDecl;
}

OOModel::VariableDeclaration* TranslateManager::getVar(clang::VarDecl* vDecl)
{
    if(varMap_.contains(vDecl))
        return varMap_.value(vDecl);
    return nullptr;
}

OOModel::Method* TranslateManager::addNewMethod(clang::CXXMethodDecl* mDecl)
{
    // add a new method
    OOModel::Method* method = new OOModel::Method();
    method->setName(QString::fromStdString(mDecl->getNameAsString()));
    // process result type
    OOModel::Expression* restype = CppImportUtilities::convertClangType(mDecl->getResultType());
    if(restype)
    {
        OOModel::FormalResult* methodResult = new OOModel::FormalResult();
        methodResult->setTypeExpression(restype);
        method->results()->append(methodResult);
    }
    // process arguments
    clang::FunctionDecl::param_const_iterator it = mDecl->param_begin();
    for(;it != mDecl->param_end();++it)
    {
        OOModel::FormalArgument* arg = new OOModel::FormalArgument();
        arg->setName(QString::fromStdString((*it)->getNameAsString()));
        OOModel::Expression* type = CppImportUtilities::convertClangType((*it)->getType());
        if(type) arg->setTypeExpression(type);
        method->arguments()->append(arg);
    }
    // find the correct class to add the method
    if(classMap_.contains(mDecl->getParent()))
    {
        OOModel::Class* parent = classMap_.value(mDecl->getParent());
        parent->methods()->append(method);
    }
    else
        std::cout << "ERROR TRANSLATEMNGR: METHOD DECL NO PARENT FOUND" << std::endl;

    methodMap_.insert(mDecl,method);

    return method;
}
