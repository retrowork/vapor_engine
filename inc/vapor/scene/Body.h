/************************************************************************
*
* vaporEngine (2008-2009)
*
************************************************************************/

#pragma once

#include "vapor/Platform.h"

#include "vapor/scene/Component.h"
#include "vapor/scene/Transform.h"
#include "vapor/scene/node.h"

#include "vapor/math/Matrix4x3.h"
#include "vapor/math/Vector3.h"
#include "vapor/math/EulerAngles.h"
#include "vapor/math/AABB.h"

#include "vapor/physics/Physics.h"

#include <Common/Base/hkBase.h>
#include <Common/Base/Math/Matrix/hkRotation.h>
#include <Physics/Collide/Shape/hkpShape.h>
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>

#include <Physics/Dynamics/hkpDynamics.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Dynamics/Entity/hkpRigidBodyCinfo.h>
#include <Physics/Dynamics/Motion/hkpMotion.h>
#include <Physics/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>


namespace vapor { namespace scene {

//-----------------------------------//

class VAPOR_API Body : public Component
{
public:

	Body();
	Body(float mass, hkpMotion::MotionType motion);
	virtual ~Body();

	// Inits the physics body.
	void init();

	// Gets the type of this component. 
	virtual const std::string& getType() const;

	// Called once per frame to update the component.
	virtual void update( float delta );

	void addToWorld();
	void removeFromWorld();
	void setLinearVelocity(const math::Vector3 &lVel);
	void setAngularVelocity(const math::Vector3 &aVel); 
	void applyForce(const math::Vector3 &force);
	void applyTorque(const math::Vector3 &torque);
	void applyLinearImpulse(const math::Vector3 &imp);

private:
	
	void setTransform(hkpRigidBodyCinfo& info);
	hkpBoxShape getShape(const math::AABB &bb);
	hkVector4 convertVector(const math::Vector3 &v);
	hkpRigidBody * body;
	Transform * transform;
	physics::PhysicsManager* physicsManager;
	bool inWorld;
	bool firstUpdate;

protected:

	static const std::string& type;
};

//-----------------------------------//

TYPEDEF_SHARED_POINTER_FROM_CLASS( Body );

//-----------------------------------//

} } // end namespaces