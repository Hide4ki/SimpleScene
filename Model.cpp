#include "Model.h"

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
			faces.push_back(j->Shadow(_lightSource));
		}
	}

	sort(faces.begin(), faces.end(), [](Face *l, Face *r) { return l->GetMidZ() < r->GetMidZ(); });
	
	for (auto r : faces)
		r->Draw();

	for (auto i : faces)
		if (!i->Real())
			delete i;

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
			faces.push_back(j->Shadow(_lightSource));
		}
	}

	for (auto r : faces)
		r->Clear();
	
	for (auto i : faces)
		if (!i->Real())
			delete i;

}

void Model::UpdateView()
{
	_canvas._update = true;
}

Model::Model(View &canvas, LightSource &light) :_canvas{ canvas }, _lightSource{ light }
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
