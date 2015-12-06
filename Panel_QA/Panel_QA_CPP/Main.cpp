#include <stdio.h>
#include "Panel.h"

int main() {
	Panel *panel = new Panel();
	// panel->ShowMessage("Test message");
	free(panel);

	printf("End of the test program\n");
	system("pause");
	return 0;
}