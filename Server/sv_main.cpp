#include "Server.h"


int main() {
	Server server(5000);
	server.init();
	server.run();

}
