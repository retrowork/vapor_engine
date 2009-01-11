/************************************************************************
*
* vaporEngine by triton � (2008-2009)
*
*	<http://www.portugal-a-programar.org>
*
************************************************************************/

#include "vapor/render/opengl/GL_Device.h"

namespace vapor {
	namespace render {

Device::Device()
{

}

Device::~Device()
{
	delete _adapter;
	delete _window;
}

Window& Device::getWindow()
{
	return *_window;
}

Adapter& Device::getAdapter()
{
	return *_adapter;
}

void Device::updateTarget()
{
	_activeTarget->update();
}

void Device::setRenderTarget(RenderTarget* renderTarget)
{
	_activeTarget = renderTarget;
}

BufferManager* Device::getBufferManager()
{
	return _bufferManager;
}

Device* Device::createDevice(WindowSettings wS)
{
	return new opengl::GLDevice(wS);
}

} } // end namespaces
