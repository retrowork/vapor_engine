/************************************************************************
*
* vaporEngine (2008-2009)
*
*	<http://www.portugal-a-programar.org>
*
************************************************************************/

#pragma once

#include "vapor/Platform.h"

#include "vapor/resources/Shader.h"
#include "vapor/render/VertexBuffer.h"

namespace vapor {
	namespace render {

//-----------------------------------//

/**
 * A program is a collection of shaders (at least a vertex shader 
 * and a pixel shader). When it is linked it is ready to be used
 * by the renderer. A program will have some parameters automatically
 * bound, like world matrices and such. Refer to the documentation
 * to have more information about these.
 */

class VAPOR_API Program
{
public:

	Program( resources::ShaderPtr vs, resources::ShaderPtr ps );
	virtual ~Program();

	// Adds a named parameter to the program.
	virtual void addAttribute( const std::string& slot, VertexAttribute::Enum attr ) = 0;

	// Adds a named uniform to the program.
	virtual void addUniform( const std::string& slot, std::vector< float > data ) = 0;

	// Links the program and returns if it was successful.
	virtual bool link() = 0;

	// Binds the program to be used for rendering operations.
	virtual void bind() = 0;

	// Unbinds the program.
	virtual void unbind() = 0;

	// Returns if this program has been successfully linked.
	virtual bool isLinked() const;

	// Gets the linking log.
	const std::string& getLog() const;

	// Serialization

	//virtual void load( const std::string& name ) = 0;
	//virtual void save( const std::string& name ) = 0;

protected:

	std::vector< resources::ShaderPtr > shaders;
	std::string log;
	bool linked;
};

//-----------------------------------//

typedef tr1::shared_ptr< Program > ProgramPtr;

//-----------------------------------//

} } // end namespaces