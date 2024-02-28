#ifndef __DATABASE_H_
#define __DATABASE_H_

#include <map>
#include "Header.h"
#include <vector>
#include <iostream>
#include "Objects.h"

struct PROJECT_EXPORT DataBase {

	DataBase(int count = 0) : countOfObjects(count) {

	}

	~DataBase() {

	}

	void addType(const int typeId) {

		std::map<int, std::shared_ptr<object>> pairObjectIdAndObject;
		objects.emplace(typeId, pairObjectIdAndObject);
		std::vector<int> objectIds;
		typeAndObjectIds.emplace(typeId, objectIds);
		typeIds.push_back(typeId);
	}

	void addObject(const int typeId, const int objectId, std::shared_ptr<object> obj) {

		objects.at(typeId).emplace(objectId, obj);
		typeAndObjectIds.at(typeId).push_back(objectId);
	}


	std::map<int, std::vector<int>> typeAndObjectIds;
	std::vector<int> typeIds;
	int countOfObjects;
	std::map<int, std::map<int, std::shared_ptr<object>>> objects;
};

#endif __DATABASE_H_
