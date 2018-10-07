@echo off

pushd %~dp0

for /f %%a in ('git config --global user.email') do set "user=%%a"

:: reset env variables to not interfere 
set project=
set rpath_prefix=

:: read proj.cfg
for /f "delims=" %%a in ('call ini.cmd ../config/proj.cfg project project') do (
    set project=%%a
)

for /f "delims=" %%a in ('call ini.cmd ../config/proj.cfg project rpath_prefix') do (
    set rpath_prefix=%%a
)

set OUT_FOLDER="%rpath_prefix%%project%_out"

set SCRIPT=""-u %~dp0scripts/run.py --goal gen --out %OUT_FOLDER% --check_gen True""

echo %SCRIPT%

python %SCRIPT% %*

echo ERRORLEVEL=%ERRORLEVEL%
