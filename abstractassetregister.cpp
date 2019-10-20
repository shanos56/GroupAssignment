#include "abstractassetregister.h"
using namespace core;
AbstractAssetRegister::AbstractAssetRegister(QObject *parent) : QObject(parent)
{

}
template<class T>
std::shared_ptr<T>  AbstractAssetRegister::instance() {
    if (_instance.get() == nullptr)
        _intance(new T());

    return _instance;
}


