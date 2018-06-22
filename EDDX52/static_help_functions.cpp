#include "stdafx.h"
#include "static_help_functions.h"

void wrapWcharP(const wchar_t * &str, wchar_t(&out)[3][16]) {
	size_t length = wcslen(str);

	int lastWrap = 0;
	int wrapPossible = 0;
	int line = 0;
	for (int i = 0; i < length; i++) {
		if (line > 2) {
			break;
		}

		for (int o = 0; o < 16; o++) {
			if (i >= length) {
				for (int o = lastWrap; o < length; o++) {
					out[line][o - lastWrap] = str[o];
				}

				return;
			}

			if (str[i] == L' ') {
				wrapPossible = i;
			}

			i++;
		}

		if (wrapPossible == lastWrap)
			wrapPossible = lastWrap + 15;

		for (int o = lastWrap; o < wrapPossible; o++) {
			out[line][o - lastWrap] = str[o];
		}

		lastWrap = wrapPossible + 1;

		i = wrapPossible;

		line++;
	}

	for (int i = lastWrap; i < 13; i++) {
		out[2][i] = str[lastWrap + i];
	}

	out[2][13] = '.';
	out[2][14] = '.';
	out[2][15] = '.';
}

void WriteASCII(const std::string str)		// ASCII file..
{
	std::fstream fstream("c:\\code\\eddif.txt", std::ios::app);         // open the file
	fstream << str;
	fstream.close();
}

void WriteUnicode(LPCTSTR buffer)
{
	char buffer2[30000];
	WideCharToMultiByte(CP_ACP, 0, buffer, -1, buffer2, sizeof(buffer2), 0, 0);		// need to convert back to ASCII
	WriteASCII((const char*)buffer2);
}

int determineStringLength(const wchar_t * str) {
	size_t length = wcslen(str);

	int out = 0;
	for (int i = 0; i < length; i++) {
		if (str[i] != ' ') {
			out = i;
		}
	}

	return out;
}

void performMfdEnterAnimation(DirectOutput_SetString &setString, wchar_t (&out)[3][16], wchar_t (&display)[3][16], int (&length)[3], void * activeDevice, DWORD workPage)
{
	using namespace std::chrono_literals;

	for (int z = 0; z < 3; z++) {
		setString(activeDevice, workPage, z, 16, display[z]);
		for (int i = 0; i < length[z]; i++) {
			std::this_thread::sleep_for(50ms);
			display[z][i] = out[z][i];
			display[z][i + 1] = '<';
			setString(activeDevice, workPage, z, 16, display[z]);
		}
		display[z][length[z]] = out[z][length[z]];
		std::this_thread::sleep_for(50ms);
		setString(activeDevice, workPage, z, 16, display[z]);
	}
}
