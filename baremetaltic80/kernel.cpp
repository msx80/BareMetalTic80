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

static tic80_input tic_input;

#define MAXBUFLEN (1024*1024)



CKernel::CKernel (void)
:	CStdlibAppStdio ("Tic-80")
{
	mActLED.Blink (5);	// show we are alive
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

void* loadFile(char* filename, u32* size)
{
  char source[MAXBUFLEN];
  FILE *fp = fopen(filename, "rb");
  if (fp != NULL) {
    size_t newLen = fread(source, sizeof(char), MAXBUFLEN, fp);
    if ( ferror( fp ) != 0 ) {
        fputs("Error reading file", stderr);
    } else {
       // source[newLen++] = '\0'; /* Just to be safe. */
    }

    fclose(fp);
    printf("STREAM SIZE is %d\n", newLen);
    void* cart = malloc(newLen);
    memcpy(cart, source, newLen);
    *size = newLen;
    return cart;
  }
  else
  {
    return 0;
  }
}

void CKernel::KeyPressedHandler (const char *pString)
{
	int len = strlen(pString);
	//printf("SIZE OF STRING: %d\n", strlen(pString));
	//printf(pString);
	if (len==1)
	{
	
		tic_input.gamepads.first.a = true;
	}
	
}
void CKernel::KeyStatusHandlerRaw (unsigned char ucModifiers, const unsigned char RawKeys[6])
{

	tic_input.gamepads.first.data = 0;
	

//	printf("MODIF %02x ", ucModifiers);
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

//	printf("\n");
}
CStdlibApp::TShutdownMode CKernel::Run (void)
{
	mLogger.Write (GetKernelName (), LogNotice, "TIC80 Port test");

	mLogger.Write (GetKernelName (), LogNotice, "stdio test...");


	CUSBKeyboardDevice *pKeyboard = (CUSBKeyboardDevice *) mDeviceNameService.GetDevice ("ukbd1", FALSE);
	if (pKeyboard == 0)
	{
		mLogger.Write (GetKernelName(), LogError, "Keyboard not found");

		return ShutdownHalt;
	}
	pKeyboard->RegisterKeyStatusHandlerRaw (KeyStatusHandlerRaw);

	printf("Hello world!\n");
	fprintf(stderr, "Hello world on stderr!\n");

	CScreenDevice* screen = &mScreen;
	printf("Screen is:\n");
	printf("%d x %d pitch: %d\n", screen->GetWidth(), screen->GetHeight(), screen->GetPitch());

	printf("Creating tic80 instance..\n");

	tic80* tic = tic80_create(44100);
	printf("tic80: %p\n", tic);
	printf("screen: %p\n", tic->screen);

	printf("Loading cart.tic...\n");

	u32 size;
        void* cart = loadFile("cart.tic", &size);

	        if(cart)
	        {
			tic80_load(tic, cart, size);
		}
		else
		{
			printf("no cart\n");
		}

	printf("screen: %p\n", tic->screen);
	printf("screen: %p\n", tic->screen);

		screen->GetBuffer()[0] = 123456789;
		screen->GetBuffer()[239] = 13456789;
		screen->GetBuffer()[135*240+239] = 13456789;


	CTimer::SimpleMsDelay(5000);

	
	for(int i=0;i<10000;i++)
	{
		//printf("tic...");
		tic80_tick(tic, tic_input);
		screenCopy(screen, tic);

		screen->GetBuffer()[0] = 123456789;
		
		screen->vsync();
	}

	printf("Type some characters and hit <RETURN>\n");

	char line[200];
	if (fgets(line, sizeof(line), stdin) != nullptr)
	{
		printf("Read '%s' from stdin...\n", line);
	}
	else
	{
		perror("fgets returned NULL");
	}

	char outstr[200];
        time_t const t = time (nullptr);
        struct tm * const tmp = localtime (&t);

        if (tmp == nullptr)
        {
                perror("localtime");
        }
        else if (strftime(outstr, sizeof(outstr), "%D %T", tmp) == 0)
        {
                fprintf(stderr, "strftime returned 0");
        }
        else
        {
                // Do not expect a valid current time as the Raspberry Pi
                // clock has not been set.
                printf("The current date/time is \"%s\"\n", outstr);
        }

	mLogger.Write (GetKernelName (), LogNotice, "C Standard Library Demo finished");

	return ShutdownHalt;
}
