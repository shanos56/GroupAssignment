#include "tester.h"

Tester::Tester()
{

}

void Tester::testAbstractAsset() {
    this->_reg = AbstractAssetRegister::instance<AssetRegister>();
    QMap<QString,QVariant> value;
    value.insert("val","anything");
    qDebug() << "create factory";
    _factory = _reg->getFactory();

    qDebug() << "store first entity";
    _reg.get()->storeEntity(_factory->createCustodian(this->_reg->generateId(),value,this->_reg.get()));
    qDebug() << "store second entity";
    _reg.get()->storeEntity(_factory->createCustodian(this->_reg->generateId(),value,this->_reg.get()));

    auto ent =  _reg.get()->allEntities();

    for(auto i : ent) {
        qDebug() << i->getId();
    }




}

void Tester::testCommonEntityFactory() {

    QMap<QString,QVariant> value;
    value.insert("val","anything");
    _reg.get()->storeEntity(_factory->createCustodian(this->_reg->generateId(),value,this->_reg.get()));
     auto ent =  _reg.get()->allEntities();
    for(auto i : ent) {
        qDebug() << i->getId();
    }



}

void Tester::testCustodian() {

    this->_custodian.reset(new Custodian(_reg->generateId(),_reg.get()));
    qDebug() << "save name";
    auto  definit = std::make_shared<UserPropertyDefinition> (_reg->generateId(),_custodian.get());
    qDebug() << "make prop";
    auto  prop = std::make_shared<TypedUserProperty<QString> >(_reg->generateId(),definit);
    qDebug() << "set value";

    prop->setValue(QString("Random name"));
    qDebug() << "set name";

    qDebug()<< prop.get()->value();
    if (_custodian->setName(prop) ) {
        qDebug() << "success";
    }
    qDebug() << "name saved";
    qDebug()<< _custodian.get()->getName();
}

void Tester::testCustodianPhone () {
    std::shared_ptr<UserPropertyDefinition> definit (new UserPropertyDefinition(_reg->generateId(),_custodian.get()));

    qDebug() << "add validator";
    definit->addValidator("Phone",std::shared_ptr<UserPropertyValidator>(new PhoneNumberValidator ()));
    qDebug() << "create phone number";
    std::shared_ptr<TypedUserProperty<QString>> phone(new  TypedUserProperty<QString>(_reg->generateId(),definit));

    qDebug() << "set value";
    phone->setValue(QString("+09435803 48"));


    qDebug() << "validate value";
    if (phone->validate()) {
        _custodian->setPhoneNumber(phone);
        qDebug() << "success";
    } else {

        qDebug() << phone->getErrorMessage();
    }
}


void Tester::testCustodianDepartment () {
    qDebug() << "saving department";
    std::shared_ptr<UserPropertyDefinition> definit (new UserPropertyDefinition(_reg->generateId(),_custodian.get()));
    qDebug() << "saving department";
    definit->addValidator("Department",std::shared_ptr<UserPropertyValidator>(new DepartmentValidator ()));
     std::shared_ptr<TypedUserProperty<QString>> department(new  TypedUserProperty<QString>(_reg->generateId(),definit));

     qDebug() << "saving department 2";
     department->setValue(QString("Operations"));

    qDebug() << "department saved";
    if (department->validate()) {
        _custodian->setDepartment(department);
        qDebug() << "success";
    } else {
      qDebug() << department->getErrorMessage();
    }



}


void Tester::testAsset() {
    qDebug() << "\n/////////////////////////////////";
    qDebug() << "Test Asset";
    qDebug() << "//////////////////////////////";
    qDebug() << "create instance";
    this->_asset.reset(new Asset(_reg->generateId(),_reg.get()));
    qDebug() << "save model";
    this->_asset->setModel("ModelTest");
    qDebug() << "Model name" << this->_asset->getModel();
    qDebug() << "add to register";
    _reg->storeEntity(this->_asset);

    qDebug() << "id: "<< this->_asset->getId();
    qDebug() << "reset asset";
    this->_asset.reset();
    qDebug() << "loop entities";
    auto re = _reg->allEntities();
    for(auto i : re) {
        qDebug() << i.get()->getId();
    }
    qDebug() << "create asset type";
    auto assetType = _reg->getFactory()->createAssetType(_reg->generateId());
    qDebug() << "create asset";
    _asset.reset();
    _asset = _reg->getFactory()->createAsset(assetType,_reg->generateId());
    qDebug() << "store asset";
    _reg->storeEntity(_asset);

    _asset = _reg->getFactory()->createAsset(assetType,_reg->generateId());
    qDebug() << "store asset";
    _reg->storeEntity(_asset);




}

