//
// kernel.cpp
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include "kernel.h"
#include "customscreen.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <tic80.h>
#include <cstring>
#include <cerrno>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <circle/usb/usbkeyboard.h>
#include "utils.h"
#include <limits.h>

static tic80_input tic_input;

CKernel::CKernel (void)
:	CStdlibAppStdio ("Tic-80")
{
}

void screenCopy(CScreenDevice* screen, tic80* tic)
{
 u32 pitch = screen->GetPitch();
 u32* buf = screen->GetBuffer();
 u32* ts = tic -> screen;
 for (int y = 0; y<136;y++)
 for (int x = 0; x<240;x++)
  {
	u32 p = ts[(y+8)*(8+240+8)+(x+8)];
	buf[pitch*y + x] = p;
  }
/*
	for (int y = 0; y<SCREEN_HEIGHT; y++)
	{
		u32* src = (tic->screen) + y*SCREEN_WIDTH;
		TScreenColor* dest = screen->GetBuffer()+ y * screen->GetPitch();
		memcpy(dest, src, SCREEN_WIDTH*4);
	}
*/
//	memcpy(screen->GetBuffer(), tic->screen, 240*136*4);
}

void CKernel::KeyStatusHandlerRaw (unsigned char ucModifiers, const unsigned char RawKeys[6])
{

	tic_input.gamepads.first.data = 0;

	for (unsigned i = 0; i < 6; i++)
	{
		if (RawKeys[i] != 0)
		{
			switch(RawKeys[i])
			{
				case 0x1d: tic_input.gamepads.first.a = true; break;
				case 0x1b: tic_input.gamepads.first.b = true; break;
				case 0x52: tic_input.gamepads.first.up = true; break;
				case 0x51: tic_input.gamepads.first.down = true; break;
				case 0x50: tic_input.gamepads.first.left = true; break;
				case 0x4F: tic_input.gamepads.first.right = true; break;
			}

		}
	}
}
CStdlibApp::TShutdownMode CKernel::Die(const char *msg)
{
	printf("FATAL\n");
	printf(msg);
	CTimer::SimpleMsDelay(100000);
	return ShutdownHalt;
}

CStdlibApp::TShutdownMode CKernel::Run (void)
{
	mLogger.Write (GetKernelName (), LogNotice, "TIC80 Port");

	CUSBKeyboardDevice *pKeyboard = (CUSBKeyboardDevice *) mDeviceNameService.GetDevice ("ukbd1", FALSE);
	if (pKeyboard == 0)
	{
		return Die("Keyboard not found");
	}


	CScreenDevice* screen = &mScreen;
	printf("Screen is:\n");
	printf("%d x %d pitch: %d\n", screen->GetWidth(), screen->GetHeight(), screen->GetPitch());

	printf("Creating tic80 instance..\n");

	tic80* tic = tic80_create(44100);
	if( !tic)
	{
		return Die("Could not tic80_create");
	}
	printf("tic80: %p\n", tic);
	printf("Loading cart.tic...\n");

	u32 size;
        void* cart = loadFile("cart.tic", &size);

        if(cart)
        {
		tic80_load(tic, cart, size);
	}
	else
	{
		return Die("Could not load cart");
	}


	// CTimer::SimpleMsDelay(5000);

	pKeyboard->RegisterKeyStatusHandlerRaw (KeyStatusHandlerRaw);


	while(true)
	{
		tic80_tick(tic, tic_input);
		screenCopy(screen, tic);
		screen->vsync();
	}

	return ShutdownHalt;
}
