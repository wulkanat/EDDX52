// UnitTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#include <comdef.h>
#include <iostream>

void wrapWcharP(const wchar_t * &str, wchar_t (&out)[3][16]) {
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

int main()
{
	const wchar_t * str = L"Lorem ipsum dolor sid amed jola fader sed fuda";
	wchar_t out[3][16] = {
		L"               ",
		L"               ",
		L"               "
	};

	wrapWcharP(str, out);

	printf("%S", out[0]);
	printf("%S", "\n");
	printf("%S", out[1]);
	printf("%S", "\n");
	printf("%S", out[2]);

	int x;
	std::cin >> x;

    return 0;
}