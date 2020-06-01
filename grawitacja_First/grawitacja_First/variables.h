#ifndef _variables_
#define _variables_
namespace variables {

	float width = 800.0f;
	float height = 600.0f;
	float viewAngle = 45.0f;
	float deltaTime = 0.0f, currentFrame = 0.0f, lastFrame = 0.0f;

	float moveDeltaTime = 0.0f, moveCurrentFrame = 0.0f, moveLastFrame = 0.0f, moveFrameAfter;

	const float refreshValue = 1.0E-5;

	const float constG(1.0f);
}
#endif