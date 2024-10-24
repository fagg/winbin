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
// This util is basically "touch" from *nix.
//

#define WIN32_LEAN_AND_MEAN
#include <wchar.h>
#include <windows.h>

#include <iostream>
#include <string>

int Touch(const std::wstring &path);

int __cdecl wmain(int argc, wchar_t **argv) {
  if (argc < 2) {
    std::wcout << L"Usage: touch.exe <file_path>" << std::endl;
    return 1;
  }

  std::wstring file_path = argv[1];
  return Touch(file_path);
}

int Touch(const std::wstring &path) {
  //
  // CreateFileW with the OPEN_ALWAYS option will return a handle to
  // the file - if preexisting - or it will create the file and then
  // return the handle.
  //

  HANDLE h = CreateFileW(path.c_str(),
			 GENERIC_WRITE,
			 0,
			 NULL,
			 OPEN_ALWAYS,
			 FILE_ATTRIBUTE_NORMAL,
			 NULL);

  if (h == INVALID_HANDLE_VALUE) {
    std::wcerr << L"Failed to create/open the file. Error = " << GetLastError() << std::endl;
    return EXIT_FAILURE;
  }

  //
  // Get the system time, and then update the file's last modification time.
  //

  SYSTEMTIME system_time;
  GetSystemTime(&system_time);
  FILETIME file_time;

  int rc = EXIT_SUCCESS;

  if (!(SystemTimeToFileTime(&system_time, &file_time) && SetFileTime(h, NULL, NULL, &file_time))) {
    std::wcerr << L"Something happened, could not set file time. Error = " << GetLastError() << std::endl;
    rc = EXIT_FAILURE;
  }

  CloseHandle(h);
  return rc;
}
