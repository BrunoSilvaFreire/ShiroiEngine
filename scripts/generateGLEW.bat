@echo off
SET SCRIPTS_DIR=%~dp0
SET ROOT=%SCRIPTS_DIR%../libs/glew/auto
ECHO "Generating GLEW files @ %ROOT%"
CALL CD %ROOT%
CALL make clean