#include "Object.h"

vector<Face*> Object::GetFaces()
{
	return _body;
}

Object::Object(View &canvas, Viewer &camera) :_canvas{ canvas }, _camera{ camera }
{
}

Object::Object(const Object &copyObj) : _canvas{ copyObj._canvas }, _camera{ copyObj._camera }
{
	for (auto i : copyObj._body)
		_body.push_back(new Face(*i));
}

Object::Object(Object &&moveObj) : _canvas{ moveObj._canvas }, _camera{ moveObj._camera }
{
	for (auto i : moveObj._body)
		_body.push_back(new Face(move(*i)));
}

Object::~Object()
{
	for (auto i : _body)
		if(!i)
			delete i;
}

void Object::SetId(int id)
{
	_id = id;
}

int Object::GetId()
{
	return _id;
}

void Object::operator()(TransformMatrix &tMatrix)
{
	TransformMatrix from;
	for (auto i : _body)
	{
		auto m = i->Centre();
		from(3, 0) += m(0, 0);
		from(3, 1) += m(0, 1);
		from(3, 2) += m(0, 2);
	}
	from(3, 0) /= _body.size();
	from(3, 1) /= _body.size();
	from(3, 2) /= _body.size();
	TransformMatrix to{ from };
	to(3, 0) *= -1;
	to(3, 1) *= -1;
	to(3, 2) *= -1;
	TransformMatrix transform;
	for (int i = 0; i < 4; i++)
		transform(i, i) = 1;
	transform *= to * tMatrix * from;
	for (auto i : _body)
	{
		*i->GetSetCoordinats() *= transform;
		i->CalculMidZ();
	}
}
