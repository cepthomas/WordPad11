
cls
echo off

rem Copy exe to convenient location.
copy /Y %~dp0bin\x64\wordpad.exe %~dp0..\install

rem Optional exe copy for internal use.
if defined TOOLS_PATH (
  copy /Y %~dp0bin\x64\wordpad.exe %TOOLS_PATH%
)
