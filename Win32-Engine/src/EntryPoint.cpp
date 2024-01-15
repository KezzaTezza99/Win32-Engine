#include <iostream>
#include "Graphics/Window.h"
#include "Utilities/Colours.h"

//Having a global variable for the window to temp pass it around (won't stay like this hopefully)
Window* gameWindow = new Window();

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//Getting user input

	//Clearing the back buffer

	//Drawing to the screen

	//Game loop
	while (gameWindow->IsRunning())
	{
		//Storing the users messages to read 
		MSG message;

		//Resetting Input
		//input.ResetKeysPressed();

		//Keys keys{};

		//reading the messages to see if need to exit
		while (PeekMessage(&message, gameWindow->GetWindow(), 0, 0, PM_REMOVE))
		{
			//Handle Keyboard Input
			switch (message.message)
			{
				//Would handle keyboard messages here
				default:
				{
					//Dispatch messages
					TranslateMessage(&message);

					DispatchMessage(&message);
				}
			}
		}

		//Simulate game or application here

		//Drawing a single red pixel for now
		gameWindow->GetRenderer()->DrawPixel(gameWindow->GetRenderer()->GetCentreX(), gameWindow->GetRenderer()->GetCentreY(), RED);

		//Rendering the buffer to the screen
		BITMAPINFO data = gameWindow->GetRenderer()->GetBitmapBufferInfo();
		StretchDIBits(gameWindow->GetWindowContext(), 0, 0, gameWindow->GetRenderer()->GetBufferWidth(), gameWindow->GetRenderer()->GetBufferHeight(), 0, 0,
			gameWindow->GetRenderer()->GetBufferWidth(), gameWindow->GetRenderer()->GetBufferHeight(), gameWindow->GetRenderer()->GetMemoryBuffer(),
			&data, DIB_RGB_COLORS, SRCCOPY);
	}
}