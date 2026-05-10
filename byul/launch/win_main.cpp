// Copyright (c) 2026 snooy. All rights reserved.

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

import Launch;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	return byul::Launch::GuardedMain();
}