#ifndef TESTER_H
#define TESTER_H

#include "abstractassetregister.h"
#include "assetregister.h"

class Tester
{
    std::shared_ptr<AbstractEntityFactory> _factory;
    std::shared_ptr<AbstractAssetRegister> _reg;
    std::shared_ptr<Custodian> _custodian;
    std::shared_ptr<Asset> _asset;
public:
    Tester();

    void testAbstractAsset();
    void testCommonEntityFactory();
    void testCustodian();
    void testCustodianPhone ();
    void testCustodianDepartment ();
    void testAsset();

};

#endif // TESTER_H
