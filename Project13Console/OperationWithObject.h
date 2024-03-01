#ifndef __OPERATIONWITHOBJECT_H_
#define __OPERATIONWITHOBJECT_H_
#include <iostream>
#include "Objects.h"

struct BaseOperationWithObject {

	BaseOperationWithObject(std::shared_ptr<object> obj);

	virtual void operation();

	virtual void editId(const int id);
	virtual void editName(const std::string& name);
	virtual void remove();

	std::shared_ptr<object> mObj;
};

struct OperationWithLine : BaseOperationWithObject {

	OperationWithLine(std::shared_ptr<object> obj);

	void operation() override;

	void editStartPoint(const vector2D& start);
	void editEndPoint(const vector2D& end);
	
	std::shared_ptr<Line> mLine;
};

struct OpertationWithRectangle : BaseOperationWithObject {

	OpertationWithRectangle(std::shared_ptr<object> obj);

	void operation() override;

	void editLeftDownPoint(const vector2D& leftDownPoint);
	void editLenth(const double lenth);
	void editWidth(const double width);

	std::shared_ptr<Rectangle> mRec;
};

struct OpertationWithCircle : BaseOperationWithObject {

	OpertationWithCircle(std::shared_ptr<object> obj);

	void operation() override;

	void editCenter(const vector2D center);
	void editRadius(const double radius);

	std::shared_ptr<Circle> mCircle;
};

struct OperationWithPolyline : BaseOperationWithObject {

};












#endif __OPERATIONWITHOBJECT_H_