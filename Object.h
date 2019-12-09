#pragma once
#include <vector>
#include <map>
#include "Face.h"
#include "View.h"
#include "Viewer.h"
#include "TransformMatrix.h"

using namespace std;

enum class TypeObject { CUBE, PARALLEPIPED };
class Face;
class View;

class Object
{
private:
	vector<Face*> GetFaces();
protected:
	Object(View&, Viewer&);
	void SetId(int);
	int GetId();
	void operator()(TransformMatrix&);
public:
	~Object();
	Object() = delete;
	Object(const Object&);
	Object(Object&&);
private:
	int _id;
protected:
	vector<Face*> _body;
	View &_canvas;
	Viewer &_camera;
	friend class Model;
};

