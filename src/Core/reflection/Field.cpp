/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#include "Core/API.h"
#include "core/Field.h"

namespace vapor {

//-----------------------------------//

Field::Field( const Type& type )
	: type(type)
	, qualifiers(0)
	, size(-1)
	, offset(-1)
	, pointerSize(-1)
	, setterFunction(nullptr)
{ }

//-----------------------------------//

void Field::setSetter( SetterFunctionPtr fn )
{
	setterFunction = fn;
}

//-----------------------------------//

void Field::setQualifier( byte qualifier )
{
	qualifiers |= qualifier;
}

//-----------------------------------//

bool Field::isArray() const
{
	return (qualifiers & Qualifier::Array);
}

//-----------------------------------//

bool Field::isHandle() const
{
	return (qualifiers & Qualifier::Handle) != 0;
}


//-----------------------------------//

bool Field::isPointer() const
{
	return (qualifiers & Qualifier::RawPointer)
		|| (qualifiers & Qualifier::SharedPointer)
		|| (qualifiers & Qualifier::RefPointer);
}

//-----------------------------------//

bool Field::isReadOnly() const
{
	return (qualifiers & Qualifier::ReadOnly) != 0;
}

//-----------------------------------//

} // end namespace