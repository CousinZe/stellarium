/*
 * Stellarium
 * Copyright (C) 2002 Fabien Chereau
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

// Class to manage s_fonts

#ifndef _S_FONT_H
#define _S_FONT_H

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "SDL_opengl.h"
#include "StelUtils.hpp"
#include "typeface.h"

class SFont
{
public:
    SFont(float size_i, const string& ttfFileName) : typeFace(ttfFileName, (size_t)(size_i), 72) {;}
    ~SFont() {;}
    
    void print(float x, float y, const string& s, int upsidedown = 1) const {typeFace.render(StelUtils::stringToWstring(s), Vec2f(x, y), upsidedown==1);}
	void print(float x, float y, const wstring& ws, int upsidedown = 1) const {typeFace.render(ws, Vec2f(x, y), upsidedown==1);}
	
	void print_char(const wchar_t c) const {
		wchar_t wc[] = L"xx";
		wc[0] = c;
		wc[1] = 0;  // terminate string
		typeFace.renderGlyphs((wstring(wc)));
	}

	void print_char_outlined(const wchar_t c) const {

		// This is not the most elegant way to do this,
		// but avoids needing two fonts loaded

		wchar_t wc[] = L"xx";
		wc[0] = c;
		wc[1] = 0;  // terminate string

		GLfloat current_color[4];
		glGetFloatv(GL_CURRENT_COLOR, current_color);	 
 	 	 

		glColor3f(0,0,0);
		//		glColor3f(0.2,0.2,0.2);

		glPushMatrix();
		glTranslatef(1,1,0);		
		typeFace.renderGlyphs((wstring(wc)));
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-1,-1,0);		
		typeFace.renderGlyphs((wstring(wc)));
		glPopMatrix();

		glPushMatrix();
		glTranslatef(1,-1,0);		
		typeFace.renderGlyphs((wstring(wc)));
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-1,1,0);		
		typeFace.renderGlyphs((wstring(wc)));
		glPopMatrix();

		glColor4fv(current_color);

		typeFace.renderGlyphs((wstring(wc)));
	}
	
	void print_char(const unsigned char c) const {
		wchar_t wc[] = L"xx";
		wc[0] = c;
		wc[1] = 0;  // terminate string
		typeFace.renderGlyphs((wstring(wc)));
	}

	void print_char_outlined(const unsigned char c) const {

		print_char_outlined(wchar_t(c));
	}

    float getStrLen(const wstring& s) const {return typeFace.width(s);}
    float getStrLen(const string& s) const {return typeFace.width(StelUtils::stringToWstring(s));}
    float getLineHeight(void) const {return typeFace.lineHeight();}
    float getAscent(void) const {return typeFace.ascent();}
    float getDescent(void) const {return typeFace.descent();}

private:
	mutable TypeFace typeFace;
};


#endif  //_S_FONT_H
