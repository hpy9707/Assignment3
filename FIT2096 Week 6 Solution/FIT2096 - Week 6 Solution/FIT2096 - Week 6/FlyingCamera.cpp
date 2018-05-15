#include "FlyingCamera.h"
#include "MathsHelper.h"

Vector3 FlyingCamera::Getforward(float heading)
{
	Vector3 forward;
	//look back
	if (heading < ToRadians(-135.0f)) {
		forward = Vector3(0, 0, -1);
	}//look left
	else if (heading < ToRadians(-45.0f)) {
		forward = Vector3(-1, 0, 0);
	}//look front
	else if (heading < ToRadians(45.0f)) {
		forward = Vector3(0, 0, 1);
	}//look right
	else if (heading < ToRadians(135.0f)) {
		forward = Vector3(1, 0, 0);
	}//reamaing part still look back
	else
	{
		forward = Vector3(0, 0, -1);
	}

	return forward;
}

Vector3 FlyingCamera::Getright(float heading)
{
	Vector3 right;
	//look back
	if (heading < ToRadians(-135.0f)) {
		right = Vector3(-1, 0, 0);
	}//look left
	else if (heading < ToRadians(-45.0f)) {
		right = Vector3(0, 0, 1);
	}//look front
	else if (heading < ToRadians(45.0f)) {
		right = Vector3(1, 0, 0);
	}//look right
	else if (heading < ToRadians(135.0f)) {
		right = Vector3(0, 0, -1);
	}//reamaing part still look back
	else
	{
		right = Vector3(-1, 0, 0);
	}
	return right;
}

FlyingCamera::FlyingCamera(InputController* input, Vector3 startPos)
{
	m_input = input;
	SetPosition(startPos);

	m_moveSpeed = 10.0f;
	m_heightChangeSpeed = 10.0f;
	m_rotationSpeed = 0.50f;

	m_heading = 0.0f;
	m_pitch = 0.0f;
}

void FlyingCamera::Update(float timestep)
{
	// Accumulate change in mouse position 
	m_heading += m_input->GetMouseDeltaX() * m_rotationSpeed * timestep;
	m_pitch += m_input->GetMouseDeltaY() * m_rotationSpeed * timestep;
	
	
	m_pitch = MathsHelper::Clamp(m_pitch, ToRadians(-70.0f), ToRadians(70.0f));
	if (m_heading > ToRadians(180.0f)) { 
		while (m_heading > PI) 
		{ m_heading -= 2 * PI; } 
	}
	if (m_heading < ToRadians(-180.0f)) {
		while (m_heading < -PI) {
			m_heading += 2 * PI;
		}
	}
	Matrix heading = Matrix::CreateRotationY(m_heading);
	Matrix pitch = Matrix::CreateRotationX(m_pitch);

	
	Vector3 localRight = Getright(m_heading);

	
	Vector3 localForwardXZ = Getforward(m_heading);

	
	Vector3 currentPos = GetPosition();
	
	/*if (m_input->GetKeyDown('W'))
	{
		currentPos += localForwardXZ ;
	}
	if (m_input->GetKeyDown('S'))
	{
		currentPos -= localForwardXZ ;
	}
	if (m_input->GetKeyDown('A'))
	{
		currentPos -= localRight;
	}
	if (m_input->GetKeyDown('D'))
	{
		currentPos += localRight ;
	}*/
	

	// Combine pitch and heading into one matrix for convenience
	Matrix lookAtRotation = pitch * heading;

	// Transform a world forward vector into local space (take pitch and heading into account)
	Vector3 lookAt = Vector3::TransformNormal(Vector3(0, 0, 1), lookAtRotation);

	// At this point, our look-at vector is still relative to the origin
	// Add our position to it so it originates from the camera and points slightly in front of it
	// Remember the look-at vector needs to describe a point in the world relative to the origin
	lookAt += currentPos;

	// Use parent's mutators so isDirty flags get flipped
	SetLookAt(lookAt);
	SetPosition(currentPos);

	// Give our parent a chance to regenerate the view matrix
	Camera::Update(timestep);
}
