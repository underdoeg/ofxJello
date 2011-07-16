#include "SpringBody.h"

SpringBody::~SpringBody()
{
	delete [] mIndices;
	mSprings.clear();
	mIndexList.clear();
}


SpringBody::SpringBody(ClosedShape *shape, float massPerPoint, float edgeSpringK, float edgeSpringDamp, Vector2 &pos, float angleinRadians, Vector2 scale, bool kinematic):
Body(shape,massPerPoint,pos,angleinRadians,scale,kinematic)
{
	mShapeMatchingOn = false;
	setPositionAngle(pos, angleinRadians, scale);

    
    mShapeSpringK = 0.0f;
    mShapeSpringDamp = 0.0f;
    mEdgeSpringK = edgeSpringK;
    mEdgeSpringDamp = edgeSpringDamp;

	
	dragPoint = -1;

    // build default springs.
    _buildDefaultSprings();

	Type = 2;
}

SpringBody::SpringBody(ClosedShape *shape, float massPerPoint, float shapeSpringK, float shapeSpringDamp, float edgeSpringK, float edgeSpringDamp, Vector2 &pos, float angleinRadians, Vector2 scale, bool kinematic):
Body(shape,massPerPoint,pos,angleinRadians,scale,kinematic)
{
	setPositionAngle(pos, angleinRadians, scale);

    mShapeMatchingOn = true;
    mShapeSpringK = shapeSpringK;
    mShapeSpringDamp = shapeSpringDamp;
    mEdgeSpringK = edgeSpringK;
    mEdgeSpringDamp = edgeSpringDamp;

	
	dragPoint = -1;

    // build default springs.
    _buildDefaultSprings();

	Type = 2;
}

void SpringBody::addInternalSpring(int pointA, int pointB, float springK, float damping)
{
    float dist = (mPointMasses[pointB]->Position - mPointMasses[pointA]->Position).Length();
    InternalSpring *s = new InternalSpring(pointA, pointB, dist, springK, damping);

    mSprings.push_back(s);
}

void SpringBody::_buildDefaultSprings()
{
	for (unsigned int i = 0; i < mPointMasses.size(); i++)
    {
        if (i < (mPointMasses.size() - 1))
            addInternalSpring(i, i + 1, mEdgeSpringK, mEdgeSpringDamp);
        else
            addInternalSpring(i, 0, mEdgeSpringK, mEdgeSpringDamp);
    }
}

void SpringBody::clearAllSprings()
{
    mSprings.clear();
    _buildDefaultSprings();
}

void SpringBody::setShapeMatching(bool onoff) { mShapeMatchingOn = onoff; }
void SpringBody::setShapeMatchingConstants(float springK, float damping) { mShapeSpringK = springK; mShapeSpringDamp = damping; }

void SpringBody::setEdgeSpringConstants(float edgeSpringK, float edgeSpringDamp)
{
    // we know that the first n springs in the list are the edge springs.
    for (unsigned int i = 0; i < mPointMasses.size(); i++)
    {
        mSprings[i]->springK = edgeSpringK;
        mSprings[i]->damping = edgeSpringDamp;
    }
}

void SpringBody::setSpringConstants(int springID, float springK, float springDamp)
{
    // index is for all internal springs, AFTER the default internal springs.
    int index = mPointMasses.size() + springID;
    mSprings[index]->springK = springK;
    mSprings[index]->damping = springDamp;
}

float SpringBody::getSpringK(int springID)
{
    int index = mPointMasses.size() + springID;
    return mSprings[index]->springK;
}

float SpringBody::getSpringDamping(int springID)
{
    int index = mPointMasses.size() + springID;
    return mSprings[index]->damping;
}

void SpringBody::accumulateInternalForce2()
{
	Vector2 force;
    for (unsigned int i = 0; i < mSprings.size(); i++)
    {
        InternalSpring *s = mSprings[i];
		VectorTools::calculateSpringForce(mPointMasses[s->pointMassA]->Position, mPointMasses[s->pointMassA]->Velocity,
            mPointMasses[s->pointMassB]->Position, mPointMasses[s->pointMassB]->Velocity,
            s->springD, s->springK, s->damping,
            force);

        mPointMasses[s->pointMassA]->Force.X += force.X;
        mPointMasses[s->pointMassA]->Force.Y += force.Y;

        mPointMasses[s->pointMassB]->Force.X -= force.X;
        mPointMasses[s->pointMassB]->Force.Y -= force.Y;
    }

    // shape matching forces.
    if (mShapeMatchingOn)
    {
        mBaseShape->transformVertices( mDerivedPos, mDerivedAngle, mScale, mGlobalShape);
        for (unsigned int i = 0; i < mPointMasses.size(); i++)
        {
            if (mShapeSpringK > 0.0f)
            {
				force = VectorTools::calculateSpringForce(mPointMasses[i]->Position, mPointMasses[i]->Velocity,
                    mGlobalShape[i], mPointMasses[i]->Velocity, 0.0f, mShapeSpringK, mShapeSpringDamp);

                mPointMasses[i]->Force.X += force.X;
                mPointMasses[i]->Force.Y += force.Y;
            }
        }
    }
}

void SpringBody::accumulateInternalForces()
{
    accumulateInternalForce2();
}

void SpringBody::addTriangle(int A, int B, int C)
{
	mIndexList.push_back(A);
    mIndexList.push_back(B);
    mIndexList.push_back(C);
}

void SpringBody::finalizeTriangles()
{
	mIndicesCount = mIndexList.size();
    mIndices = new int[mIndexList.size()];
    for (unsigned int i = 0; i < mIndexList.size(); i++)
        mIndices[i] = mIndexList[i];
}

void SpringBody::accumulateExternalForces()
{
   // base.accumulateExternalForces();

    // gravity!
    for (unsigned int i = 0; i < mPointMasses.size(); i++)
		mPointMasses[i]->Force += Vector2(0, -9.8f * ((PointMass*)mPointMasses.at(i))->Mass);

	if (dragPoint != -1)
		mPointMasses[dragPoint]->Force += dragForce;

    dragPoint = -1;
}

void SpringBody::setDragForce(Vector2 force, int pm)
{
	dragForce = force * 2;
	dragPoint = pm;
}
