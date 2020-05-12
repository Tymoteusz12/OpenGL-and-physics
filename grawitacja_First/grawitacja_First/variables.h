namespace variables {

	float width = 800.0f;
	float height = 600.0f;
	float viewAngle = 45.0f;
	float deltaTime = 0.0f, currentFrame = 0.0f, lastFrame = 0.0f;

	float moveDeltaTime = 0.0f, moveCurrentFrame = 0.0f, moveLastFrame = 0.0f, moveFrameAfter;

	const float scale = 1.0E-2;

	const float refreshValue = 1.0E-2;
	const float sunRadius = 6.9634E8 * scale;
	const float sunScale = 10000.0f;
	int skipVar = 0;

	const float constG(0.1f);
}
