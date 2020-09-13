#ifndef _variables_
#define _variables_
namespace variables {

	constexpr float width = 1024.0f;
	constexpr float height = 800.0f;
	constexpr float viewAngle = 45.0f;
	float deltaTime = 0.0f, currentFrame = 0.0f, lastFrame = 0.0f;

	const double refreshValue = 1.0E-1; // increasing causes accuracy drop

	const double constG = 6.6743E-24;
}
#endif