/************************************************************************
*
* vaporEngine (2008-2010)
*
*	<http://www.portugal-a-programar.org>
*
************************************************************************/

#include <vapor/PCH.h>

#include "Example.h"

#include "vapor/StringUtilities.h"
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

//-----------------------------------//

Example::Example(const char** argv)
	: Framework("Example", argv), c( 0.0f, 0.10f, 0.25f ),
	fpsUpdateTime( 0.0f )
{

}

//-----------------------------------//

void Example::onInit()
{
	// Mount VFS points
	const std::string& media = "media";

	if ( !getVFS()->mount( media ) )
	{
		Log::MessageDialog( "Missing archive/directory '" + media + "'." );
		exit(1);
	}

	//physicsManager->createWorld();
}

//-----------------------------------//

void Example::onSetupResources() 
{
	ResourceManager* rm = getResourceManager();
	
	ImagePtr img = rm->loadResource< Image >( "triton.png" );
	snd = rm->loadResource< resources::Sound >( "stereo.ogg" );
}

//-----------------------------------//

std::string getFPS( float lastFrameTime )
{
	if( lastFrameTime == 0 ) return "FPS:";

	std::string fps( boost::lexical_cast< std::string >
		( int( 1.0f / lastFrameTime ) ) );
	
	return "FPS: " + fps;
}

//-----------------------------------//

void Example::onSetupScene() 
{
	ScenePtr scene = getSceneManager();
	ResourceManager* rm = getResourceManager();

	// TODO: make shaders automatically loaded?
	ProgramPtr tex( new GLSL_Program( 
			rm->loadResource< GLSL_Shader >( "tex.vs" ),
			rm->loadResource< GLSL_Shader >( "tex.fs" ) ) );

	ProgramPtr diffuse( new GLSL_Program( 
			rm->loadResource< GLSL_Shader >( "diffuse.vs" ),
			rm->loadResource< GLSL_Shader >( "diffuse.fs" ) ) );

	ProgramPtr toon( new GLSL_Program( 
			rm->loadResource< GLSL_Shader >( "toon.vs" ),
			rm->loadResource< GLSL_Shader >( "toon.fs" ) ) );

	ProgramManager::getInstance().registerProgram( "diffuse", diffuse );
	ProgramManager::getInstance().registerProgram( "tex", tex );
	ProgramManager::getInstance().registerProgram( "toon", toon );
	
	// Create a new Camera
	NodePtr camera( new Node( "MainCamera" ) );
	cam.reset( new FirstPersonCamera( getInputManager(), getRenderDevice() ) );
	camera->addComponent( TransformPtr( new Transform() ) );
	camera->addComponent( cam );
	scene->add( camera );

	MeshPtr mesh = rm->loadResource< Mesh >( "cubo.ms3d" );
	NodePtr ct( new Node( "ct" ) );
	ct->addComponent( TransformPtr( new Transform( 0.0f, 50.0f, 0.0f ) ) );
	ct->addComponent( mesh );
	//ct->addComponent( BodyPtr( new Body() ) );
	scene->add(ct);

	foreach( const RenderablePtr& rend, mesh->getRenderables() )
	{
		rend->getMaterial()->setProgram( tex );
	}
	
	// Materials too?
	MaterialPtr mat( new Material( "FontMaterial", tex ) );
	FontPtr font = rm->loadResource< Font >( "Verdana.font" );
	label.reset( new Label( getFPS( (float)lastFrameTime ), font, mat ) );
	NodePtr fps( new Node( "FPSNode" ) );
	fps->addComponent( TransformPtr( new Transform() ) );
	fps->addComponent( label );
	fps->getTransform()->translate( -300.0f, 220.0f, 0.0f );
	scene->add( fps );

	NodePtr grid( new Node( "Grid" ) );
	grid->addComponent( TransformPtr( new Transform() ) );
	grid->addComponent( ComponentPtr( new Grid( mat ) ) );
	//grid->addComponent( BodyPtr( new Body( 100.0f, hkpMotion::MOTION_FIXED ) ) );
	scene->add( grid );

	foreach( const RenderablePtr& rend, 
	grid->getComponent<Geometry>("Grid")->getRenderables() )
	{
		rend->getMaterial()->setProgram( diffuse );
	}

	NodePtr lnode( new Node( "Light" ) );
	LightPtr light( new Light( LightType::Point ) );
	light->diffuseColor = Colors::Red;
	light->ambientColor = Colors::Yellow;
	lnode->addComponent( light );
	scene->add( lnode );

	TerrainSettings settings;
	settings.CellSize = 1024;
	settings.TileDimensions = 32;
	settings.MaxHeight = 150;

	TerrainPtr terrain( new Terrain( settings ) );

	NodePtr terreno( new Node( "Terreno" ) );
	terreno->addComponent( TransformPtr( new Transform() ) );
	terreno->addComponent( terrain );
	scene->add( terreno );

	ImagePtr heightmap = rm->loadResource< Image >( "height2.png" );
	Cell* cell = terrain->createCell( heightmap, 0, 0 );
}

//-----------------------------------//
 
void Example::onUpdate( double delta ) 
{
	ScenePtr scene = getSceneManager();
	scene->update( delta );
	
	if( fpsUpdateTime <= 1.0f )
	{
		fpsUpdateTime += delta;
	}
	else
	{
		label->setText( getFPS( (float)lastFrameTime ) );
		fpsUpdateTime = 0.0f;
	}
}

//-----------------------------------//

void Example::onRender()
{
	render::Device* device = getRenderDevice();

	device->setClearColor( c );
	device->clearTarget();

	cam->render();
}

//-----------------------------------//

void Example::onKeyPressed( const KeyEvent& keyEvent )
{
	if( keyEvent.keyCode == Keys::Space )
		debug( "time: %f", frameTimer.getElapsedTime() );

	if( keyEvent.keyCode == Keys::Pause )
		Log::showDebug = !Log::showDebug;

	//if( keyEvent.keyCode == Keys::F )
		//debug( "fps: %d", int( 1.0f / lastFrameTime ) );

	if( keyEvent.keyCode == Keys::G )
	{
		debug( "min/avg/max: %f / %f / %f", 
					minFrameTime, avgFrameTime, maxFrameTime );
	}

	if( keyEvent.keyCode == Keys::P )
	{
		if( sound->isPlaying() )
			sound->pause();
		else
			sound->play();
	}
}

//-----------------------------------//

void Example::onButtonPressed( const MouseButtonEvent& btnEvent )
{

}

//-----------------------------------//
