#include "pch.h"
#include "Object.h"

Object::Object()
	: Objtype(eObjectType_None)
	, x(0.0f)
	, y(0.0f)
	, width(0)
	, height(0)
	, r(0)
{

}

Object::Object(EObjectType inType)
	: Objtype(inType)
	, x(0.0f)
	, y(0.0f)
	, width(0)
	, height(0)
	, r(0)
{

}