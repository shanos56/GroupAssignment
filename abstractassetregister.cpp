#include "abstractassetregister.h"
using namespace core;

AbstractAssetRegister::AbstractAssetRegister(QObject *parent) : QObject(parent)
{

}




std::weak_ptr<AbstractAssetRegister> AbstractAssetRegister::_instance;




