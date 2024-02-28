#include "Objects.h"
#include "Factorys.h"
#include <map>
#include "Header.h"
#include "ObjectFactory.h"

//template<typename TBase = object>
ObjectFactory::ObjectFactory() {

	addType(1, std::make_shared<ObjectCreator<object, Line>>());
	addType(2, std::make_shared<ObjectCreator<object, Rectangle>>());
	addType(3, std::make_shared<ObjectCreator<object, Circle>>());
	addType(4, std::make_shared<ObjectCreator<object, Polyline>>());
}

//template<typename TBase>
ObjectFactory::ObjectFactory(const ObjectFactory& factory)
	: mObjects(factory.mObjects), mTypes(factory.mTypes)
{

}

ObjectFactory& ObjectFactory::operator=(const ObjectFactory& factory) {

	for (int i = 0; i != typeIds.size(); ++i) {
		mObjects.at(typeIds[i]).clear();
	}
	
	mObjects.clear();
	mTypes.clear();

	typeIds = factory.typeIds;
	mObjects = factory.mObjects;
	mTypes = factory.mTypes;

	return *this;
}

//template<typename TBase> 
ObjectFactory::~ObjectFactory() {

	for (int i = 0; i != typeIds.size(); ++i) {
		mObjects.at(typeIds[i]).clear();
	}

	mObjects.clear();
	mTypes.clear();
}

//template<typename TBase>
void ObjectFactory::addObject(const int typeId, const int objectId) {

	if (!mObjects.contains(typeId)) {

		std::map<int, std::shared_ptr<object>> pairObjectIdAndObject;
		mObjects.emplace(typeId, pairObjectIdAndObject);
		typeIds.push_back(typeId);
	}

	if (!mObjects.at(typeId).contains(objectId)) {

		std::shared_ptr<object> objPtr = createType(typeId);
		mObjects.at(typeId).emplace(objectId, objPtr);
	}
}

//template<typename TBase>
void ObjectFactory::addType(const int typeId, std::shared_ptr<Creator<object>> object) {

	if (!mTypes.contains(typeId))
		mTypes.emplace(typeId, object);
}

//template<typename TBase>
void ObjectFactory::removeType(const int typeId) {

	if (mTypes.contains(typeId))
		mTypes.erase(typeId);
}

//template<typename TBase>
void ObjectFactory::removeObject(const int typeId, const int objectId) {

	if (mObjects.at(typeId).contains(objectId));
	mObjects.erase(objectId);
}

//template<typename TBase>
std::shared_ptr<object> ObjectFactory::getObject(const int typeId, const int objectId) {

	return mObjects.at(typeId).at(objectId);
}

//template<typename TBase>
std::map<int, std::map<int, std::shared_ptr<object>>> ObjectFactory::getObjects(int typeId) {

	return mObjects;
}

//template<typename TBase>
std::shared_ptr<object> ObjectFactory::createType(int typeId) {

	auto it = mTypes.at(typeId);
	return it->create();
}