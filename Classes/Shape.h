#pragma once
#include "Block.h"

class DetailShape;
class GridMap;

class Shape
{
public:
	Shape();
	Node* _node;
	Block4 _blocks;
	unique_ptr<DetailShape> _detail;

	pos _position;
	bool _running;

	void setPosition(const shared_ptr<GridMap>& grid, const pos& newPos);
};

class DetailShape
{
protected:
	float _maxAngle;
public:
	virtual ~DetailShape(){}
	float& getMaxAngle() { return _maxAngle; }
	virtual const int& referToInitCoordBoard(const int& row, const int& col) { return 0; };
	virtual const int& referToInitLocationNodeBoard(const int& row, const int& col) { return 0; };
	virtual const int& referToRotate(const int& row, const int& col) { return 0; };
};

class OShape : public DetailShape
{
public:
	OShape();
	const int& referToInitCoordBoard(const int& row, const int& col) override;
	const int& referToInitLocationNodeBoard(const int& row, const int& col) override;
	const int& referToRotate(const int& row, const int& col) override;
};

class IShape : public DetailShape
{
public:
	IShape();
	const int& referToInitCoordBoard(const int& row, const int& col) override;
	const int& referToInitLocationNodeBoard(const int& row, const int& col) override;
	const int& referToRotate(const int& row, const int& col) override;
};

class LShape : public DetailShape
{
public:
	LShape();
	const int& referToInitCoordBoard(const int& row, const int& col) override;
	const int& referToInitLocationNodeBoard(const int& row, const int& col) override;
	const int& referToRotate(const int& row, const int& col) override;
};

class TShape : public DetailShape
{
public:
	TShape();
	const int& referToInitCoordBoard(const int& row, const int& col) override;
	const int& referToInitLocationNodeBoard(const int& row, const int& col) override;
	const int& referToRotate(const int& row, const int& col) override;
};

class JShape : public DetailShape
{
public:
	JShape();
	const int& referToInitCoordBoard(const int& row, const int& col) override;
	const int& referToInitLocationNodeBoard(const int& row, const int& col) override;
	const int& referToRotate(const int& row, const int& col) override;
};

class SShape : public DetailShape
{
public:
	SShape();
	const int& referToInitCoordBoard(const int& row, const int& col) override;
	const int& referToInitLocationNodeBoard(const int& row, const int& col) override;
	const int& referToRotate(const int& row, const int& col) override;
};

class ZShape : public DetailShape
{
public:
	ZShape();
	const int& referToInitCoordBoard(const int& row, const int& col) override;
	const int& referToInitLocationNodeBoard(const int& row, const int& col) override;
	const int& referToRotate(const int& row, const int& col) override;
};
