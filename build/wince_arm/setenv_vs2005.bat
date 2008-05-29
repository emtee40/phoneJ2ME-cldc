@REM
@REM Copyright  1990-2007 Sun Microsystems, Inc. All Rights Reserved.
@REM DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER
@REM
@REM This program is free software; you can redistribute it and/or
@REM modify it under the terms of the GNU General Public License version
@REM 2 only, as published by the Free Software Foundation.
@REM
@REM This program is distributed in the hope that it will be useful, but
@REM WITHOUT ANY WARRANTY; without even the implied warranty of
@REM MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
@REM General Public License version 2 for more details (a copy is
@REM included at /legal/license.txt).
@REM
@REM You should have received a copy of the GNU General Public License
@REM version 2 along with this work; if not, write to the Free Software
@REM Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
@REM 02110-1301 USA
@REM
@REM Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa
@REM Clara, CA 95054 or visit www.sun.com if you need additional
@REM information or have any questions.
@REM
@REM Sample batch file for setting the environment variables to build with
@REM Visual Studio 2005.
@REM
@REM You may need to change the pathnames according to your local
@REM settings. You should use DOS 8.3 pathnames to be compatible with
@REM Cygwin. Use the command "dir /x" to determine 8.3 pathnames.

@REM wince_i386 build is no longer supported with Visual Studio 2005

set USE_VS2005=true
set VS2005_ROOT="C:/Program Files/Microsoft Visual Studio 8"


@REM Settings for the host builds (loopgen/romgen)

set PATH=%VS2005_ROOT%/Common7/IDE;%VS2005_ROOT%/vc/bin;%PATH%
set LIB=%VS2005_ROOT%/vc/lib;%VS2005_ROOT%/vc/PlatformSDK/lib
set INCLUDE=%VS2005_ROOT%/vc/include;%VS2005_ROOT%/vc/PlatformSDK/include

@REM Settings for the target build

@REM set VS2005_CE_ARM_LIB="C:/Program Files/Windows Mobile 6 SDK/PocketPC/lib/armv4i"
@REM set VS2005_CE_ARM_INCLUDE="C:/Program Files/Windows Mobile 6 SDK/PocketPC/include/armv4i"
set VS2005_CE_ARM_LIB=C:/PROGRA~1/WINDOW~4/PocketPC/Lib/Armv4i
set VS2005_CE_ARM_INCLUDE=C:/PROGRA~1/WINDOW~4/PocketPC/include/Armv4i
set VS2005_CE_ARM_PATH=%VS2005_ROOT%/vc/ce/bin/x86_arm
set VS2005_COMMON_PATH=%VS2005_ROOT%/vc/bin


