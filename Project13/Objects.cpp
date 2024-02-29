#include "Objects.h"
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include "InputFiler.h"
#include "Vector2D.h"
#include "OutputFiler.h"

object::object(const std::string& name, const int id) : mName(name), mId(id) {

}

void object::output(std::shared_ptr<OutputFiler> file) {
	file->outputString(mName);
	file->outputInt(mId);
}

void object::setName(const std::string& name) {

	mName = name;
}
void object::setId(const int id) {

	mId = id;
}

std::string object::getName() const {

	return mName;
}

int object::getId() const {

	return mId;
}

void object::input(std::shared_ptr<InputFiler> file) {

	mName = file->readString();
	mId = file->readInt();
}

Line::Line(const std::string& name_, const int id_, const vector2D& start_, const vector2D& end_)
	: object(name_, id_), mStart(start_), mEnd(end_)
{

}

double Line::getLenth() {

	vector2D dir = mEnd - mStart;

	return sqrt(dir.x * dir.x + dir.y * dir.y);
}

void Line::setStart(const vector2D& start) {

	mStart = start;
};

void Line::setEnd(const vector2D& end) {

	mEnd = end;
};

vector2D Line::getStart() const {

	return mStart;
};

vector2D Line::getEnd() const {

	return mEnd;
};

void Line::input(std::shared_ptr<InputFiler> file) {
	;
	mStart = file->readVector2D();
	mEnd = file->readVector2D();
}

void Line::output(std::shared_ptr<OutputFiler> file) {

	object::output(file);
	file->outputVector2D(mStart);
	file->outputVector2D(mEnd);
}

Rectangle::Rectangle(const std::string& name_, const int id_, const vector2D& vector2D, const double lenth_, const double width_)
	: object(name_, id_), mLeftDownPoint(vector2D), mLenth(lenth_), mWidth(width_)
{

}

void Rectangle::setLeftDownPoint(const vector2D& vector2D) {

	mLeftDownPoint = vector2D;
};

void Rectangle::setLenth(const int& lenth) {

	mLenth = lenth;
};

void Rectangle::setWidth(const int& width) {

	mWidth = width;
};

vector2D Rectangle::getLeftDownPoint() {

	return mLeftDownPoint;
};

double Rectangle::getLenth() {

	return mLenth;
};

double Rectangle::getWidth() {

	return mWidth;
};

double Rectangle::getArea() const {

	return mLenth * mWidth;
};

double Rectangle::getPerimetr() const {

	return 2 * mLenth + 2 * mWidth;
};

void Rectangle::input(std::shared_ptr<InputFiler> file) {

	mLeftDownPoint = file->readVector2D();
	mLenth = file->readDouble();
	mWidth = file->readDouble();
}

void Rectangle::output(std::shared_ptr<OutputFiler> file) {

	object::output(file);
	file->outputVector2D(mLeftDownPoint);
	file->outputDouble(mLenth);
	file->outputDouble(mWidth);

	vector2D leftUpPoint = { mLeftDownPoint.x, mLeftDownPoint.y + mWidth };
	Line ab{ "vector AB", 1, mLeftDownPoint, leftUpPoint };

	vector2D rightUpPoint = { mLeftDownPoint.x + mLenth, mLeftDownPoint.y + mWidth };
	Line bc{ "vector BC", 2, leftUpPoint, rightUpPoint };

	vector2D rightDownPoint = { mLeftDownPoint.x + mLenth, mLeftDownPoint.y };
	Line cd{ "vector CD", 3, rightUpPoint, rightDownPoint };

	Line da{ "vector DA", 4, rightDownPoint, mLeftDownPoint };

	ab.output(file);
	bc.output(file);
	cd.output(file);
	da.output(file);

	file->outputString("perimetr");
	file->outputDouble(getPerimetr());
	file->outputString("area");
	file->outputDouble(getArea());

}

Circle::Circle(const std::string& name, const int id, const vector2D& center, const double radius)
	: object(name, id), mCenter(center), mRadius(radius) {

}

void Circle::setCenter(const vector2D& center) {

	mCenter = center;
};

void Circle::setRadius(const double radius) {

	mRadius = radius;
};

vector2D Circle::getCenter() const {

	return mCenter;
};

double Circle::getRadius() const {

	return mRadius;
};

double Circle::getArea() const {

	const double Pi = 3.141592653589793;
	return Pi * mRadius * mRadius;
};

void Circle::input(std::shared_ptr<InputFiler> file) {

	mCenter = file->readVector2D();
	mRadius = file->readDouble();
}

std::vector<Line> Circle::createLines() {

	std::vector<vector2D> points;

	int countOfpoints = 360;
	const double Pi = 3.141592653589793;
	double increment = 2 * Pi / countOfpoints;

	for (double i = 0; i < 2 * Pi; i += increment) {

		vector2D point = { mCenter.x + mRadius * cos(i), mCenter.y + mRadius * sin(i) };
		points.push_back(point);
	}

	std::vector<Line> lines;
	std::vector<Line> line;
	for (int i = 0; i < 359; i++) {

		Line line("vector", i, points[i], points[i + 1]);
		lines.push_back(line);
	}
	return lines;
}

void Circle::output(std::shared_ptr<OutputFiler> file) {

	object::output(file);
	file->outputString("center");
	file->outputVector2D(mCenter);
	file->outputString("radius");
	file->outputDouble(mRadius);

	std::vector<Line> lines = createLines();
	for (int i = 0; i < lines.size() - 1; i++) {
		lines[i].output(file);
	}
}

Polyline::Polyline(const std::string& name, const int id, const std::vector<vector2D>& points)
	: object(name, id), mPoints(points)
{

}

void Polyline::input(std::shared_ptr<InputFiler> file) {


	int countOfPoints = file->readInt();

	for (int i = 0; i < countOfPoints; i++) {
		mPoints.push_back(file->readVector2D());
	}
}

void Polyline::createLines(std::vector<Line>& lines)
{

	for (int i = 0; i < mPoints.size() - 1; i++) {

		Line line("vector", i, mPoints[i], mPoints[i + 1]);
		lines.push_back(line);
	}
}

void Polyline::output(std::shared_ptr<OutputFiler> file) {

	object::output(file);

	std::vector<Line> lines;
	createLines(lines);
	file->outputString("count of points");
	file->outputInt(mPoints.size());

	for (int i = 0; i < lines.size(); i++) {
		lines[i].output(file);
	}
}