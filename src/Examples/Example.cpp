/************************************************************************
*
* vaporEngine by triton � (2008-2009)
*
*	<http://www.portugal-a-programar.org>
*
************************************************************************/

#include "Example.h"

using namespace vapor::examples;

void Example::onInit()
{


}

void Example::onRender() 
{
	// clear the render device
	Device& device = getDevice();
	
	device.clearTarget();
}

void Example::onSetupResources() 
{

}