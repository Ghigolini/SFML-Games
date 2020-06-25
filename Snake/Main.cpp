#include "Window_.h"

int main() {
	Window_ window(Vector2f(1920, 1080), "SFML", true);
	window.Run();
	return 0;
}
