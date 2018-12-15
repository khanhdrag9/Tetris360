#pragma once
#include "Block.h"

class DetailShape;

class Shape
{
public:
	Shape();
	Node* _node;
	Block4 _blocks;
	unique_ptr<DetailShape> _detail;
};

class DetailShape
{
	float _maxAngle;
public:
	virtual ~DetailShape(){}
	float& getMaxAngle() { return _maxAngle; }
	virtual const int& referToInitCoordBoard(const int& row, const int& col) { return NULL; };
	virtual const int& referToInitLocationNodeBoard(const int& row, const int& col) { return NULL; };
};

class OShape : public DetailShape
{
public:
	const int& referToInitCoordBoard(const int& row, const int& col) override;
	const int& referToInitLocationNodeBoard(const int& row, const int& col) override;
};

class IShape : public DetailShape
{
public:
	const int& referToInitCoordBoard(const int& row, const int& col) override;
	const int& referToInitLocationNodeBoard(const int& row, const int& col) override;
};

class LShape : public DetailShape
{
public:
	const int& referToInitCoordBoard(const int& row, const int& col) override;
	const int& referToInitLocationNodeBoard(const int& row, const int& col) override;
};

class TShape : public DetailShape
{
public:
	const int& referToInitCoordBoard(const int& row, const int& col) override;
	const int& referToInitLocationNodeBoard(const int& row, const int& col) override;
};