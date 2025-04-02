@echo off
setlocal

set ARES="..\Ares\ares.exe"
set LOG="debug.log"
powershell -NoProfile -Command "& %ARES% 2>&1 | Tee-Object -FilePath %LOG%"

endlocal
