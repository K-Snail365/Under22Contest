@echo off

rem 
set CONFIG=%~1
if "%CONFIG%"=="" set CONFIG=Debug

msbuild BroccoliEngine/Engine/BroccoliEngine.vcxproj /t:Build /p:Configuration=%CONFIG% /p:Platform=x64 /m
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

msbuild U22ProgrammingContest.slnx /t:Build /p:Configuration=%CONFIG% /p:Platform=x64 /m
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%