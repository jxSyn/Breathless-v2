//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================//

#ifndef COLOR_H
#define COLOR_H

#ifdef _WIN32
#pragma once
#endif

//-----------------------------------------------------------------------------
// Purpose: Basic handler for an rgb set of colors
//			This class is fully inline
//-----------------------------------------------------------------------------
class Color
{
public:
    // constructors
    Color()
    {
        *((int *)this) = 0;
    }
    Color(int _r,int _g,int _b)
    {
        SetColor(_r, _g, _b, 0);
    }
    Color(int _r,int _g,int _b,int _a)
    {
        SetColor(_r, _g, _b, _a);
    }
    
    // set the color
    // r - red component (0-255)
    // g - green component (0-255)
    // b - blue component (0-255)
    // a - alpha component, controls transparency (0 - transparent, 255 - opaque);
    void SetColor(int _r, int _g, int _b, int _a = 0)
    {
        _color[0] = (unsigned char)_r;
        _color[1] = (unsigned char)_g;
        _color[2] = (unsigned char)_b;
        _color[3] = (unsigned char)_a;
    }
    
    void GetColor(int &_r, int &_g, int &_b, int &_a) const
    {
        _r = _color[0];
        _g = _color[1];
        _b = _color[2];
        _a = _color[3];
    }
    
    void SetRawColor( int color32 )
    {
        *((int *)this) = color32;
    }
    
    int GetRawColor() const
    {
        return *((int *)this);
    }
    
    inline int r() const	{ return _color[0]; }
    inline int g() const	{ return _color[1]; }
    inline int b() const	{ return _color[2]; }
    inline int a() const	{ return _color[3]; }
    
    unsigned char &operator[](int index)
    {
        return _color[index];
    }
    
    const unsigned char &operator[](int index) const
    {
        return _color[index];
    }
    
    bool operator == (const Color &rhs) const
    {
        return ( *((int *)this) == *((int *)&rhs) );
    }
    
    bool operator != (const Color &rhs) const
    {
        return !(operator==(rhs));
    }
    
    Color &operator=( const Color &rhs )
    {
        SetRawColor( rhs.GetRawColor() );
        return *this;
    }
    
    static Color White() {
        return Color(255, 255, 255, 255);
    }
    
    static Color Red() {
        return Color(255, 0, 0, 255);
    }
    
    static Color Green() {
        return Color(0, 255, 0, 255);
    }
    
    static Color LightBlue() {
        return Color(0, 200, 255, 255);
    }
    
    static Color Blue() {
        return Color(0, 0, 200, 255);
    }
    
    static Color Avoz() {
        return Color(143, 55, 153, 255);
    }
    
    static Color Orange() {
        return Color(255, 155, 0, 255);
    }
    
    static Color Yellow() {
        return Color(255, 255, 0, 255);
    }
    
    static Color Black() {
        return Color(0, 0, 0, 255);
    }
    
    static Color Purple() {
        return Color(100, 0, 255, 255);
    }
    
    static Color Pink() {
        return Color(255, 0, 150, 255);
    }
    
    static Color Col() {
        return Color( 255, 255, 255, 255 );
    }
    
    static Color Test() {
        static int Tick = 0;
        Tick++;
        
        if (Tick > 0 && Tick < 30)
        {
            Color::Red();
        }
        else if (Tick > 30 && Tick < 60)
        {
            Color::Orange();
        }
        else if (Tick > 60 && Tick < 90)
        {
            Color::Yellow();
        }
        else if (Tick > 90 && Tick < 120)
        {
            Color::Green();
        }
        else if (Tick > 120 && Tick < 150)
        {
            Color::LightBlue();
        }
        else if (Tick > 150 && Tick < 180)
        {
            Color::Blue();
        }
        else if (Tick > 180 && Tick < 210)
        {
            Color::Purple();
        }
        else if (Tick > 210 && Tick < 240)
        {
            Color::Avoz();
        }
        else if (Tick > 240 && Tick < 270)
        {
            Color::Pink();
        }
        
        
        // Reset
        if(Tick > 270)
        {
            Tick = 0;
        }
        
    }
    
    static Color GetFromHSB(float hue, float saturation, float brightness) {
        float h = hue == 1.0f ? 0 : hue * 6.0f;
        float f = h - (int)h;
        float p = brightness * (1.0f - saturation);
        float q = brightness * (1.0f - saturation * f);
        float t = brightness * (1.0f - (saturation * (1.0f - f)));
        Byte r = 0, g = 0, b = 0;
        
        if (h < 1)
        {
            r = (brightness * 255);
            g = (t * 255);
            b = (p * 255);
        }
        else if (h < 2)
        {
            r = (q * 255);
            g = (brightness * 255);
            b = (p * 255);
        }
        else if (h < 3)
        {
            r = (p * 255);
            g = (brightness * 255);
            b = (t * 255);
        }
        else if (h < 4)
        {
            r = (p * 255);
            g = (q * 255);
            b = (brightness * 255);
        }
        else if (h < 5)
        {
            r = (t * 255);
            g = (p * 255);
            b = (brightness * 255);
        }
        else
        {
            r = (brightness * 255);
            g = (p * 255);
            b = (q * 255);
        }
        
        return Color(r, g, b);
    }
    
private:
    unsigned char _color[4];
};


#endif // COLOR_H
