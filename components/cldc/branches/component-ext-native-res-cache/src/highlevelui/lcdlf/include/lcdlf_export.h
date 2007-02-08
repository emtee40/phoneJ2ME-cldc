/*
 *  
 *
 * Copyright  1990-2006 Sun Microsystems, Inc. All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 only, as published by the Free Software Foundation. 
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License version 2 for more details (a copy is
 * included at /legal/license.txt). 
 * 
 * You should have received a copy of the GNU General Public License
 * version 2 along with this work; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA 
 * 
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa
 * Clara, CA 95054 or visit www.sun.com if you need additional
 * information or have any questions. 
 */

#ifndef _LCDLF_EXPORT_H_
#define _LCDLF_EXPORT_H_

/**
 * @defgroup highui_lcdlf Look And Feel External Interface
 * @ingroup highui
 */

/**
 * @file
 * @ingroup highui_lcdlf
 *
 * @brief LCDUI Look and Feel exported native interface (common for platform widgets and java LF).
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <java_types.h>

/**
 * Refresh the given area.  For double buffering purposes.
 */
void lcdlf_refresh(int x, int y, int w, int h);

/**
 * Change screen orientation flag
 */
jboolean lcdlf_reverse_orientation();

/**
 * Change screen orientation flag
 */
jboolean lcdlf_get_reverse_orientation();


/**
 * Return screen width
 */
int lcdlf_get_screen_width();

/**
 *  Return screen height
 */
int lcdlf_get_screen_height();

/**
 * set the screen mode either to fullscreen or normal.
 *
 * @param mode The screen mode
 */
void lcdlf_set_fullscreen_mode(jboolean mode);

/**
 * Resets native resources when foreground is gained by a new display.
 */
void lcdlf_gained_foreground();

/**
 * Initializes the window system.
 *
 * @return <tt>0</tt> upon successful initialization, or
 *         <tt>other value</tt> otherwise
 */
int lcdlf_ui_init();

/**
 * Finalize the window system.
 */
void lcdlf_ui_finalize();

#ifdef __cplusplus
}
#endif

#endif /* _LCDLF_EXPORT_H_ */
