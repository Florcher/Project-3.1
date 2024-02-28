#ifndef __OBJECTFACTORY_H_
#define __OBJECTFACTORY_H_
#include "Objects.h"
#include <map>
#include "Header.h"
#include "Factorys.h"
#include <vector>

//template<typename TBase = object>
class PROJECT_EXPORT ObjectFactory {
public:

	ObjectFactory();
	ObjectFactory(const ObjectFactory& factory);
	ObjectFactory& operator=(const ObjectFactory& factory);

	~ObjectFactory();

	void addObject(const int typeId, const int objectId);
	void addType(const int typeId, std::shared_ptr<Creator<object>> object);

	void removeType(const int typeId);
	void removeObject(const int typeId, const int objectId);

	std::shared_ptr<object> getObject(const int typeId, const int objectId);
	std::map<int, std::map<int, std::shared_ptr<object>>> getObjects(int typeId);

private:

	std::map<int, std::map<int, std::shared_ptr<object>>> mObjects;
	std::map<int, std::shared_ptr<Creator<object>>> mTypes;
	std::vector<int> typeIds;


	std::shared_ptr<object> createType(int typeId);
};

#endif __OBJECTFACTORY_H_
