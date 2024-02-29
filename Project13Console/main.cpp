#include "Input.h"
#include "Output.h"
#include "ObjectFactory.h"
#include "Vector2D.h"

struct OperationWithDataBase {

};

struct BaseOperationWithObject {

	virtual void editId(const int id);
	virtual void editName(const std::string& name);
	virtual void remove();
};

struct OperationWithLine : BaseOperationWithObject {

	OperationWithLine(std::shared_ptr<object> obj) {

	};

	void editStartPoint(const vector2D& point) {
		
	}
	void editEndPoint(const vector2D& point);

	std::shared_ptr<Line> line;
};

struct OpertationWithRectangle : BaseOperationWithObject {

	void editLeftDownPoint(const vector2D& point);
	void editLenth(const double lenth);
	void editWidth(const double width);
};

struct OpertationWithCircle : BaseOperationWithObject {

	void editCenter(const vector2D point);
	void editRadius(const double radius);
};

struct OperationWithPolyline : BaseOperationWithObject {

};




std::shared_ptr<DataBase> loadDb(const std::string& filename) {

	Input in;
	return in.input(filename);
}

void saveDb(std::shared_ptr<DataBase> db, const std::string& filename) {

	Output out;
	out.output(db, filename);
}

//std::shared_ptr<object> createEntity(const int typeId, const int objectId, const std::string& name) {
//
//	ObjectFactory factory;
//	auto obj = factory.getObject(typeId);
//	obj->setName(name);
//	obj->setId(objectId);
//	return obj;
//}

//void addEntity(std::shared_ptr<DataBase> db, const int typeId, const int objectId, const std::string& name) {
//
//	auto obj = createEntity(typeId, objectId, name);
//	db->addObject(typeId, objectId, obj);
//}

void removeEntity(std::shared_ptr<DataBase> db, const int typeId, const int objectId) {
	db->removeObject(typeId, objectId);
}

void listEntities(std::shared_ptr<DataBase> db) {
	

	for (int i = 0; i != db->typeAndObjectIds.size(); ++i) {

		int typeId = db->typeIds[i];
		std::cout << "typeId" << " " << "objectId" << " " << "name" << std::endl;

		for (int j = 0; j != db->typeAndObjectIds.at(typeId).size(); ++j) {

			int objectId = db->typeAndObjectIds.at(typeId)[j];
			auto obj = db->objects.at(typeId).at(objectId);
			std::string name = obj->getName();
			std::cout << typeId << " " << objectId << " " << name << std::endl;
		}
	}
}


int main() {

	std::shared_ptr<DataBase> dataPtr = loadDb("file2.txt");
	listEntities(dataPtr);

	
	return 0;
}

