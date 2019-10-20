#include "asset.h"
using namespace core;

Asset::Asset(QString id, QObject *parent)
{
    this->setParent(parent);
    this->id = id;
}
