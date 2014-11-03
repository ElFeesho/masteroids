#ifndef __DEBUG_H_H_H__
#define __DEBUG_H_H_H__
/* Yeah quite a fruity inclusion guard, but debug is popular */

#include <network.h>

class Debug // Namespace?
{
public:
	Debug();
	~Debug();
	// STATIC!
	static void init();
	static void send_message(char *message); 
	static int sock;
	static bool initd;
	static struct sockaddr_in dst;
};

#endif
