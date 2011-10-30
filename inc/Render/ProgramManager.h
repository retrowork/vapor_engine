/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#pragma once

FWD_DECL_INTRUSIVE(Program)
FWD_DECL_INTRUSIVE(GLSL_Program)

NAMESPACE_ENGINE_BEGIN

//-----------------------------------//

class Shader;

typedef std::map<const Shader*, GLSL_ProgramPtr> ShaderProgramsMap;
typedef std::pair<const Shader*, GLSL_ProgramPtr> ShaderProgramsMapPair;

class ResourceManager;
struct ResourceEvent;

/**
 * Manages a set of programs. The rest of the engine, when needing a 
 * program will request the program for a given shader.
 */

class API_ENGINE ProgramManager
{
	DECLARE_UNCOPYABLE(ProgramManager)

public:

	ProgramManager();
	~ProgramManager();

	// Gets a program given a shader identifier.
	ProgramPtr getProgram( const Shader*, bool precompile = false );

	// Creates a program given a shader.
	GLSL_ProgramPtr createProgram( const Shader* shader );

	// Registers a new program in the manager.
	bool registerProgram( const Shader*, const GLSL_ProgramPtr& program );

protected:

	// Populates a shader when the text file is loaded.
	void onLoad( const ResourceEvent& evt );

	// Reloads a shader when the text file changes.
	void onReload( const ResourceEvent& evt );

	// Maps the identifiers to the programs.
	ShaderProgramsMap programs;
};

//-----------------------------------//

NAMESPACE_ENGINE_END