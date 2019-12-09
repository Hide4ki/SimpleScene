#include "Model.h"

const double size_room = 100;

int Model::GenerateId()
{
	static int id = 0;
	return ++id;
}

TransformMatrix Model::GenerateTransformMatrix(Transform type, double value)
{
	TransformMatrix tmp;
	tmp(0, 0) = 1;
	tmp(1, 1) = 1;
	tmp(2, 2) = 1;
	tmp(3, 3) = 1;
	switch (type)
	{
	case Transform::MOVE_L:
		tmp(3, 0) = -value;
		break;
	case Transform::MOVE_R:
		tmp(3, 0) = value;
		break;
	case Transform::MOVE_U:
		tmp(3, 1) = -value;
		break;
	case Transform::MOVE_D:
		tmp(3, 1) = value;
		break;
	case Transform::MOVE_B:
		tmp(3, 2) = -value;
		break;
	case Transform::MOVE_F:
		tmp(3, 2) = value;
		break;
	case Transform::SCALE:
		tmp(0, 0) = value;
		tmp(1, 1) = value;
		tmp(2, 2) = value;
		break;
	case Transform::ROTATE_CW_X:
		tmp(1, 1) = cos(value*M_PI / 180);
		tmp(1, 2) = -sin(value*M_PI / 180);
		tmp(2, 1) = sin(value*M_PI / 180);
		tmp(2, 2) = cos(value*M_PI / 180);
		break;
	case Transform::ROTATE_ACW_X:
		tmp(1, 1) = cos(-value*M_PI / 180);
		tmp(1, 2) = -sin(-value*M_PI / 180);
		tmp(2, 1) = sin(-value*M_PI / 180);
		tmp(2, 2) = cos(-value*M_PI / 180);
		break;
	case Transform::ROTATE_CW_Y:
		tmp(0, 0) = cos(value*M_PI / 180);
		tmp(0, 2) = -sin(value*M_PI / 180);
		tmp(2, 0) = sin(value*M_PI / 180);
		tmp(2, 2) = cos(value*M_PI / 180);
		break;
	case Transform::ROTATE_ACW_Y:
		tmp(0, 0) = cos(-value*M_PI / 180);
		tmp(0, 2) = -sin(-value*M_PI / 180);
		tmp(2, 0) = sin(-value*M_PI / 180);
		tmp(2, 2) = cos(-value*M_PI / 180);
		break;
	case Transform::ROTATE_CW_Z:
		tmp(0, 0) = cos(value*M_PI / 180);
		tmp(0, 1) = -sin(value*M_PI / 180);
		tmp(1, 0) = sin(value*M_PI / 180);
		tmp(1, 1) = cos(value*M_PI / 180);
		break;
	case Transform::ROTATE_ACW_Z:
		tmp(0, 0) = cos(-value*M_PI / 180);
		tmp(0, 1) = -sin(-value*M_PI / 180);
		tmp(1, 0) = sin(-value*M_PI / 180);
		tmp(1, 1) = cos(-value*M_PI / 180);
		break;
	}
	return tmp;
}

void Model::Draw()
{
	vector<Face*> faces;
	for (auto i : _items)
	{
		auto f = i->GetFaces();
		for (auto j : f)
		{
			faces.push_back(j);
			TransformMatrix shadow;
			auto l = _lightSource.GetPlace();
			shadow(0, 0) = -l(0, 2);
			shadow(0, 1) = l(0, 1);
			shadow(1, 0) = l(0, 0);
			shadow(1, 1) = -l(0, 2);
			shadow(2, 2) = 0;
			shadow(2, 3) = 1;
			shadow(3, 3) = -l(0, 2);
			Face *tmp = new Face{ (*j)(shadow) };
			auto tmp2 = tmp->GetSetCoordinats();
			(*tmp2)(0, 0) /= (*tmp2)(0, 3);
			(*tmp2)(0, 1) /= (*tmp2)(0, 3);
			(*tmp2)(0, 2) /= (*tmp2)(0, 3);
			(*tmp2)(0, 3) /= (*tmp2)(0, 3);
			(*tmp2)(1, 0) /= (*tmp2)(1, 3);
			(*tmp2)(1, 1) /= (*tmp2)(1, 3);
			(*tmp2)(1, 2) /= (*tmp2)(1, 3);
			(*tmp2)(1, 3) /= (*tmp2)(1, 3);
			(*tmp2)(2, 0) /= (*tmp2)(2, 3);
			(*tmp2)(2, 1) /= (*tmp2)(2, 3);
			(*tmp2)(2, 2) /= (*tmp2)(2, 3);
			(*tmp2)(2, 3) /= (*tmp2)(2, 3);
			(*tmp2)(3, 0) /= (*tmp2)(3, 3);
			(*tmp2)(3, 1) /= (*tmp2)(3, 3);
			(*tmp2)(3, 2) /= (*tmp2)(3, 3);
			(*tmp2)(3, 3) /= (*tmp2)(3, 3);
			tmp->CalculMidZ();
			faces.push_back(tmp);
		}
	}
	sort(faces.begin(), faces.end(), [](Face *l, Face *r) { return l->GetMidZ() < r->GetMidZ(); });
	for (auto r : faces)
		r->Draw();
	UpdateView();
}

void Model::Clear()
{
	vector<Face*> faces;
	for (auto i : _items)
	{
		auto f = i->GetFaces();
		for (auto j : f)
		{
			faces.push_back(j);
			TransformMatrix shadow;
			auto l = _lightSource.GetPlace();
			shadow(0, 0) = -l(0, 2);
			shadow(0, 1) = l(0, 1);
			shadow(1, 0) = l(0, 0);
			shadow(1, 1) = -l(0, 2);
			shadow(2, 2) = 0;
			shadow(2, 3) = 1;
			shadow(3, 3) = -l(0, 2);
			Face *tmp = new Face{ (*j)(shadow) };
			auto tmp2 = tmp->GetSetCoordinats();
			(*tmp2)(0, 0) /= (*tmp2)(0, 3);
			(*tmp2)(0, 1) /= (*tmp2)(0, 3);
			(*tmp2)(0, 2) /= (*tmp2)(0, 3);
			(*tmp2)(0, 3) /= (*tmp2)(0, 3);
			(*tmp2)(1, 0) /= (*tmp2)(1, 3);
			(*tmp2)(1, 1) /= (*tmp2)(1, 3);
			(*tmp2)(1, 2) /= (*tmp2)(1, 3);
			(*tmp2)(1, 3) /= (*tmp2)(1, 3);
			(*tmp2)(2, 0) /= (*tmp2)(2, 3);
			(*tmp2)(2, 1) /= (*tmp2)(2, 3);
			(*tmp2)(2, 2) /= (*tmp2)(2, 3);
			(*tmp2)(2, 3) /= (*tmp2)(2, 3);
			(*tmp2)(3, 0) /= (*tmp2)(3, 3);
			(*tmp2)(3, 1) /= (*tmp2)(3, 3);
			(*tmp2)(3, 2) /= (*tmp2)(3, 3);
			(*tmp2)(3, 3) /= (*tmp2)(3, 3);
			tmp->CalculMidZ();
			faces.push_back(tmp);
		}
	}
	for (auto r : faces)
		r->Clear();
	for (auto i : faces)
		if (!i->GetR())
			delete i;

}

void Model::UpdateView()
{
	_canvas._update = true;
}

Model::Model(View &canvas, LightSource &light) :_canvas{ canvas }, _lightSource{ light }, _room
{
	{ 0, 0, 0, 1 }
	,{ 0, 0, size_room, 1 }
	,{ 0, size_room, 0, 1 }
	,{ 0, size_room, size_room, 1 }
	,{ size_room, 0, 0, 1 }
	,{ size_room, 0, size_room, 1 }
	,{ size_room, size_room, 0, 1 }
	,{ size_room, size_room, size_room, 1 }
}
{
}

void Model::ChangeLightSource(int newX, int newY, int newZ)
{
	Clear();
	_lightSource._place(0, 0) = newX;
	_lightSource._place(0, 1) = newY;
	_lightSource._place(0, 2) = newZ;
	Draw();
}

int Model::AddObj(TypeObject type, Object &&newObj)
{
	Clear();
	switch (type)
	{
	case TypeObject::CUBE:
		_items.push_back(new Cube(move(newObj)));
		break;
	case TypeObject::PARALLEPIPED:
		_items.push_back(new Parallepiped(move(newObj)));
		break;
	}
	auto r = GenerateId();
	_items.back()->SetId(r);
	Draw();
	return r;
}

void Model::RemoveObj(int id)
{
	Clear();
	auto f = find_if(_items.begin(), _items.end(), [id](Object* s) { return id == s->GetId(); });
	if (f == _items.end())
		return;
	swap(*f, _items.back());
	delete _items.back();
	_items.pop_back();
	Draw();
}

void Model::AloneChangeObj(int id, Transform type, double value)
{
	Clear();
	auto f = find_if(_items.begin(), _items.end(), [id](Object* s) { return id == s->GetId(); });
	if (f == _items.end())
		return;
	(**f)(GenerateTransformMatrix(type, value));
	Draw();
}

void Model::MultiChangeObj(int id, TransformMatrix &changer)
{
	Clear();
	auto f = find_if(_items.begin(), _items.end(), [id](Object* s) { return id == s->GetId(); });
	if (f == _items.end())
		return;
	(**f)(changer);
	Draw();
}

void Model::AloneChange(Transform type, double value)
{
	Clear();
	for (auto r : _items)
		(*r)(GenerateTransformMatrix(type, value));
	Draw();
}

void Model::MultiChange(TransformMatrix &changer)
{
	Clear();
	for (auto r : _items)
		(*r)(changer);
	Draw();
}
