
#include "core.h"
#include "window.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"
#include "timer.h"

#include <vector>
#include <unordered_map>
#include <ctime>
#include <string>
#include <iostream>


#define WIDTH 1024
#define HEIGHT 768

bool float_comp(float f1, float f2, float abs_tol) {
	return abs(f1 - f2) <= abs_tol * std::fmaxf(1.0f, std::fmaxf(f1, f2));
}

auto main(int argc, char* argv[]) -> int
{
	InitEngine();

	Window window(800, 600, "Monkeys");
	Window window2(800, 600, "Monkeys2");
	window.Focus();
	window.DrawTo();

	Mesh mesh2("./res/monkey3.obj");
	Shader shader("./res/basicShader");
	Texture texture("./res/texture1.jpg");

	Camera camera(glm::vec3(0, 0, -6), 70.0f, (float) WIDTH / (float) HEIGHT, 0.01f, 1000.0f);

	Transform transform;
	transform.Rotation().y = (float) M_PI;

	Timer t1;
	t1.run();

	while (!window.IsClosedRequested() || !window2.IsClosedRequested())
	{
		window.Clear(0.1f, 0.095f, 0.1f, 1.0f);
		window2.Clear(0.1f, 0.095f, 0.1f, 1.0f);

		texture.Bind(0);
		shader.Bind();
		transform.Rotation().y = (float)t1.timeElapsed();

		float pos1 = 1.8f - (float)t1.timeElapsed() * 0.7f;
		transform.Position().x = pos1;
		shader.Update(transform, camera);
		mesh2.Draw(GL_TRIANGLES);

		float pos2 = -1.8f + (float)t1.timeElapsed() * 0.7f;
		transform.Position().x = pos2;
		shader.Update(transform, camera);
		mesh2.Draw(GL_LINES);

		window.Update();
		window2.Update();

		if (window.IsClosedRequested())
			window.Hide();
		if (window2.IsClosedRequested())
			window2.Hide();
	}
	return 0;
}