/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#include "Core/API.h"
#include "Serialization.h"
#include "Reflection.h"
#include "Log.h"
#include "ReferenceCount.h"

namespace vapor {

//-----------------------------------//

ObjectWalker::ObjectWalker(ReflectionVisitor& visitor)
	: v(visitor)
{ }

//-----------------------------------//

void ObjectWalker::process(const Object* object)
{
	const Class& type = (Class&) object->getType();

	ObjectData data;
	data.type = (Type*) &type;
	data.instance = (void*) object;

	processObject(data);
}

//-----------------------------------//

void ObjectWalker::processObject(ObjectData object)
{
	v.processBegin(object);
	processType(object);
	v.processEnd(object);
}

//-----------------------------------//

void ObjectWalker::processType(ObjectData object)
{
	if( !object.instance )
		return;

	const Type& type = *object.type;

	if( type.isClass() || type.isStruct() )
	{
		processClass(object);		
	}
	else if( type.isPrimitive() )
	{
		processPrimitive(object);
	}
	else if( type.isEnum() )
	{
		processEnum(object);
	}
	else assert( false );
}

//-----------------------------------//

void ObjectWalker::processClass(ObjectData object, bool parent)
{
	Class& type = (Class&) *object.type;
	v.processClassBegin(type, parent);

	if( type.parent )
	{
		ObjectData parent;
		parent.instance = object.instance;
		parent.type = (Type*) type.parent;
		
		processClass(parent, true);
	}

	FieldsMap::const_iterator it;
	const FieldsMap& fields = type.getFields();

	for( it = fields.begin(); it != fields.end(); it++ )
	{
		const Field& field = *(it->second);
		processField(object, field);
	}

	v.processClassEnd(type, parent);
}

//-----------------------------------//

void ObjectWalker::processEnum(ObjectData object)
{
	const Enum& metaenum = (Enum&) *object.type;
	
	v.processEnumBegin(metaenum);

	int value = *(int*) object.instance;
	const std::string& name = metaenum.getName(value);
	
	v.processEnumElement(value, name);

	v.processEnumEnd(metaenum);
}

//-----------------------------------//

void ObjectWalker::processField(ObjectData object, const Field& field)
{
	if( !object.instance ) return;
	
	const Type& type = field.type;

	object.instance = (byte*) object.instance + field.offset;
	object.type = (Type*) &type;

	v.processFieldBegin(field);

	if( field.qualifiers & Qualifier::Array )
	{
		processArray(object, field);
	}
	else
	{
		if( field.isPointer() )
			processPointer(object, field);

		processType(object);
	}

	v.processFieldEnd(field);
}

//-----------------------------------//

void ObjectWalker::processPointer(ObjectData& object, const Field& field)
{
	void* address = object.instance;

	if( field.qualifiers & Qualifier::SharedPointer )
	{
		std::shared_ptr<Object>* shared = (std::shared_ptr<Object>*) address;
		address = shared->get();
	}
	else if( field.qualifiers & Qualifier::RefPointer )
	{
		RefPtr<Object>* ref = (RefPtr<Object>*) address;
		address = ref->get();
	}

	object.instance = address;

	if( !address ) return;

	const Object* elemObject = (Object*) address;
	object.type = (Type*) &elemObject->getType();
}

//-----------------------------------//

void ObjectWalker::processArray(ObjectData object, const Field& field)
{
	std::vector<byte>& array = * (std::vector<byte>*) object.instance;

	int size = 0;

	if( field.isPointer() )
		size = field.pointerSize;
	else
		size = field.size;

	uint numElems = array.size() / size;

	v.processArrayBegin(field.type, numElems);
		
	for(uint i = 0; i < numElems; i++)
	{
		void* address = (&array.front() + i * size);

		ObjectData elem;
		elem.instance = address;
		elem.type = object.type;

		if( field.isPointer() )
			processPointer(elem, field);

		v.processArrayElementBegin(i);
		processType(elem);
		v.processArrayElementEnd(i);
	}

	v.processArrayEnd(field.type);
}

//-----------------------------------//

void ObjectWalker::processPrimitive(const ObjectData& object)
{
	const Primitive& type = (const Primitive&) *object.type;

	if( type.isBool() )
	{
		bool* val = (bool*) object.instance;
		v.processBool(type, *val);
	}
	//-----------------------------------//
	else if( type.isInteger() )
	{
		int* val = (int*) object.instance;
		v.processInt(type, *val);
	}
	//-----------------------------------//
	else if( type.isFloat() )
	{
		float* val = (float*) object.instance;
		v.processFloat(type, *val);
	}
	//-----------------------------------//
	else if( type.isString() )
	{
		std::string* val = (std::string*) object.instance;
		v.processString(type, *val);
	}
	//-----------------------------------//
	else if( type.isColor() )
	{
		Color* val = (Color*) object.instance;
		v.processColor(type, *val);
	}
	//-----------------------------------//
	else if( type.isVector3() )
	{
		Vector3* vec = (Vector3*) object.instance;
		v.processVector3(type, *vec);
	}
	//-----------------------------------//
	else if( type.isQuaternion() )
	{
		Quaternion* quat = (Quaternion*) object.instance;
		v.processQuaternion(type, *quat);
	}
	//-----------------------------------//
	else if( type.isBitfield() )
	{
		uint* bits = (uint*) object.instance;
		v.processBitfield(type, *bits);
	}
	else assert( false );
}

//-----------------------------------//

} // end namespace