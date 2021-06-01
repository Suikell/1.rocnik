#======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
#
# Účel:		Makefile
#
# $NoKeywords: $ivs_project_2 $Makefile
# $Author:     Pavol Cubinek <xcubin00@stud.fit.vutbr.cz>
# $Date:       $2021-04-10
#============================================================================//

ROOT_DIR:=$(shell cd)
VISUAL_STUIDO_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional
MSBUILD=MSBuild\15.0\Bin\MSBuild.exe
MSTEST=Common7\IDE\MSTEST.exe
NUGET=MSBuild\ReadyRoll\OctoPack\tools\NuGet.exe
DEVENV=Common7\IDE\devenv.com
PACKAGES_FILE=packages.config
PACKAGES_DIR=$(ROOT_DIR)\packages

PROJECT_NAME=StarCalculator
STDDEV_NAME=StandardDeviation
PROJECT_DIR=$(ROOT_DIR)\GUI_calculator\HelloCalculator
SLN=$(ROOT_DIR)\GUI_calculator\StarCalculator.sln
PROJECT=$(PROJECT_DIR)\bin\Release\$(PROJECT_NAME).exe
PROJECT_FILE=$(PROJECT_DIR)\$(PROJECT_NAME).csproj
STDDEV_DIR=$(ROOT_DIR)\Profiling\stddev
STDDEV_PROJ=$(STDDEV_DIR)\bin\Release\$(STDDEV_NAME).exe
STDDEV_FILE=$(STDDEV_DIR)\$(STDDEV_NAME).csproj

PACK_NAME=xcubin00_xradac00_xsnase07
PACK_ARCHIVE=$(ROOT_DIR)\..\$(PACK_NAME).zip
PACK_DIR:=$(ROOT_DIR)\..\..\$(PACK_NAME)
GIT_DIR:=$(ROOT_DIR)\..\.git
PACK_DOC_DIR=$(PACK_DIR)\doc
PACK_INSTALL_DIR=$(PACK_DIR)\install
PACK_REPO_DIR=$(PACK_DIR)\repo

INSTALLER_NAME=StarCalculatorInstaller
INSTALLER_DIR=$(ROOT_DIR)\$(INSTALLER_NAME)
INSTALLER_FILE=$(INSTALLER_DIR)\$(INSTALLER_NAME).vdproj

DOXYGEN_OUTPUT_DIR=$(ROOT_DIR)\Doxygen

all: run	

help :
	@echo "For starting application please run command 'make run'"
		
build:
	cd "$(VISUAL_STUIDO_PATH)" & $(MSBUILD) "$(PROJECT_FILE)" /t:Build /p:Configuration=Release
	
buildInstaller:	
	cd "$(VISUAL_STUIDO_PATH)" & $(DEVENV) $(SLN) /build Debug /project "$(INSTALLER_FILE)" /projectconfig Debug 
	
stddev:
	cd "$(VISUAL_STUIDO_PATH)" & $(MSBUILD) "$(STDDEV_FILE)" /t:Build /p:Configuration=Release
	
run :
	if not exist "$(PROJECT)" make build
	"$(PROJECT)"
	
profile :
	if not exist "$(STDDEV_PROJ)" make build
	"$(STDDEV_PROJ)"
	
TO_REMOVE_FILES="$(ROOT_DIR)\Calculator.sln.DotSettings.user" "$(PROJECT_DIR)\$(PROJ_NAME).csproj.user" "$(TESTS_DIR)\$(TESTS_NAME).csproj.user" "$(STDDEV_DIR)\$(STDDEV_NAME).csproj.user"
TO_REMOVE_DIRS="$(ROOT_DIR)\.vs" "$(PACKAGES_DIR)" "$(PROJECT_DIR)\bin" "$(PROJECT_DIR)\obj" "$(STDDEV_DIR)\bin" "$(STDDEV_DIR)\obj" "$(INSTALLER_DIR)\Debug" "$(INSTALLER_DIR)\Release"
clean:
	for %%f in ($(TO_REMOVE_FILES)) do ( if exist %%f del %%f )
	for %%d in ($(DIRS_TO_REMOVE)) do ( if exist %%d del %%d /f /s /q 1>nul & rmdir %%d /s /q )
	if exist "$(PACK_ARCHIVE)" del "$(PACK_ARCHIVE)"
	
pack: 
	if exist "$(PACK_DIR)" del "$(PACK_DIR)" /f /s /q 1>nul & rmdir "$(PACK_DIR)" /s /q
	mkdir "$(PACK_DIR)"
	
	mkdir "$(PACK_DOC_DIR)"
	xcopy /s "$(DOXYGEN_OUTPUT_DIR)\html\*" "$(PACK_DOC_DIR)"
	
	mkdir "$(PACK_INSTALL_DIR)"
	xcopy /s "$(INSTALLER_DIR)\Release\$(INSTALLER_NAME).msi" "$(PACK_INSTALL_DIR)"
	
	mkdir "$(PACK_REPO_DIR)"
	make clean
	xcopy /s "$(ROOT_DIR)\.." "$(PACK_REPO_DIR)"
	xcopy /s "$(GIT_DIR)\*" "$(PACK_REPO_DIR)\.git\"
	cd "$(PACK_DIR)\.." & zip -r "$(PACK_ARCHIVE)" $(PACK_NAME)
	del "$(PACK_DIR)" /f /s /q 1>nul
	rmdir "$(PACK_DIR)" /s /q

	
