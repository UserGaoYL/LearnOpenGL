#include <iostream>


extern int StartHelloWindow();
extern int StartHelloTriangle();
extern int StartShaderWindow();


int main()
{
	printf("Hello OpenGL\n");	
	return StartShaderWindow();
}

