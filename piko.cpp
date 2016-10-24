#include <mednafen/mednafen.h>

#include <mednafen/MemoryStream.h>
#include <SDL.h>
#include <SDL_syswm.h>
#include <Uxtheme.h>
#include <olectl.h>

#define HIMETRIC_INCH 2540
#define MAP_LOGHIM_TO_PIX(x,ppli) ( ((ppli)*(x) + HIMETRIC_INCH/2) / HIMETRIC_INCH ) 

#ifndef PAL_VIEW
const int output_height = 240;
#else
const int output_height = 224;
#endif

char working_dir[1024];



void get_working_dir(void)
{
	int i;

	GetModuleFileNameA(0, working_dir, 1024);

	for (i = strlen(working_dir) - 1;i >= 0;--i)
	{
		if (working_dir[i] == '\\' || working_dir[i] == '/')
		{
			working_dir[i + 1] = 0;
			break;
		}
	}
}



void MDFN_DispMessage(const char *format, ...) noexcept
{

}

void MDFN_PrintError(const char *format, ...) noexcept
{

}

bool MDFN_DumpToFile(const std::string& path, const std::vector<PtrLengthPair> &pearpairs, bool throw_on_error)
{
	return false;
}

std::unique_ptr<Stream> MDFN_AmbigGZOpenHelper(const std::string& path, std::vector<size_t> good_sizes)
{
	return NULL;
}

bool MDFNSS_StateAction(StateMem *sm, const unsigned load, const bool data_only, SFORMAT *sf, const char *sname, const bool optional) noexcept
{
	// !TODO: ugly hack, using it to save my time
	char* fileName = (char*)sm;

	if (load)
	{
		FILE* file = fopen(fileName, "rb");

		if (file)
		{
			fread(sf->v, sf->size, 1, file);
			fclose(file);
		}

	}
	else
	{
		FILE* file = fopen(fileName, "wb");

		if (file)
		{
			fwrite(sf->v, sf->size, 1, file);
			fclose(file);
		}
	}

	return true;
}

uint64 MDFN_GetSettingUI(const char *name)
{
	return 0;
}

int64 MDFN_GetSettingI(const char *name)
{
	return 0;
}

double MDFN_GetSettingF(const char *name)
{
	return 0;
}

bool MDFN_GetSettingB(const char *name)
{
	return false;
}

std::string MDFN_GetSettingS(const char *name)
{
	return "";
}

void MDFN_MidLineUpdate(EmulateSpecStruct *espec, int y)
{

}

std::string MDFN_MakeFName(int type, int id1, const char *cd1) 
{
	return "";
}

bool MDFNMP_Init(uint32 ps, uint32 numpages)
{
	return true;
}

void MDFNMP_AddRAM(uint32 size, uint32 address, uint8 *RAM, bool use_in_search)
{

}

void MDFNMP_ApplyPeriodicCheats(void)
{

}

void Player_Draw(MDFN_Surface *surface, MDFN_Rect *dr, int CurrentSong, int16 *samples, int32 sampcount)
{

}

extern MDFNGI EmulatedSNES;
MDFNGI *MDFNGameInfo = &EmulatedSNES;

MDFNFILE::MDFNFILE(const char *path, const FileExtensionSpecStruct *known_ext, const char *purpose) : ext((const char * const &)f_ext), fbase((const char * const &)f_fbase)
{
	f_ext = NULL;
	f_fbase = NULL;

	Open(path, known_ext, purpose);
}

MDFNFILE::~MDFNFILE()
{
	Close();
}

void MDFNFILE::Close(void) throw()
{
	if (f_ext)
	{
		free(f_ext);
		f_ext = NULL;
	}

	if (f_fbase)
	{
		free(f_fbase);
		f_fbase = NULL;
	}

	if (str.get())
	{
		delete str.release();
	}
}

static int PendingLoadRom = 0;

void LoadRom(int id)
{
	PendingLoadRom = id;
}

static const SDL_Scancode windows_scancode_table[] =
{
	/*	0						1							2							3							4						5							6							7 */
	/*	8						9							A							B							C						D							E							F */
	SDL_SCANCODE_UNKNOWN,		SDL_SCANCODE_ESCAPE,		SDL_SCANCODE_1,				SDL_SCANCODE_2,				SDL_SCANCODE_3,			SDL_SCANCODE_4,				SDL_SCANCODE_5,				SDL_SCANCODE_6,			/* 0 */
	SDL_SCANCODE_7,				SDL_SCANCODE_8,				SDL_SCANCODE_9,				SDL_SCANCODE_0,				SDL_SCANCODE_MINUS,		SDL_SCANCODE_EQUALS,		SDL_SCANCODE_BACKSPACE,		SDL_SCANCODE_TAB,		/* 0 */

	SDL_SCANCODE_Q,				SDL_SCANCODE_W,				SDL_SCANCODE_E,				SDL_SCANCODE_R,				SDL_SCANCODE_T,			SDL_SCANCODE_Y,				SDL_SCANCODE_U,				SDL_SCANCODE_I,			/* 1 */
	SDL_SCANCODE_O,				SDL_SCANCODE_P,				SDL_SCANCODE_LEFTBRACKET,	SDL_SCANCODE_RIGHTBRACKET,	SDL_SCANCODE_RETURN,	SDL_SCANCODE_LCTRL,			SDL_SCANCODE_A,				SDL_SCANCODE_S,			/* 1 */

	SDL_SCANCODE_D,				SDL_SCANCODE_F,				SDL_SCANCODE_G,				SDL_SCANCODE_H,				SDL_SCANCODE_J,			SDL_SCANCODE_K,				SDL_SCANCODE_L,				SDL_SCANCODE_SEMICOLON,	/* 2 */
	SDL_SCANCODE_APOSTROPHE,	SDL_SCANCODE_GRAVE,			SDL_SCANCODE_LSHIFT,		SDL_SCANCODE_BACKSLASH,		SDL_SCANCODE_Z,			SDL_SCANCODE_X,				SDL_SCANCODE_C,				SDL_SCANCODE_V,			/* 2 */

	SDL_SCANCODE_B,				SDL_SCANCODE_N,				SDL_SCANCODE_M,				SDL_SCANCODE_COMMA,			SDL_SCANCODE_PERIOD,	SDL_SCANCODE_SLASH,			SDL_SCANCODE_RSHIFT,		SDL_SCANCODE_PRINTSCREEN,/* 3 */
	SDL_SCANCODE_LALT,			SDL_SCANCODE_SPACE,			SDL_SCANCODE_CAPSLOCK,		SDL_SCANCODE_F1,			SDL_SCANCODE_F2,		SDL_SCANCODE_F3,			SDL_SCANCODE_F4,			SDL_SCANCODE_F5,		/* 3 */

	SDL_SCANCODE_F6,			SDL_SCANCODE_F7,			SDL_SCANCODE_F8,			SDL_SCANCODE_F9,			SDL_SCANCODE_F10,		SDL_SCANCODE_NUMLOCKCLEAR,	SDL_SCANCODE_SCROLLLOCK,	SDL_SCANCODE_HOME,		/* 4 */
	SDL_SCANCODE_UP,			SDL_SCANCODE_PAGEUP,		SDL_SCANCODE_KP_MINUS,		SDL_SCANCODE_LEFT,			SDL_SCANCODE_KP_5,		SDL_SCANCODE_RIGHT,			SDL_SCANCODE_KP_PLUS,		SDL_SCANCODE_END,		/* 4 */

	SDL_SCANCODE_DOWN,			SDL_SCANCODE_PAGEDOWN,		SDL_SCANCODE_INSERT,		SDL_SCANCODE_DELETE,		SDL_SCANCODE_UNKNOWN,	SDL_SCANCODE_UNKNOWN,		SDL_SCANCODE_NONUSBACKSLASH,SDL_SCANCODE_F11,		/* 5 */
	SDL_SCANCODE_F12,			SDL_SCANCODE_PAUSE,			SDL_SCANCODE_UNKNOWN,		SDL_SCANCODE_LGUI,			SDL_SCANCODE_RGUI,		SDL_SCANCODE_APPLICATION,	SDL_SCANCODE_UNKNOWN,		SDL_SCANCODE_UNKNOWN,	/* 5 */

	SDL_SCANCODE_UNKNOWN,		SDL_SCANCODE_UNKNOWN,		SDL_SCANCODE_UNKNOWN,		SDL_SCANCODE_UNKNOWN,		SDL_SCANCODE_F13,		SDL_SCANCODE_F14,			SDL_SCANCODE_F15,			SDL_SCANCODE_F16,		/* 6 */
	SDL_SCANCODE_F17,			SDL_SCANCODE_F18,			SDL_SCANCODE_F19,			SDL_SCANCODE_UNKNOWN,		SDL_SCANCODE_UNKNOWN,	SDL_SCANCODE_UNKNOWN,		SDL_SCANCODE_UNKNOWN,		SDL_SCANCODE_UNKNOWN,	/* 6 */

	SDL_SCANCODE_INTERNATIONAL2,		SDL_SCANCODE_UNKNOWN,		SDL_SCANCODE_UNKNOWN,		SDL_SCANCODE_INTERNATIONAL1,		SDL_SCANCODE_UNKNOWN,	SDL_SCANCODE_UNKNOWN,		SDL_SCANCODE_UNKNOWN,		SDL_SCANCODE_UNKNOWN,	/* 7 */
	SDL_SCANCODE_UNKNOWN,		SDL_SCANCODE_INTERNATIONAL4,		SDL_SCANCODE_UNKNOWN,		SDL_SCANCODE_INTERNATIONAL5,		SDL_SCANCODE_UNKNOWN,	SDL_SCANCODE_INTERNATIONAL3,		SDL_SCANCODE_UNKNOWN,		SDL_SCANCODE_UNKNOWN	/* 7 */
};

#define CONTROLLER_BUTTONS 12

static WNDPROC OldEditProc = NULL;

static SDL_Scancode WindowsScanCodeToSDLScanCode(LPARAM lParam, WPARAM wParam)
{
	SDL_Scancode code;
	char bIsExtended;
	int nScanCode = (lParam >> 16) & 0xFF;

	/* 0x45 here to work around both pause and numlock sharing the same scancode, so use the VK key to tell them apart */
	if (nScanCode == 0 || nScanCode == 0x45) {
		switch (wParam) {
		case VK_CLEAR: return SDL_SCANCODE_CLEAR;
		case VK_MODECHANGE: return SDL_SCANCODE_MODE;
		case VK_SELECT: return SDL_SCANCODE_SELECT;
		case VK_EXECUTE: return SDL_SCANCODE_EXECUTE;
		case VK_HELP: return SDL_SCANCODE_HELP;
		case VK_PAUSE: return SDL_SCANCODE_PAUSE;
		case VK_NUMLOCK: return SDL_SCANCODE_NUMLOCKCLEAR;

		case VK_F13: return SDL_SCANCODE_F13;
		case VK_F14: return SDL_SCANCODE_F14;
		case VK_F15: return SDL_SCANCODE_F15;
		case VK_F16: return SDL_SCANCODE_F16;
		case VK_F17: return SDL_SCANCODE_F17;
		case VK_F18: return SDL_SCANCODE_F18;
		case VK_F19: return SDL_SCANCODE_F19;
		case VK_F20: return SDL_SCANCODE_F20;
		case VK_F21: return SDL_SCANCODE_F21;
		case VK_F22: return SDL_SCANCODE_F22;
		case VK_F23: return SDL_SCANCODE_F23;
		case VK_F24: return SDL_SCANCODE_F24;

		case VK_OEM_NEC_EQUAL: return SDL_SCANCODE_KP_EQUALS;
		case VK_BROWSER_BACK: return SDL_SCANCODE_AC_BACK;
		case VK_BROWSER_FORWARD: return SDL_SCANCODE_AC_FORWARD;
		case VK_BROWSER_REFRESH: return SDL_SCANCODE_AC_REFRESH;
		case VK_BROWSER_STOP: return SDL_SCANCODE_AC_STOP;
		case VK_BROWSER_SEARCH: return SDL_SCANCODE_AC_SEARCH;
		case VK_BROWSER_FAVORITES: return SDL_SCANCODE_AC_BOOKMARKS;
		case VK_BROWSER_HOME: return SDL_SCANCODE_AC_HOME;
		case VK_VOLUME_MUTE: return SDL_SCANCODE_AUDIOMUTE;
		case VK_VOLUME_DOWN: return SDL_SCANCODE_VOLUMEDOWN;
		case VK_VOLUME_UP: return SDL_SCANCODE_VOLUMEUP;

		case VK_MEDIA_NEXT_TRACK: return SDL_SCANCODE_AUDIONEXT;
		case VK_MEDIA_PREV_TRACK: return SDL_SCANCODE_AUDIOPREV;
		case VK_MEDIA_STOP: return SDL_SCANCODE_AUDIOSTOP;
		case VK_MEDIA_PLAY_PAUSE: return SDL_SCANCODE_AUDIOPLAY;
		case VK_LAUNCH_MAIL: return SDL_SCANCODE_MAIL;
		case VK_LAUNCH_MEDIA_SELECT: return SDL_SCANCODE_MEDIASELECT;

		case VK_OEM_102: return SDL_SCANCODE_NONUSBACKSLASH;

		case VK_ATTN: return SDL_SCANCODE_SYSREQ;
		case VK_CRSEL: return SDL_SCANCODE_CRSEL;
		case VK_EXSEL: return SDL_SCANCODE_EXSEL;
		case VK_OEM_CLEAR: return SDL_SCANCODE_CLEAR;

		case VK_LAUNCH_APP1: return SDL_SCANCODE_APP1;
		case VK_LAUNCH_APP2: return SDL_SCANCODE_APP2;

		default: return SDL_SCANCODE_UNKNOWN;
		}
	}

	if (nScanCode > 127)
		return SDL_SCANCODE_UNKNOWN;

	code = windows_scancode_table[nScanCode];

	bIsExtended = (lParam & (1 << 24)) != 0;
	if (!bIsExtended) {
		switch (code) {
		case SDL_SCANCODE_HOME:
			return SDL_SCANCODE_KP_7;
		case SDL_SCANCODE_UP:
			return SDL_SCANCODE_KP_8;
		case SDL_SCANCODE_PAGEUP:
			return SDL_SCANCODE_KP_9;
		case SDL_SCANCODE_LEFT:
			return SDL_SCANCODE_KP_4;
		case SDL_SCANCODE_RIGHT:
			return SDL_SCANCODE_KP_6;
		case SDL_SCANCODE_END:
			return SDL_SCANCODE_KP_1;
		case SDL_SCANCODE_DOWN:
			return SDL_SCANCODE_KP_2;
		case SDL_SCANCODE_PAGEDOWN:
			return SDL_SCANCODE_KP_3;
		case SDL_SCANCODE_INSERT:
			return SDL_SCANCODE_KP_0;
		case SDL_SCANCODE_DELETE:
			return SDL_SCANCODE_KP_PERIOD;
		case SDL_SCANCODE_PRINTSCREEN:
			return SDL_SCANCODE_KP_MULTIPLY;
		default:
			break;
		}
	}
	else {
		switch (code) {
		case SDL_SCANCODE_RETURN:
			return SDL_SCANCODE_KP_ENTER;
		case SDL_SCANCODE_LALT:
			return SDL_SCANCODE_RALT;
		case SDL_SCANCODE_LCTRL:
			return SDL_SCANCODE_RCTRL;
		case SDL_SCANCODE_SLASH:
			return SDL_SCANCODE_KP_DIVIDE;
		case SDL_SCANCODE_CAPSLOCK:
			return SDL_SCANCODE_KP_PLUS;
		default:
			break;
		}
	}

	return code;
}

struct PlayerButton
{
	enum
	{
		KEYBOARD,
		GAMEPAD
	}type;

	union
	{
		SDL_Scancode code;

		struct
		{
			bool hat;
			int value;
			SDL_JoystickGUID guid;
		};
	};

	PlayerButton()
		: type(KEYBOARD), code(SDL_SCANCODE_UNKNOWN), hat(false), value(0)
	{
		memset(&guid, 0, sizeof(SDL_JoystickGUID));
	}

	const char* getName()
	{
		if (type == PlayerButton::KEYBOARD)
			return SDL_GetScancodeName(code);
		else if (type == PlayerButton::GAMEPAD)
		{
			const PlayerButton* button = this;
			const int Masks[] = { SDL_HAT_UP, SDL_HAT_RIGHT, SDL_HAT_DOWN, SDL_HAT_LEFT };
			const char* Names[] = { "up", "right", "down", "left" };
			static char name[256];

			if (hat)
			{
				for (int i = 0; i < sizeof(Masks) / sizeof(Masks[0]); i++)
				{
					if (value & Masks[i])
					{
						sprintf(name, "joy %s", Names[i]);
						break;
					}
				}
			}
			else
			{
				sprintf(name, "joy btn%i", value);
			}

			return name;
		}

		return NULL;
	}
};

struct PlayerSetup
{
	PlayerButton buttons[CONTROLLER_BUTTONS];
};

#define PLAYERS_COUNT 2
struct ControllerSetup
{
	PlayerSetup player[PLAYERS_COUNT];
};

static ControllerSetup controllerSetup;

static const int EditIDs[CONTROLLER_BUTTONS] = { IDC_EDIT_UP, IDC_EDIT_DOWN, IDC_EDIT_LEFT, IDC_EDIT_RIGHT, IDC_EDIT_A, IDC_EDIT_B,
IDC_EDIT_Y, IDC_EDIT_X, IDC_EDIT_SELECT, IDC_EDIT_START, IDC_EDIT_L,  IDC_EDIT_R };

static class
{
public:
	ControllerSetup data;
	HWND tab;
	HWND dlg;

	PlayerSetup& getSelectedPlayer()
	{
		int sel = TabCtrl_GetCurSel(tab);
		return data.player[sel];
	}

	void updateButtonCodeNames()
	{
		for (int i = 0; i < CONTROLLER_BUTTONS; i++)
			SetWindowText(GetDlgItem(dlg, EditIDs[i]), ControllerSetupDialog.getSelectedPlayer().buttons[i].getName());
	}

} ControllerSetupDialog;

#define WM_JOYSTICK (WM_USER + 1000)

static int getEditControlIndex(HWND edit)
{
	int id = GetWindowLong(edit, GWL_ID);
	int i = 0;
	for (; i < CONTROLLER_BUTTONS; i++)
		if (EditIDs[i] == id) break;

	return i;
}

static int CALLBACK SubEditProc(HWND edit, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_JOYSTICK:
		{
			ControllerSetupDialog.getSelectedPlayer().buttons[getEditControlIndex(edit)] = *(PlayerButton*)lParam;			
			ControllerSetupDialog.updateButtonCodeNames();
		}
		break;
	case WM_GETDLGCODE: return DLGC_WANTALLKEYS;
	case WM_KEYDOWN:
	{
		SDL_Scancode code = WindowsScanCodeToSDLScanCode(lParam, wParam);

		if (code == SDL_SCANCODE_ESCAPE)
			code = SDL_SCANCODE_UNKNOWN;

		PlayerButton& button = ControllerSetupDialog.getSelectedPlayer().buttons[getEditControlIndex(edit)];
		button.type = PlayerButton::KEYBOARD;
		button.code = code;
		ControllerSetupDialog.updateButtonCodeNames();
	}
	case WM_CHAR:
		return FALSE;
	}

	return CallWindowProc(OldEditProc, edit, msg, wParam, lParam);
}

static int CALLBACK PlayerDlgConfig(HWND dlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:

		ControllerSetupDialog.dlg = dlg;
		EnableThemeDialogTexture(dlg, ETDT_ENABLETAB);

		memcpy(&ControllerSetupDialog.data, &controllerSetup, sizeof(ControllerSetup));

		for (int i = 0; i < CONTROLLER_BUTTONS; i++)
			OldEditProc = (WNDPROC)SetWindowLongPtr(GetDlgItem(dlg, EditIDs[i]), GWLP_WNDPROC, (LONG_PTR)SubEditProc);

		ControllerSetupDialog.updateButtonCodeNames();

		return TRUE;
	}

	return FALSE;
}

static void addTabItem(HWND tab, int index)
{
	TCITEM item = { 0 };
	item.mask = TCIF_TEXT;

	char buf[] = "Player #%i";
	sprintf(buf, buf, index + 1);
	item.pszText = buf;

	TabCtrl_InsertItem(tab, index, &item);
}

int CALLBACK DlgConfig(HWND dlg, UINT msg, WPARAM wParam, LPARAM lParam);

#define JOYSTICKS_COUNT 2

class GameState
{
private:
	struct Config
	{
		Config() : scale(3), smoothing(false), fullscreen(true) {}
		int scale;
		bool smoothing;
		bool fullscreen;

		ControllerSetup controller;
	};

public:

	bool exit;
	bool pause;
	int framerate;
	SDL_Joystick* joysticks[JOYSTICKS_COUNT];
	SDL_GameController* gamepads[JOYSTICKS_COUNT];

	int getAxisMask(SDL_Joystick* joystick)
	{
		int axesCount = SDL_JoystickNumAxes(joystick);

		for (int a = 0; a < axesCount; a++)
		{
			int axe = SDL_JoystickGetAxis(joystick, a);

			if (axe)
			{
				if (a == 0)
				{
					if (axe > 16384) return SDL_HAT_RIGHT;
					else if(axe < -16384) return SDL_HAT_LEFT;
				}
				else if (a == 1)
				{
					if (axe > 16384) return SDL_HAT_DOWN;
					else if (axe < -16384) return SDL_HAT_UP;
				}
			}
		}

		return 0;
	}

	bool processGamepad(PlayerButton& button)
	{
		for (int i = 0; i < JOYSTICKS_COUNT; i++)
		{
			SDL_Joystick* joystick = joysticks[i];

			if (joystick && SDL_JoystickGetAttached(joystick))
			{
				{
					int axe = getAxisMask(joystick);

					if (axe)
					{
						button.type = PlayerButton::GAMEPAD;
						button.guid = SDL_JoystickGetDeviceGUID(i);
						button.hat = true;
						button.value = axe;

						return true;
					}
				}

				{
					int hatsCount = SDL_JoystickNumHats(joystick);

					for (int h = 0; h < hatsCount; h++)
					{
						int hat = SDL_JoystickGetHat(joystick, h);

						if (hat)
						{
							button.type = PlayerButton::GAMEPAD;
							button.guid = SDL_JoystickGetDeviceGUID(i);
							button.hat = true;
							button.value = hat;

							return true;
						}
					}
				}

				{
					int buttonsCount = SDL_JoystickNumButtons(joystick);

					for (int b= 0; b < buttonsCount; b++)
					{
						int btn = SDL_JoystickGetButton(joystick, b);

						if (btn)
						{
							button.type = PlayerButton::GAMEPAD;
							button.guid = SDL_JoystickGetDeviceGUID(i);
							button.hat = false;
							button.value = b;

							return true;
						}
					}
				}
			}
		}

		return false;
	}

	void configureControls()
	{
		if (DialogBox(NULL, MAKEINTRESOURCE(IDD_INPUTCONFIG), hwnd, DlgConfig) == IDOK)
		{
			memcpy(&controllerSetup, &ControllerSetupDialog.data, sizeof(ControllerSetup));

			saveConfig();
		}
	}

	void blit(uint32* pixels)
	{
		SDL_UpdateTexture(texture, NULL, pixels, sizeof(int) * EmulatedSNES.nominal_width);

		{
			int w, h;
			SDL_GetWindowSize(window, &w, &h);
			SDL_Rect rect;

			rect.w = w;
			rect.h = h;
			rect.x = 0;
			rect.y = 0;

			if (artwork) SDL_RenderCopy(renderer, artwork, NULL, &rect); else SDL_RenderClear(renderer);

			rect.w = EmulatedSNES.nominal_width * h / output_height;
			rect.h = h;
			rect.x = (w - rect.w) / 2;
			rect.y = 0;


			SDL_RenderCopy(renderer, texture, NULL, &rect);
		}

		SDL_RenderPresent(renderer);
	}

	void loadArtworkResource(int id)
	{
		SDL_Surface* surface;
		HDC dcPictureLoad;
		IPicture *pic = NULL;
		unsigned int* ScreenData;
		OLE_XSIZE_HIMETRIC iwdt, ihgt;
		int wdt, hgt;
		int i, j, rgb;
		unsigned int *dst;
		BITMAPINFOHEADER bmi = { 0 };

		HRSRC res = FindResource(GetModuleHandle(NULL), MAKEINTRESOURCE(id), RT_RCDATA);

		if (!res) return;

		HGLOBAL mem = LoadResource(GetModuleHandle(NULL), res);
		void *data = LockResource(mem);
		size_t sz = SizeofResource(GetModuleHandle(NULL), res);

		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, sz);
		LPVOID pvData = GlobalLock(hGlobal);
		memcpy(pvData, data, sz);
		GlobalUnlock(hGlobal);

		LPSTREAM pStream = NULL;
		HRESULT hr = CreateStreamOnHGlobal(hGlobal, TRUE, &pStream);
		OleLoadPicture(pStream, 0, FALSE, IID_IPicture, (void **)&pic);
		pStream->Release();

		pic->get_Width(&iwdt);
		pic->get_Height(&ihgt);

		HDC hScreenDC = CreateDC("DISPLAY", NULL, NULL, NULL);
		HDC hMemoryDC = CreateCompatibleDC(hScreenDC);

		wdt = MAP_LOGHIM_TO_PIX(iwdt, GetDeviceCaps(hScreenDC, LOGPIXELSX));
		hgt = MAP_LOGHIM_TO_PIX(ihgt, GetDeviceCaps(hScreenDC, LOGPIXELSX));

		HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, wdt, hgt);

		SelectObject(hMemoryDC, hBitmap);

		pic->Render(hMemoryDC, 0, 0, wdt, hgt, 0, ihgt, iwdt, -ihgt, NULL);
		pic->Release();

		bmi.biSize = sizeof(BITMAPINFOHEADER);
		bmi.biPlanes = 1;
		bmi.biBitCount = 32;
		bmi.biWidth = wdt;
		bmi.biHeight = -hgt;
		bmi.biCompression = BI_RGB;
		bmi.biSizeImage = 0;

		ScreenData = (unsigned int*)malloc(wdt * hgt*sizeof(unsigned int));

		GetDIBits(hMemoryDC, hBitmap, 0, hgt, ScreenData, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);

		surface = SDL_CreateRGBSurface(0, wdt, hgt, 32, 0, 0, 0, 0);

		SDL_LockSurface(surface);

		for (i = 0;i < hgt;++i)
		{
			dst = ((unsigned int*)surface->pixels) + i*surface->w;

			for (j = 0;j < wdt;++j)
			{
				rgb = ScreenData[i*wdt + j];

				*dst++ = rgb;
			}

		}

		SDL_UnlockSurface(surface);

		artwork = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_FreeSurface(surface);
		free(ScreenData);
		DeleteDC(hMemoryDC);
		DeleteObject(hBitmap);
		GlobalFree(hGlobal);
	}

	void loadIconResource(int id)
	{
		const int size = 48;
		const int bpp = 32;
		HICON icon;
		ICONINFO ici;
		HDC dc;
		BITMAPINFO bmi;
		SDL_Surface* surface;

		surface = SDL_CreateRGBSurface(0, size, size, bpp, 0, 0, 0, 0);

		icon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(id), IMAGE_ICON, size, size, LR_SHARED);

		GetIconInfo(icon, &ici);

		dc = CreateCompatibleDC(NULL);

		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = size;
		bmi.bmiHeader.biHeight = -size;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = bpp;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = 0;

		SelectObject(dc, ici.hbmColor);
		GetDIBits(dc, ici.hbmColor, 0, size, surface->pixels, &bmi, DIB_RGB_COLORS);
		SDL_SetWindowIcon(window, surface);
		SDL_FreeSurface(surface);

		DeleteDC(dc);

		DeleteObject(ici.hbmColor);
		DeleteObject(ici.hbmMask);

		DestroyIcon(icon);
	}
	
	void init()
	{
		window = SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_SHOWN);

		loadIconResource(IDI_ICON1);

		loadRomData(0);

		SDL_SysWMinfo info;
		SDL_VERSION(&info.version);

		if (SDL_GetWindowWMInfo(window, &info))
		{
			menu = LoadMenu(NULL, MAKEINTRESOURCE(IDR_GAMEMENU));
			hwnd = info.info.win.window;
			SetMenu(hwnd, menu);

			if (sizeof(RomTitleNames)<=sizeof(const char*))
			{
				RemoveMenu(GetSubMenu(menu, 0), 3, MF_BYPOSITION);
			}
		}

		updateSmoothing();
		updateWindowSize();
		updateFullscreen();

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET,
			EmulatedSNES.nominal_width, output_height);

		artwork = NULL;

		loadArtworkResource(IDR_ARTWORK);
	}

	void escapeFullscreen()
	{
		if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP)
			fullScreen();
	}

	void fullScreen()
	{
		config.fullscreen = !config.fullscreen;
		saveConfig();
		updateFullscreen();
	}

	void smoothing()
	{
		config.smoothing = !config.smoothing;
		saveConfig();
		updateSmoothing();
	}

	void stateAction(bool load, int slot)
	{
		if (romIndex)
		{
			char buf[256] = { 0 };
			sprintf(buf, "%i_%i.sav", romIndex, slot);

			if (!load || FileExists(buf))
				EmulatedSNES.StateAction((StateMem*)buf, load, false);

			if (!load) updateSavingMenu();
		}
	}

	void updateSavingMenu()
	{
		for (int slot = 0; slot < 9; slot++)
		{
			char filename[256] = { 0 };
			sprintf(filename, "%i_%i.sav", romIndex, slot);

			MENUITEMINFO mii = { 0 };

			mii.cbSize = sizeof(mii);
			char slotString[256] = { 0 };
			char dateString[256] = "empty";

			mii.fState = MFS_DISABLED;

			WIN32_FILE_ATTRIBUTE_DATA attr = { 0 };
			if (GetFileAttributesEx(filename, GetFileExInfoStandard, &attr))
			{
				mii.fState = MFS_ENABLED;

				FILETIME localTime = { 0 };
				FileTimeToLocalFileTime(&attr.ftLastWriteTime, &localTime);

				SYSTEMTIME sysTime;
				if (FileTimeToSystemTime(&localTime, &sysTime))
				{
					sprintf(dateString, "%02i.%02i.%04i %02i:%02i", sysTime.wDay, sysTime.wMonth, sysTime.wYear, sysTime.wHour, sysTime.wMinute);
				}
			}

			sprintf(slotString, "Slot #%i (%s)\tF%i", slot + 1, dateString, slot + 1);
			mii.dwTypeData = slotString;
			mii.fMask = MIIM_STRING | MIIM_STATE;

			SetMenuItemInfo(menu, ID_LOADGAMEPOSITION_SLOT1 + slot, FALSE, &mii);

			sprintf(slotString, "Slot #%i (%s)\tShift+F%i", slot + 1, dateString, slot + 1);
			mii.fMask = MIIM_STRING;
			SetMenuItemInfo(menu, ID_SAVEGAMEPOSITION_SLOT1 + slot, FALSE, &mii);
		}
	}

	void loadRomData(int id)
	{
		bool quick_saves;
		char filename[1024];

		strcpy(filename,working_dir);
		strcat(filename,RomFileNames[id]);

		romIndex = id;

		SDL_SetWindowTitle(window, RomTitleNames[id]);

		//quick_saves = romIndex ? true : false;
		quick_saves = true;

		EnableMenuItem(menu, 1, MF_BYPOSITION | (quick_saves ? MF_ENABLED : MF_DISABLED));
		DrawMenuBar(hwnd);

#ifdef EMBED_ROM
		MDFNFILE gameFile((const char *)(IDR_RC_ROMDATA0 + id), &EmulatedSNES.FileExtensions[0], NULL);
#else
		MDFNFILE gameFile(filename, &EmulatedSNES.FileExtensions[0], NULL);
#endif

		EmulatedSNES.Load(&gameFile);

		if (quick_saves)
			updateSavingMenu();
	}

	void resizeWindow(int scaleValue)
	{
		config.scale = scaleValue;
		saveConfig();
		updateWindowSize();
	}

	void pauseGame()
	{
		pause = !pause;

		MENUITEMINFO mii = { 0 };
		mii.cbSize = sizeof(mii);
		mii.dwTypeData = pause ? "&Resume\tPause" : "&Pause\tPause";
		mii.fMask = MIIM_STRING;

		SetMenuItemInfo(menu, ID_GAME_PAUSE, FALSE, &mii);
	}

	GameState()
		: exit(false)
		, pause(false)
		, hwnd(NULL)
		, menu(NULL)
		, window(NULL)
		, renderer(NULL)
		, texture(NULL)
		, romIndex(0)
		, framerate(60)
	{
		memset(&joysticks, NULL, sizeof(joysticks));
		memset(&gamepads, NULL, sizeof(gamepads));

		{
			const SDL_Scancode DefaultButtons[CONTROLLER_BUTTONS] =
			{
				SDL_SCANCODE_UP,
				SDL_SCANCODE_DOWN,
				SDL_SCANCODE_LEFT,
				SDL_SCANCODE_RIGHT,
				SDL_SCANCODE_Z,
				SDL_SCANCODE_X,
				SDL_SCANCODE_S,
				SDL_SCANCODE_A,
				SDL_SCANCODE_SPACE,
				SDL_SCANCODE_RETURN,
				SDL_SCANCODE_D,
				SDL_SCANCODE_C,
			};

			for (int i = 0; i < CONTROLLER_BUTTONS; i++)
			{
				PlayerButton* button = &controllerSetup.player[0].buttons[i];
				memset(button, 0, sizeof(PlayerButton));
				button->type = PlayerButton::KEYBOARD;
				button->code = DefaultButtons[i];
			}
		}

		get_working_dir();
		loadConfig();
	}

	~GameState()
	{
		SDL_DestroyTexture(texture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}

private:

	void updateWindowSize()
	{
		SDL_SetWindowSize(window, EmulatedSNES.nominal_width * config.scale, output_height * config.scale);
		SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

		CheckMenuRadioItem(menu, ID_DISPLAY_SCALE1X, ID_DISPLAY_SCALE4X, ID_DISPLAY_SCALE1X + config.scale - 1, MF_BYCOMMAND);
	}

	void updateSmoothing()
	{
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, config.smoothing ? "1" : "0");
		updateWindowSize();

		CheckMenuItem(menu, ID_DISPLAY_SMOOTHING, MF_BYCOMMAND | (config.smoothing ? MF_CHECKED : MF_UNCHECKED));
	}

	void updateFullscreen()
	{
		if (config.fullscreen)
		{
			while (ShowCursor(FALSE) >= 0);

			SetMenu(hwnd, NULL);
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
		else
		{
			while (ShowCursor(TRUE) < 0);

			SDL_SetWindowFullscreen(window, 0);
			SetMenu(hwnd, menu);
		}

		CheckMenuItem(menu, ID_DISPLAY_FULLSCREEN, MF_BYCOMMAND | (config.fullscreen ? MF_CHECKED : MF_UNCHECKED));
	}

	void loadConfig()
	{
		char filename[1024];

		strcpy(filename,working_dir);
		strcat(filename,CONFIG_NAME);

		FILE* file = fopen(filename, "rb");

		if (file)
		{
			fseek(file, 0, SEEK_END);
			int size = ftell(file);
			fseek(file, 0, SEEK_SET);

			if (size == sizeof(Config))
			{
				fread(&config, sizeof(Config), 1, file);

				memcpy(&controllerSetup, &config.controller, sizeof(ControllerSetup));
			}

			fclose(file);
		}
	}

	void saveConfig()
	{
		char filename[1024];

		strcpy(filename,working_dir);
		strcat(filename,CONFIG_NAME);

		FILE* file = fopen(filename, "wb");

		if (file)
		{
			memcpy(&config.controller, &controllerSetup, sizeof(ControllerSetup));

			fwrite(&config, sizeof(Config), 1, file);
			fclose(file);
		}
	}

	static bool FileExists(const char* path)
	{
		DWORD attr = GetFileAttributes(path);

		return (attr != INVALID_FILE_ATTRIBUTES &&
			!(attr & FILE_ATTRIBUTE_DIRECTORY));
	}

	HWND hwnd;
	HMENU menu;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Texture* artwork;
	int romIndex;
	Config config;
};

static GameState gameState;

#define IDT_TIMER 100

static int CALLBACK DlgConfig(HWND dlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:

		{
			SetTimer(dlg, IDT_TIMER, 100, NULL);
		}

		{
			ControllerSetupDialog.tab = GetDlgItem(dlg, IDC_PLAYER_TAB);

			for (int i = 0; i < PLAYERS_COUNT; i++) addTabItem(ControllerSetupDialog.tab, i);

			HWND content = CreateDialog(NULL, MAKEINTRESOURCE(IDD_PLAYER_TAB_DIALOG), dlg, PlayerDlgConfig);
			SetWindowPos(content, NULL, 20, 40, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		}

		return TRUE;
	case WM_TIMER:
		{
			SDL_JoystickUpdate();

			PlayerButton button;

			if (gameState.processGamepad(button))
			{
				HWND focus = GetFocus();

				if (focus && GetWindowLongPtr(focus, GWLP_WNDPROC) == (LONG)SubEditProc)
				{
					SubEditProc(focus, WM_JOYSTICK, 0, (LPARAM)&button);
				}
			}
		}
		break;
	case WM_NOTIFY:
		if (wParam == IDC_PLAYER_TAB && ((LPNMHDR)lParam)->code == TCN_SELCHANGE)
			ControllerSetupDialog.updateButtonCodeNames();
		break;
	case WM_CLOSE:
		KillTimer(dlg, IDT_TIMER);
		EndDialog(dlg, IDCANCEL);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			KillTimer(dlg, IDT_TIMER);
			return EndDialog(dlg, LOWORD(wParam));
		}
	}

	return FALSE;
}

void MDFNFILE::Open(const char *path, const FileExtensionSpecStruct *known_ext, const char *purpose)
{
#ifdef EMBED_ROM
	// !TODO: ugly hack :(
	int id = (int)path;
	HRSRC res = FindResource(NULL, MAKEINTRESOURCE(id), RT_RCDATA);
	int size = SizeofResource(NULL, res);
	HGLOBAL data = LoadResource(NULL, res);
	void* bin = LockResource(data);

	str.reset(new MemoryStream(size, true));
	memcpy(str->map(), bin, str->size());

	UnlockResource(data);
	FreeResource(data);
#else

	static unsigned bin[8 * 1024 * 1024];

	FILE *file;
	int size;

	file = fopen(path, "rb");

	if (!file) exit(1);

	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	fread(bin, size, 1, file);
	fclose(file);

	str.reset(new MemoryStream(size, true));
	memcpy(str->map(), bin, str->size());

#endif
}

StateMem::~StateMem(void)
{
}

class SoundBuffer
{
public:

	static const int Freq = 44100;

	SoundBuffer()
	{
		SDL_AudioSpec wantSpec;
		wantSpec.freq = Freq;
		wantSpec.format = AUDIO_S16;
		wantSpec.channels = 2;
		wantSpec.samples = 1024;
		wantSpec.userdata = this;
		wantSpec.callback = &SoundBuffer::FillAudio;

		audioDevice = SDL_OpenAudioDevice(NULL, 0, &wantSpec, &audioSpec, SDL_AUDIO_ALLOW_ANY_CHANGE);

		size = audioSpec.freq * audioSpec.channels / 2;
		ptr = (int16*)malloc(size * sizeof(int16));
		stream = (int16*)malloc(audioSpec.freq / 30 * sizeof(int16) * wantSpec.channels);
		pos = 0;
		format = wantSpec.format;
	}

	~SoundBuffer()
	{
		SDL_CloseAudioDevice(audioDevice);

		free(ptr);
		free(stream);
	}

	void resume()
	{
		SDL_PauseAudioDevice(audioDevice, 0);
	}

	void pause()
	{
		SDL_PauseAudioDevice(audioDevice, 1);
	}

	static void FillAudio(void* udata, uint8* stream, int size)
	{
		SoundBuffer* buffer = (SoundBuffer*)udata;
		switch (buffer->format)
		{
		case AUDIO_F32: buffer->getAudioFloat((float*)stream, size / sizeof(float)); break;
		case AUDIO_S16: buffer->getAudioShort((int16*)stream, size / sizeof(int16)); break;
		}
	}

	void blit(int samples)
	{
		samples *= audioSpec.channels;

		int len = size - pos;

		if (len < samples)
		{
			len = samples - len;
			memmove(ptr, ptr + len, (size - len) * sizeof(int16));
			pos -= len;
		}

		memcpy(ptr + pos, stream, samples * sizeof(int16));
		pos += samples;
	}

	int16* getStream() const
	{
		return stream;
	}

private:
	void getAudioFloat(float* stream, int len)
	{

	}

	void getAudioShort(int16* stream, int len)
	{
		if (len < pos)
		{
			memcpy(stream, ptr, len * sizeof(int16));
			memmove(ptr, ptr + len, (size - len) * sizeof(int16));
			pos -= len;
		}
		//else
		//{
		//	printf("missing samples %i\n", len - pos);
		//}
	}

	int16* ptr;
	int16* stream;
	int pos;
	int size;
	SDL_AudioFormat format;
	SDL_AudioDeviceID audioDevice;
	SDL_AudioSpec audioSpec;
};

static void WindowsMessageHook(void *userdata, void *hWnd, unsigned int message, Uint64 wParam, Sint64 lParam)
{
	GameState* gameState = (GameState*)userdata;
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_CONFIGURE_CONTROLS:
			gameState->configureControls();
			break;
		case ID_GAME_PAUSE:
			gameState->pauseGame();
			break;
		case ID_GAME_RESETTOMENU: 
			gameState->loadRomData(0);
			break;
		case ID_GAME_RESETGAME: 
			EmulatedSNES.DoSimpleCommand(MDFN_MSC_RESET); 
			break;
		case ID_GAME_EXIT: 
			gameState->exit = true;
			break;
		case ID_DISPLAY_SCALE1X:
		case ID_DISPLAY_SCALE2X:
		case ID_DISPLAY_SCALE3X:
		case ID_DISPLAY_SCALE4X:
			gameState->resizeWindow(LOWORD(wParam) - ID_DISPLAY_SCALE1X + 1);
			break;
		case ID_SAVEGAMEPOSITION_SLOT1:
		case ID_SAVEGAMEPOSITION_SLOT2:
		case ID_SAVEGAMEPOSITION_SLOT3:
		case ID_SAVEGAMEPOSITION_SLOT4:
		case ID_SAVEGAMEPOSITION_SLOT5:
		case ID_SAVEGAMEPOSITION_SLOT6:
		case ID_SAVEGAMEPOSITION_SLOT7:
		case ID_SAVEGAMEPOSITION_SLOT8:
		case ID_SAVEGAMEPOSITION_SLOT9:
			gameState->stateAction(false, LOWORD(wParam) - ID_SAVEGAMEPOSITION_SLOT1);
			break;
		case ID_LOADGAMEPOSITION_SLOT1:
		case ID_LOADGAMEPOSITION_SLOT2:
		case ID_LOADGAMEPOSITION_SLOT3:
		case ID_LOADGAMEPOSITION_SLOT4:
		case ID_LOADGAMEPOSITION_SLOT5:
		case ID_LOADGAMEPOSITION_SLOT6:
		case ID_LOADGAMEPOSITION_SLOT7:
		case ID_LOADGAMEPOSITION_SLOT8:
		case ID_LOADGAMEPOSITION_SLOT9:
			gameState->stateAction(true, LOWORD(wParam) - ID_LOADGAMEPOSITION_SLOT1);
			break;
		case ID_DISPLAY_FULLSCREEN: 
			gameState->fullScreen();
			break;
		case ID_DISPLAY_SMOOTHING:
			gameState->smoothing();
			break;
		}
		break;
	}
}

void setPlayerInput(int index)
{
	static Uint16 inputData[PLAYERS_COUNT] = { 0 };

	Uint16& input = inputData[index];

	input = 0;

	PlayerSetup& player = controllerSetup.player[index];

	const int ButtonsOrders[] = { 4, 7, 10, 11, -1, -1, -1, -1, 5, 6, 8, 9, 0, 1, 2, 3 };

	const Uint8* state = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < sizeof(ButtonsOrders)/sizeof(ButtonsOrders[0]); i++)
	{
		bool pressed = false;

		if (ButtonsOrders[i] >= 0)
		{
			PlayerButton& button = player.buttons[ButtonsOrders[i]];

			if (button.type == PlayerButton::KEYBOARD)
			{
				if (button.code != SDL_SCANCODE_UNKNOWN && state[button.code])
					pressed = true;
			}
			else if (button.type == PlayerButton::GAMEPAD)
			{
				for (int j = 0; j < JOYSTICKS_COUNT; j++)
				{
					SDL_Joystick* joystick = gameState.joysticks[j];

					if (joystick && SDL_JoystickGetAttached(joystick))
					{
						SDL_JoystickGUID guid = SDL_JoystickGetGUID(joystick);
						if (memcmp(&guid, &button.guid, sizeof(SDL_JoystickGUID)) == 0)
						{
							if (button.hat)
							{
								int hatsCount = SDL_JoystickNumHats(joystick);

								for (int h = 0; h < hatsCount; h++)
									if (SDL_JoystickGetHat(joystick, h) & button.value)
									{
										pressed = true;
										break;
									}

								if (!pressed)
								{
									int axe = gameState.getAxisMask(joystick);

									if (axe & button.value)
									{
										pressed = true;
										break;
									}
								}
							}
							else
							{
								int buttonsCount = SDL_JoystickNumButtons(joystick);

								for (int b = 0; b < buttonsCount; b++)
								{
									if (SDL_JoystickGetButton(joystick, b) && button.value == b)
									{
										pressed = true;
										break;
									}
								}
							}

							break;
						}
					}
				}
			}
		}

		if(pressed) input |= (1 << i);
	}

	EmulatedSNES.SetInput(index, "gamepad", (uint8*)&inputData[index]);
}

int main(int argc, char **argv)
{
	SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK);

	SDL_SetWindowsMessageHook(WindowsMessageHook, &gameState);
	gameState.init();

	SoundBuffer soundBuffer;
	soundBuffer.resume();

	MDFN_PixelFormat nf(MDFN_COLORSPACE_RGB, 0, 8, 16, 24);
	MDFN_Surface videoBuffer(NULL, EmulatedSNES.nominal_width, EmulatedSNES.nominal_height, EmulatedSNES.nominal_width, nf);
	int32 videoLineWidths[256];

	SDL_Event event;
	bool videoFormatChanged = true;

	while (!gameState.exit)
	{
		if (PendingLoadRom)
		{
			gameState.loadRomData(PendingLoadRom);
			PendingLoadRom = 0;
		}

		gameState.framerate = EmulatedSNES.VideoSystem == VIDSYS_NTSC ? 60 : 50;

		Uint32 start = SDL_GetTicks();

		soundBuffer.pause();

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_CONTROLLERDEVICEADDED:
				{
					int id = event.cdevice.which;
					if (id < JOYSTICKS_COUNT)
					{
						if (gameState.gamepads[id])
							SDL_GameControllerClose(gameState.gamepads[id]);

						gameState.gamepads[id] = SDL_GameControllerOpen(id);
					}
				}
				break;
			case SDL_JOYDEVICEADDED:
				{
					int id = event.jdevice.which;

					if (id < JOYSTICKS_COUNT)
					{
						if(gameState.joysticks[id])
							SDL_JoystickClose(gameState.joysticks[id]);


						gameState.joysticks[id] = SDL_JoystickOpen(id);
					}
				}
				break;
			case SDL_JOYDEVICEREMOVED:
				{
					int id = event.jdevice.which;

					if (id < JOYSTICKS_COUNT && gameState.joysticks[id])
					{
						SDL_JoystickClose(gameState.joysticks[id]);
						gameState.joysticks[id] = NULL;
					}
				}
				break;
			case SDL_QUIT: gameState.exit = true; break;
			case SDL_KEYDOWN: 
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_PAUSE:
					gameState.pauseGame();
					break;
				case SDL_SCANCODE_F1:
				case SDL_SCANCODE_F2:
				case SDL_SCANCODE_F3:
				case SDL_SCANCODE_F4:
				case SDL_SCANCODE_F5:
				case SDL_SCANCODE_F6:
				case SDL_SCANCODE_F7:
				case SDL_SCANCODE_F8:
				case SDL_SCANCODE_F9:
					{
						int slot = event.key.keysym.scancode - SDL_SCANCODE_F1;
						if (event.key.keysym.mod & KMOD_SHIFT) gameState.stateAction(false, slot);
						else if (event.key.keysym.mod == 0) gameState.stateAction(true, slot);
					}
					break;

				case SDL_SCANCODE_RETURN:
					if (event.key.keysym.mod & KMOD_ALT)
						gameState.fullScreen();
					break;
				case SDL_SCANCODE_ESCAPE:
					gameState.escapeFullscreen();
					break;
				}
				break;
			}
		}

		if (!gameState.pause)
			soundBuffer.resume();

		for (int i = 0; i < PLAYERS_COUNT; i++) setPlayerInput(i);
		
		EmulateSpecStruct espec;
		memset(&espec, 0, sizeof(EmulateSpecStruct));
		espec.VideoFormatChanged = videoFormatChanged;
		videoFormatChanged = false;
		espec.surface = &videoBuffer;
		espec.LineWidths = videoLineWidths;

		espec.SoundRate = SoundBuffer::Freq;
		espec.SoundBuf = soundBuffer.getStream();
		espec.SoundVolume = 1.0;

		if (gameState.pause)
		{
			for (int i = 0; i < (videoBuffer.w * videoBuffer.h); i++)
			{
				uint32* pixel = videoBuffer.pixels + i;

				int r, g, b;
				videoBuffer.DecodeColor(*pixel, r, g, b);
				int c = (r + g + b) / 3;
				*pixel = videoBuffer.MakeColor(c, c, c);
			}
		}
		else EmulatedSNES.Emulate(&espec);

		gameState.blit(videoBuffer.pixels);
		soundBuffer.blit(espec.SoundBufSize);

		Uint32 delta = SDL_GetTicks() - start;

		if (delta < 1000 / gameState.framerate)
			SDL_Delay(1000 / gameState.framerate - delta);
	}

	SDL_Quit();

    return 0;
}
