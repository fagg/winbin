//
// Copyright (c) 2024, Dr Ashton Fagg <ashton@fagg.id.au>
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

//
// Pretty simple utility to power down the monitors on the box.
// Useful for if you have DisplayPort monitors that have that stupid
// DDC thing that causes them to disconnect when powered off by the switch.
//

#define WIN32_LEAN_AND_MEAN
#include <wchar.h>
#include <windows.h>

#include <iostream>
#include <string>

#define UNICODE
#define _UNICODE

void ShowUsage();

int __cdecl wmain(int argc, wchar_t **argv) {
  if (argc > 2) {
    ShowUsage();
    return 1;
  }


  //
  // By default, we only power down the monitor. Not lock the machine.
  //

  bool lock_machine = false;

  if (argc == 2) {
    if (wcscmp(argv[1], L"/l") == 0 || wcscmp(argv[1], L"/lock") == 0) {
      lock_machine = true;
    } else if (wcscmp(argv[1], L"/h") == 0 || wcscmp(argv[1], L"/help") == 0) {
      ShowUsage();
      return EXIT_SUCCESS;
    } else {
      ShowUsage();
      return 1;
    }
  }

  if (lock_machine && !LockWorkStation()) {
    std::wcout << L"Failed to lock workstation. Error = " << GetLastError() << std::endl;
    return EXIT_FAILURE;
  }

  return SendMessage(HWND_BROADCAST,
		     WM_SYSCOMMAND,
		     SC_MONITORPOWER,
		     2);
}


void ShowUsage() {
  std::wcout << L"monoff.exe <options>" << std::endl;
  std::wcout << L"/h,/help - displays this helpful message." << std::endl;
  std::wcout << L"/l,/lock - lock the system prior to monitor power off." << std::endl;
}
