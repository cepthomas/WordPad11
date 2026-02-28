
cls
echo off

echo Copy exe to convenient location.
copy /Y %~dp0bin\x64\wordpad.exe %~dp0..\install

rem Optional copy
if defined TOOLS_PATH (
  echo Copy exe for internal use.
  copy /Y %~dp0bin\x64\wordpad.exe %TOOLS_PATH%
)
