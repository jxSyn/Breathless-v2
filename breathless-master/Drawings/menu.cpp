//
//  menu.cpp
//  macOS base
//

#include "menu.h"
#include "Config.h"

cMenu* menu = new cMenu();
Config cfg;

// Colours

Color Red             = Color(255, 0, 57, 255);
Color inactive          = Color(82, 82, 82, 255);
Color MainColor         = Red;

Color FontColor         = Color(255, 255, 255, 250);
Color background        = Color(28, 28, 28, 255);
Color outline           = Color(43, 43, 43, 255);
Color backgroundalpha   = Color(28, 28, 28, 255); // 225 alpha
Color border1           = Color(60, 60, 60, 255);
Color border2           = Color(40, 40, 40, 255);
Color black             = Color(0, 0, 0, 255);
Color Avoz              = Color(163, 12, 224, 255);
Color FontColorDeselect = Color(190, 190, 190, 255);


bool WasPressed, WasReleased;
auto Pressed (ButtonCode_t code) -> void {
    
    if (pInputSystem->IsButtonDown(code)) {
        
        WasPressed = true;
        
    } else if (!(pInputSystem->IsButtonDown(code))) {
        
        if (WasPressed) {
            
            WasReleased = true;
            
        } else {
            
            WasReleased = false;
            
        }
        
        WasPressed = false;
        
    }
    
}

// Menu components

void cMenu::renderCheckbox(int x, int y, const char* str, bool *var) {
    
    int size = 8;
    
    draw->fillrgba(x, y, 18, 8, Color(56,56,56,242));
    draw->fillrgba(x + 1, y + 1, 10 - 2, 8 - 2, Color(252,252,252,255));
    
    if (*var) {
        draw->fillrgba( x, y, 18, 8, Color(124, 200, 0,242));
        draw->fillrgba( x + 9, y + 1, 10 - 1, 8 - 2, Color(252,252,252,255));
    }
    
    if (draw->inArea(x, y, 18, 8)) {
        
        if (*var) {
            draw->fillrgba( x, y, 18, 8, Color(124, 200, 0,242));
            draw->fillrgba( x + 9, y + 1, 10 - 1, 8 - 2, Color(252,252,252,255));
        }
        
        if (WasReleased)
            *var = !*var;
    }
    
    draw->drawbox(x, y, 18, 8, Color(2,2,2,255)); // Outline
    
    draw->drawstring(x + 25, y - 3, FontColor, mFont, str);
    
}


// The sliders are kinda broken, if you click past the ends itll still move
// for ints
void cMenu::renderSlider_c(int x, int y, int w, const char* szString, int& value, int max, int min, Color &col) {
    
    int h = 6;
    int curValue = value * ((float)w / (float)(max));
    
    if (draw->GetMouse().x > x - 4 && draw->GetMouse().y > y - 2 && draw->GetMouse().x < x + w + 4 && draw->GetMouse().y < y + h + 2) {
        
        Color col = Color(40, 45, 55, 255);
        
        if (pInputSystem->IsButtonDown(MOUSE_LEFT)) {
            
            value = (draw->CalcPos(x) / ((float)w / (float)(max)));
            
            if (value > max)
                value = max;
            
            if (value < min)
                value = min;
            
        }
        
    }
    
    // draw->RectOutlined(x, y + 5, w + 2, h, 1, background, Color::Black());
    //  draw->fillrgba(x, y + 5, w + 2, h, Color(40, 45, 55, 255));
    //draw->fillrgba(x, y + 5, curValue, h, Color(40, 45, 55, 255));
    draw->RectOutlined(x + 5, y + 5, w, h, 1, Color(58, 58, 58, 255), Color::Black());
    draw->fillrgba( x + 5, y + 5, curValue, h, col );                       // Color till cursor
    
    draw->drawstring(x + w + 15, y + 3, Color::White(), mFont, to_string(value).c_str());
    draw->drawstring(x + 5, y - 9, FontColor, supremacy, szString);
    //better one
    // draw->fillrgba(x + curValue, y - 1, 4, h + 2, Color(10, 145, 190, 255));
    //  draw->drawbox(x, y, w, h, Color(10, 145, 190, 255));
    //   draw->drawstring(x + curValue - 5, y + 7, FontColor, mFont, to_string(value).c_str());
    
}
void cMenu::renderSlider(int x, int y, int w, const char* szString, int& value, int max, int min) {
    
    int h = 6;
    int curValue = value * ((float)w / (float)(max));
    
    if (draw->GetMouse().x > x - 4 && draw->GetMouse().y > y - 2 && draw->GetMouse().x < x + w + 4 && draw->GetMouse().y < y + h + 2) {
        
        Color col = Color(40, 45, 55, 255);
        
        if (pInputSystem->IsButtonDown(MOUSE_LEFT)) {
            
            value = (draw->CalcPos(x) / ((float)w / (float)(max)));
            
            if (value > max)
                value = max;
            
            if (value < min)
                value = min;
            
        }
        
    }
    
    // draw->RectOutlined(x, y + 5, w + 2, h, 1, background, Color::Black());
    //  draw->fillrgba(x, y + 5, w + 2, h, Color(40, 45, 55, 255));
    //draw->fillrgba(x, y + 5, curValue, h, Color(40, 45, 55, 255));
    draw->RectOutlined(x + 5, y + 5, w, h, 1, Color(58, 58, 58, 255), Color::Black());
    draw->fillrgba( x + 5, y + 5, curValue, h, Avoz );                       // Color till cursor
    
    draw->drawstring(x + w + 15, y + 3, Color::White(), mFont, to_string(value).c_str());
    draw->drawstring(x + 5, y - 9, FontColor, mFont, szString);
    //better one
    // draw->fillrgba(x + curValue, y - 1, 4, h + 2, Color(10, 145, 190, 255));
    //  draw->drawbox(x, y, w, h, Color(10, 145, 190, 255));
    //   draw->drawstring(x + curValue - 5, y + 7, FontColor, mFont, to_string(value).c_str());
    
}

// for floats
void cMenu::renderSlider(int x, int y, int w, const char* szString, float& value, int max, int min) {
    
    int h = 8;
    int curValue = value * ((float)w / (float)(max));
    
    if (draw->GetMouse().x > x - 4 && draw->GetMouse().y > y - 2 && draw->GetMouse().x < x + w + 4 && draw->GetMouse().y < y + h + 2) {
        
        if (pInputSystem->IsButtonDown(MOUSE_LEFT)) {
            
            value = (draw->CalcPos(x) / ((float)w / (float)(max)));
            
            if (value > max)
                value = max;
            
            if (value < min)
                value = min;
            
        }
        
    }
    /*
     draw->fillrgba(x + curValue, y - 1, 4, h + 2, Color(10, 145, 190, 255));
     draw->drawbox(x, y, w, h, Color(10, 145, 190, 255));
     draw->drawstring(x + curValue - 5, y + 7, FontColor, mFont, to_string(value).c_str());
     */
    char buffer[16];
    
    sprintf(buffer, "%.2f", value);
    
    draw->RectOutlined(x + 5, y + 5, w, h, 1, Color(58, 58, 58, 255), Color(2, 2, 2, 255));
    draw->fillrgba( x + 5, y + 5, curValue, h, Avoz );                       // Color till cursor
    
    draw->drawstring(x + w + 15, y + 3, Color::White(), mFont, buffer);
    draw->drawstring(x + 5, y - 9, FontColor, mFont, szString);
}




void cMenu::renderCombo(int x, int y, int w, int h, const char* szString, vector<string> szValue, int& currValue, bool* bOpend) {
    
    int Y = y + h;
    
    if(draw->inArea(x, y, w, h)) {
        if(WasReleased) {
            *bOpend = !*bOpend;
        }
    }
    
    if (*bOpend) {
        
        for ( int i = 0; i < szValue.size(); i++ ) {
            
            auto bHover = draw->inArea(x, Y + 2 + ( i * 20 ), w, 18);
            
            draw->RectOutlined(x, Y + 1 + ( i * 20 ), w + 2, 18, 1, bHover ? Color(37, 52, 60, 255) : Color(58, 58, 58, 255), Color(2, 2, 2, 255));
            draw->drawstring(x + 5, Y + 2 + (i*20), Color::White(), mFont, szValue[i].c_str());
            
            if (draw->inArea(x, Y + 2 + ( i * 20 ), w, 18)) {
                if(WasPressed){
                    currValue = i;
                    *bOpend = false;
                }
            }
        }
    }
    
    if(currValue == 0)
        szString = szString;
    else
        szString = szValue[currValue].c_str();
    
    // Draws the box
    draw->RectOutlined(x, y, w + 2, h, 1, Color(58, 58, 58, 255), Color(2, 2, 2, 255));
    ;
    draw->drawstring(x + 5, y + (h/2) - 7, FontColor, mFont, szString);
    
    
    if (!*bOpend)
    {
        // draw arrow pointing down
        draw->fillrgba( ( x + w - h + 113 - 107 ), ( y + 8 ), 1, 1, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 114 - 107 ), ( y + 8 ), 1, 2, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 115 - 107 ), ( y + 8 ), 1, 3, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 116 - 107 ), ( y + 8 ), 1, 4, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 117 - 107 ), ( y + 8 ), 1, 3, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 118 - 107 ), ( y + 8 ), 1, 2, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 119 - 107 ), ( y + 8 ), 1, 1, Color( 255, 255, 255, 255 ) );
    }
    else
    {
        // draw arrow pointing up
        draw->fillrgba( ( x + w - h + 113 - 107 ), ( y + 11 ), 1, 1, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 114 - 107 ), ( y + 10 ), 1, 2, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 115 - 107 ), ( y + 9 ), 1, 3, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 116 - 107 ), ( y + 8 ), 1, 4, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 117 - 107 ), ( y + 9 ), 1, 3, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 118 - 107 ), ( y + 10 ), 1, 2, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 119 - 107 ), ( y + 11 ), 1, 1, Color( 255, 255, 255, 255 ) );
    }
}

void cMenu::renderButton(int x, int y, const char* szString, bool* var) {
    
    int w = 60;
    int h = 20;
    
    if(draw->inArea(x, y, w, h)) {
        if(WasPressed) {
            *var = true;
        }
    } else {
        *var = false;
    }
    
    bool bHovering = draw->inArea(x, y, w, h);
    draw->drawgradient(x, y, w, h, bHovering ? Color(37, 52, 60, 255) : Color(25, 25, 25, 255), Color(25, 25, 25, 255));
    draw->drawbox(x + 1, y + 1, w - 2, h - 2, bHovering ? Color(64, 91, 106, 255) : Color(67, 67, 67, 255));
    draw->drawbox(x, y, w, h, bHovering ? Color(25, 35, 40, 255) : Color(9, 9, 9, 255));
    
    draw->drawstring(x + w / 2, y + h / 2, FontColor, framefont, szString, true);
    
}

void cMenu::playerbutton(int x, int y, int w, int h, int index, int& playercount, const char* szString)
{
    y += index * 24;
    
    if(draw->inArea(x, y, w, h))
    {
        if(WasReleased)
        {
            playercount = index;
        }
    }
    
    bool bHovering = draw->inArea(x, y, w, h);
    draw->drawgradient(x, y, w, h, bHovering ? Color(30, 30, 30, 255), FontColor : Color(15, 15, 15, 255), Color(15, 15, 15, 255));
    draw->drawbox(x, y, w, h, Color::Black());
    draw->drawstring(x + w / 2, y + h / 2, FontColor, mFont, szString, true);
}

void cMenu::render_section(int x, int y, int w, int h, const char* label)
{
    
    draw->RectOutlined(x, y, w, h, 1, Color(28, 28, 28, 255), Color(43, 43, 43, 255));
    // ImGui::PushFont(Fonts::section);
    
    auto text_size = draw->GetTextSize(label, mSection);
    
    draw->fillrgba(x + 12, y - 1, text_size.x + 7, 3, Color(28, 28, 28, 255));
    // draw->drawbox(x + 12, y - 1, text_size.x + 7, 3, Color(255, 20, 20, 255));
    draw->drawstring(x + 15, y - 6, FontColor, mSection, label);
}

void cMenu::render_tab_section(int x, int y, int w, int h)
{
    draw->RectOutlined(x, y, w, h, 1, Color(28, 28, 28, 255), Color(43, 43, 43, 255));
}

// Made by ViKiNG
void cMenu::drawcolorpicker(int x, int y, const char *szString, Color &col) {
    
    int oner = 6;
    float flRnbw = 0.0005f;
    int currPosX, currPosY;
    
    for(int i = 0 ; i < 21; i++) {
        flRnbw += 0.045f;
        
        Color col1 = Color::GetFromHSB(flRnbw, 1.0f, 1.0f);
        Color col2 = Color::GetFromHSB(flRnbw, 0.90f, 0.90f);
        Color col3 = Color::GetFromHSB(flRnbw, 0.80f, 0.80f);
        Color col4 = Color::GetFromHSB(flRnbw, 0.70f, 0.70f);
        Color col5 = Color::GetFromHSB(flRnbw, 0.60f, 0.60f);
        Color col6 = Color::GetFromHSB(flRnbw, 0.50f, 0.50f);
        Color col7 = Color::GetFromHSB(flRnbw, 0.40f, 0.40f);
        Color col8 = Color::GetFromHSB(flRnbw, 0.30f, 0.30f);
        Color col9 = Color::GetFromHSB(flRnbw, 0.20f, 0.20f);
        Color col10 = Color::GetFromHSB(flRnbw, 0.15f, 0.15f);
        Color col11 = Color::GetFromHSB(flRnbw, 0.10f, 0.10f);
        
        draw->fillrgba(x + i * oner, y, oner, oner, Color(col1.r(), col1.g(), col1.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 1, oner, oner, Color(col2.r(), col2.g(), col2.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 2, oner, oner, Color(col3.r(), col3.g(), col3.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 3, oner, oner, Color(col4.r(), col4.g(), col4.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 4, oner, oner, Color(col5.r(), col5.g(), col5.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 5, oner, oner, Color(col6.r(), col6.g(), col6.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 6, oner, oner, Color(col7.r(), col7.g(), col7.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 7, oner, oner, Color(col8.r(), col8.g(), col8.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 8, oner, oner, Color(col9.r(), col9.g(), col9.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 9, oner, oner, Color(col10.r(), col10.g(), col10.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 10, oner, oner, Color(col11.r(), col11.g(), col11.b(), 255));
        
        int x1 = x + i * oner;
        int y2 = y + oner * 1;
        int y3 = y + oner * 2;
        int y4 = y + oner * 3;
        int y5 = y + oner * 4;
        int y6 = y + oner * 5;
        int y7 = y + oner * 6;
        int y8 = y + oner * 7;
        int y9 = y + oner * 8;
        int y10 = y + oner * 9;
        int y11 = y + oner * 10;
        
        if(draw->inArea(x1, y, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col1;
                draw->drawbox(x1, y, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y;
            }
        } else if(draw->inArea(x1, y2, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col2;
                draw->drawbox(x1, y2, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y2;
            }
        } else if(draw->inArea(x1, y3, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col3;
                draw->drawbox(x1, y3, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y3;
            }
        } else if(draw->inArea(x1, y4, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col4;
                draw->drawbox(x1, y4, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y4;
            }
        } else if(draw->inArea(x1, y5, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col5;
                draw->drawbox(x1, y5, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y5;
            }
        } else if(draw->inArea(x1, y6, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col6;
                draw->drawbox(x1, y6, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y6;
            }
        }
        else if(draw->inArea(x1, y7, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col7;
                draw->drawbox(x1, y7, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y7;
            }
        }
        else if(draw->inArea(x1, y8, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col8;
                draw->drawbox(x1, y8, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y8;
            }
        }
        else if(draw->inArea(x1, y9, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col9;
                draw->drawbox(x1, y9, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y9;
            }
        }
        else if(draw->inArea(x1, y10, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col10;
                draw->drawbox(x1, y10, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y10;
            }
        }
        else if(draw->inArea(x1, y11, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col11;
                draw->drawbox(x1, y11, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y11;
            }
        }
    }
    
    draw->fillrgba(x, y + 73, 5, 20, Color(col.r(), col.g(), col.b(), 255));
    draw->drawbox(x, y + 73, 5, 20, Color::Black());
    
    string strPalette;
    
    strPalette.append("R: ");
    strPalette.append(to_string(col.r()));
    
    strPalette.append(" G: ");
    strPalette.append(to_string(col.g()));
    
    strPalette.append(" B: ");
    strPalette.append(to_string(col.b()));
    
    draw->drawstring(x, y - 20, Color::White(), mFont, szString);
    draw->drawstring(x + 10, y + 78, Color::White(), mFont, strPalette.c_str());
}

// Tabs

void cMenu::renderAim(int x, int y) {
    
    vector<string> hitscan;
    
    hitscan.push_back("high");
    hitscan.push_back("medium");//xanax moving
    hitscan.push_back("low");//supremacy $
    /* hitscan.push_back("high");//gamesense
     hitscan.push_back("extreme");
     hitscan.push_back("baim");
     */
    
    vector<string> FLag;
    
    FLag.push_back("Dynamic");
    FLag.push_back("Multiply");
    
    vector<string> AutoStop;
    
    AutoStop.push_back("Minimum Speed");
    AutoStop.push_back("Full Stop");
    
    vector<string> FakeLag;
    
    FakeLag.push_back("Factor");
    FakeLag.push_back("Break Lag Comp");
    FakeLag.push_back("Switch");
    FakeLag.push_back("Random");
    FakeLag.push_back("On Peek");
    FakeLag.push_back("Spike");
    
    this->renderCheckbox(x - 15, y, "Enabled", &vars.aimbot.enabled);
    this->renderCheckbox(x - 15, y + 20, "SilentAim", &vars.aimbot.silent);
    //draw->drawstring(x + 5, y + 40, FontColor, mFont, "FOV");
    this->renderSlider(x + 5, y + 40, 150, "Fov", vars.aimbot.FovToPlayer, 180, 0);
    // draw->drawstring(x, y + 70, FontColor, mFont, "Hitbox");
    this->renderSlider(x + 5, y + 70, 150, "Hitbox", vars.aimbot.hitbox, 19, 0);
    this->renderCheckbox(x - 15, y + 90, "Auto Wall", &vars.aimbot.autowall);
    this->renderSlider(x + 5, y + 110, 150, "Minimum Damage", vars.aimbot.mindmg, 100, 0);
    this->renderSlider(x + 5, y + 140, 150, "Hitchance", vars.aimbot.accuracyhithcance, 100, 0);
    this->renderSlider(x + 5, y + 160, 150, "Pointscale", vars.aimbot.pointscale, 100, 0);
    this->renderCheckbox(x - 15, y + 180, "Baim Under X Hp", &vars.aimbot.Baim);
    this->renderSlider(x + 5, y + 200, 150, "", vars.aimbot.BaimHP, 100, 0);
    this->renderCheckbox(x - 15, y + 220, "Fakelag", &vars.misc.fakelag);
    this->renderCheckbox(x - 15, y + 240, "Adaptive", &vars.misc.adaptive);
    this->renderCombo(x + 10, y + 260, 150, 20, "Factor", FakeLag, vars.misc.fakelagtype, &vars.fakewalk_opend);
    if(!vars.fakewalk_opend){
        this->renderSlider(x + 5, y + 290, 150, "Choke", vars.misc.fakelagf, 16, 0);
    }
    
    this->renderCheckbox(x + 235, y, "Auto Scope", &vars.aimbot.autoscope);
    this->renderCheckbox(x + 235, y + 20, "Auto Pistol", &vars.aimbot.autopistol);
    this->renderCheckbox(x + 235, y + 40, "Auto Crouch", &vars.aimbot.autocrouch);
    this->renderCheckbox(x + 235, y + 60, "Auto Shoot", &vars.aimbot.autoshoot);
    this->renderCheckbox(x + 235, y + 80, "Auto Cock", &vars.aimbot.autocock);
    this->renderCheckbox(x + 235, y + 100, "Auto Slow", &vars.aimbot.autoslow);
    this->renderCheckbox(x + 235, y + 120, "Backtrack", &vars.aimbot.backtrack);
    this->renderCheckbox(x + 235, y + 140, "Hitscan", &vars.aimbot.hitscan);
    
    
    
    
    
    vector<string> resolver;
    vector<string> freestand_mode;
    
    resolver.push_back("Simple");
    resolver.push_back("Prediction");//xanax moving
    resolver.push_back("Bruteforce");//supremacy $'
    resolver.push_back("LBY");//supremacy $
    
        this->renderCheckbox(x + 235, y + 190, "Resolve", &vars.aimbot.Yawresolver);
        this->renderCheckbox(x + 235, y + 210, "Override Yaw[.]", &vars.aimbot.overrideYaw);
    this->renderCombo(x + 260, y + 160, 150, 20, "High", hitscan, vars.aimbot.hitscantype, &vars.hitscan_opend);
        //lby correction
        // this->renderCombo(x + 259, y + 250, 150, 20, "Simple", resolver, vars.aimbot.yresolve, &vars.yawResolver_opend);
    
   // this->renderCheckbox(x + 235, y + 355, "Anti-Aim", &vars.misc.antiaim);
   // this->renderCheckbox(x + 235, y + 375, "Pitch", &vars.misc.pitch);
   // this->renderCheckbox(x + 330, y + 355, "Yaw", &vars.misc.AAenabled);
   // this->renderCheckbox(x + 330, y + 375, "Auto-Direction", &vars.misc.freestand);
    
  //  if (!vars.freestand_opend) {
        
        // this->renderSlider(x + 235, y + 400, 160, "Jitter", vars.aimbot.jitter, 180, 0);
  //  }
    
    
}

void cMenu::renderAntiAim(int x, int y) {
    this->renderCheckbox(x - 15, y, "Anti-Aim", &vars.misc.antiaim);
     this->renderCheckbox(x - 15, y + 20, "Pitch", &vars.misc.pitch);
     this->renderCheckbox(x - 15, y + 40, "Yaw", &vars.misc.AAenabled);
     this->renderCheckbox(x - 15, y + 60, "Auto-Direction", &vars.misc.freestand);
    
    if (!vars.freestand_opend) {
    
     this->renderSlider(x + 5, y + 80, 160, "Jitter", vars.aimbot.jitter, 180, 0);
        
      }
}


void cMenu::renderLegit(int x, int y) {
    
    vector<string> Hitgroup;  // Resolver
    
    Hitgroup.push_back("Head");
    Hitgroup.push_back("Body");
    Hitgroup.push_back("Legs");
    // Hitgroup.push_back("Best Bone");
    // Hitgroup.push_back("Dick");
    // Hitgroup.push_back("p100Maxwell");
    //  Hitgroup.push_back("Basic");
    
    
    
    this->renderCheckbox(x - 15, y, "Enabled", &vars.aimbot.LegitEnabled);
    this->renderSlider(x + 5, y + 20, 150, "Fov", vars.aimbot.legitFOV, 5.0f, 0.0f);
    this->renderCheckbox(x - 15, y + 40, "Smoothing", &vars.aimbot.smooth);
    
    
    this->renderSlider(x + 5, y + 60, 150, "Amount", vars.aimbot.smoothf, 1.0f, 0.0f);
    
    this->renderCheckbox(x - 15, y + 80, "Target Hitgroup", &vars.aimbot.legitHitscan);
    
    //    draw->Text
    
    this->renderCheckbox(x - 15, y + 130, "Triggerbot", &vars.aimbot.trigger);
    this->renderCheckbox(x - 15, y + 150, "Delay", &vars.aimbot.delay);
    if(!vars.legithitscanpri_opend){
    this->renderSlider(x + 5, y + 170, 150, "", vars.aimbot.lowBound, 100, 0);
    }
    this->renderCombo(x + 10, y + 100, 150, 20, "Head", Hitgroup, vars.aimbot.legitHitscanType, &vars.legithitscanpri_opend);

    this->renderSlider(x + 5, y + 200, 150, "Minimum Hitchance", vars.aimbot.triggerHitchance, 100, 0);
    //this->renderCheckbox(x - 15, y + 220, "Ignore In Air", &vars.aimbot.TargetAirCheck);
    
    this->renderCheckbox(x - 15, y + 220, "RCS", &vars.aimbot.rcs);
    this->renderSlider(x + 5, y + 240, 150, "Recoil Vertical", vars.aimbot.rcsx, 100, 0);
    this->renderSlider(x + 5, y + 260, 150, "Recoil Horizontal", vars.aimbot.rcsy, 100, 0);
    
    this->renderCheckbox(x - 15, y + 280, "Legit Backtrack", &vars.aimbot.legitBacktrack);
    this->renderSlider(x + 5, y + 300, 150, "Ticks", vars.aimbot.legitBacktrackTicks, 12, 0.);
}



void cMenu::renderPlayer(int x, int y)
{
    std::vector<std::string> SkyBox;
    
    SkyBox.push_back("Clear Sky HD");
    SkyBox.push_back("Clear Sky");
    SkyBox.push_back("Nuke");
    SkyBox.push_back("Cloudy");
    SkyBox.push_back("Night");
    SkyBox.push_back("Night 2");
    SkyBox.push_back("Night Flat");
    SkyBox.push_back("Rural");
    SkyBox.push_back("Baggage");
    SkyBox.push_back("Vertigo HD");
    SkyBox.push_back("Jungle");
    SkyBox.push_back("Tibet");
    SkyBox.push_back("Embassy");
    
    this->renderCheckbox(x - 15, y, "Enabled", &vars.visuals.enabled);
    
    //  this->renderCheckbox(x, y, "Enabled", &vars.visuals.enabled);
    this->renderCheckbox(x - 15, y + 20, "Enemy only", &vars.visuals.enemyonly);
    this->renderCheckbox(x - 15, y + 40, "Vis Only Chams", &vars.visuals.visonly);
    this->renderCheckbox(x - 15, y + 60, "Box", &vars.visuals.box);
    this->renderCheckbox(x - 15, y + 80, "Name", &vars.visuals.name);
    this->renderCheckbox(x - 15, y + 100, "Health", &vars.visuals.health);
    this->renderCheckbox(x - 15, y + 120, "Armour", &vars.visuals.armour);
    this->renderCheckbox(x - 15, y + 100, "Health Text", &vars.visuals.healthtext);
    //  this->renderCheckbox(x, y + 165, "Heath text", &vars.visuals.healthtext);
    this->renderCheckbox(x - 15, y + 140, "Skeleton", &vars.visuals.skeleton);
    this->renderCheckbox(x - 15, y + 160, "Snaplines", &vars.visuals.snapline);
    
    vector<string> Players;
    vector<string> Hands;
    vector<string> Weapons;
    
    Players.push_back("Lit");
    Players.push_back("Texture");
    Players.push_back("Wired");
    /*  Players.push_back("Plastic");
     Players.push_back("Dogtag");
     Players.push_back("Gold");
     Players.push_back("Crystal");
     Players.push_back("Velvet");
     Players.push_back("DarkChrome"); */
    
    Hands.push_back("Lit");
    Hands.push_back("Texture");
    Hands.push_back("Wireframe");
    Weapons.push_back("Lit");
    Weapons.push_back("Texture");
    Weapons.push_back("Wireframe");
    
    this->renderCheckbox(x - 15, y + 180, "Player Chams", &vars.visuals.chams);
    this->renderCheckbox(x - 15 , y + 200, "Hand Chams", &vars.visuals.handchams);
    this->renderCheckbox(x - 15, y + 220, "Weapon Chams", &vars.visuals.weaponchams);
    if(vars.visuals.chams) {
        this->renderCombo(x + 10, y + 240, 150, 20, "Lit", Players, vars.visuals.playersType, &vars.players_opend);
    }
    if(vars.visuals.handchams) {
        if(!vars.players_opend)
            this->renderCombo(x + 10, y + 260, 150, 20, "Lit", Hands, vars.visuals.handsType, &vars.hands_opend);
    }
    if(vars.visuals.weaponchams) {
        if((!vars.players_opend) && !vars.hands_opend)
            this->renderCombo(x + 10, y + 280, 150, 20, "Lit", Weapons, vars.visuals.weaponType, &vars.weapons_opend);
    }
    
    
    int iScreenWidth, iScreenHeight;
    pEngine->GetScreenSize(iScreenWidth, iScreenHeight);
    vector<string> Sounds;
    
    Sounds.push_back("None");
    Sounds.push_back("Arena Switch");
    Sounds.push_back("Also Nothing u sperg");
    
    this->renderCheckbox(x + 235, y , "Recoil Crosshair", & vars.visuals.rcrosshair);
    this->renderCheckbox(x + 235, y + 20, "Night Mode", &vars.visuals.nightmode);
    //this->renderCheckbox(x, y + 170, "Bullet Tracers", & vars.visuals.bullettracer);
    this->renderCheckbox(x + 235, y + 40, "SkinChanger", & vars.visuals.skinc);
    //  this->renderCheckbox(x, y + 230, "Grenade ESP", & vars.visuals.grenade);
    // this->renderCheckbox(x + 235, y + 65, "Clantag", & vars.misc.clantag);//misc
    this->renderCheckbox(x + 235, y + 60, "Spread Crosshair", &vars.aimbot.spreadcrosshair);
    //this->renderCheckbox(x + 235, y + 85, "FOV Cirlce", &vars.visuals.fovcircle);
    this->renderCheckbox(x + 235, y + 80, "Radar", &vars.visuals.radar);
    this->renderCheckbox(x + 235, y + 100, "Rage Backtrack ESP", &vars.visuals.backtrackesp);
    this->renderCheckbox(x + 235, y + 120, "Legit Backtrack ESP", &vars.visuals.legitBacktrackesp);
    /* this->renderCheckbox(x + 235, y + 145, "Offscreen ESP", &vars.visuals.offscreenESP);
     this->renderSlider(x + 235, y + 175, 150, "Range", vars.visuals.offscreenESPRange, iScreenHeight / 2, 0); */
    this->renderCheckbox(x + 235, y + 140, "Grenade ESP", &vars.visuals.grenade);
    this->renderCheckbox(x + 235, y + 160, "No Smoke", & vars.visuals.nosmoke);
    this->renderCheckbox(x + 235, y + 180, "Grenade Prediction", & vars.visuals.GrenadePrediction);
    this->renderCheckbox(x + 235, y + 200, "Hitmarker", & vars.visuals.hitmarker);
    this->renderCheckbox(x + 235, y + 220, "Hitmarker Sound", &vars.visuals.hitenabled);
    this->renderCheckbox(x + 235, y + 220, "No Scope", &vars.misc.noscope);
    // this->renderCombo(x + 235, y + 240, 160, 20, "Sound", Sounds, vars.visuals.sound, &vars.sound_opend);
    
    
    
    // this->renderCheckbox(x, y + 210, "Clantag", & vars.misc.clantag);
}


void cMenu::renderMisc(int x, int y) {
    
    //  this->renderCheckbox(x, y, "Clantag", & vars.misc.clantag);//misc
    
    this->renderCheckbox(x, y, "Bhop", &vars.misc.bhop);
    this->renderCheckbox(x, y + 20, "Auto strafe", &vars.misc.autostrafe);
    this->renderCheckbox(x, y + 40, "Circle Strafe", &vars.misc.cstrafe);
    this->renderCheckbox(x, y +  60, "FOV Changer", &vars.misc.fovt);
    this->renderSlider(x + 5, y + 80, 150, "FOV", vars.misc.fov, 70, 0);
    this->renderCheckbox(x, y + 100, "No recoil", &vars.misc.norecoil);
    this->renderCheckbox(x, y + 120, "No visual recoil", &vars.misc.novisual);
    this->renderCheckbox(x, y + 140, "Clantag", &vars.misc.clantag);
    this->renderCheckbox(x, y + 160, "Reveal Ranks", &vars.misc.showrank);
    this->renderCheckbox(x, y + 180, "Thirdperson", & vars.misc.thirdperson);
    this->renderSlider(x + 5, y + 200, 150, "Distance", vars.misc.tpdistance, 360, 0);
    this->renderCheckbox(x, y + 220, "Real Angles", & vars.misc.Real);
    
    this->renderCheckbox(x, y + 240, "Knife Left Hand", & vars.visuals.leftHandKnife);
    
    
    
    //combo for menu color, combos for vis chams and non vis chams, have 3-4 colours and make it effect both teams instead of having separate
    this->renderCheckbox(x + 235, y, "Anti untrust", &vars.misc.antiuntrust);
    this->renderCheckbox(x + 235, y + 20, "Antiscreenshot", &vars.misc.antiscreenshot);
    this->renderCheckbox(x + 235, y + 40, "WorldPaint", &vars.misc.worldpaint);
    this->renderCheckbox(x + 235, y + 60, "Spec List", &vars.misc.showspectators);
    
    vector<string> conf;
    
    conf.push_back("Legit");
    conf.push_back("Rage");
    conf.push_back("HvH");
    
    this->renderCombo(x + 260, y + 80, 150, 20, "Legit", conf, cfg.cfgcombo, &vars.cfg_opend);
    if(!vars.cfg_opend){
        this->renderButton(x + 260, y + 105, "Save", &cfg.saveconfig);
        this->renderButton(x + 345, y + 105, "Load", &cfg.loadconfig);
    }
    
}




void cMenu::renderColors(int x, int y) {
    
    vector<string> Colors;
    
    Colors.push_back("Chams");
    Colors.push_back("Hands/Weapon");
    Colors.push_back("World Colours");
    
    // this->renderCombo(x + 100, y + 22 + 14, 160, 20, "CT Colours", Colors, vars.colors.combo, &vars.colors_opend);
    
    
    
    
    vars.colors.ctchams = Color(vars.visuals.CTcham_red, vars.visuals.CTcham_green, vars.visuals.CTcham_blue, 255);
    this->renderSlider_c(x + 5, y + 20, 150, "Red", vars.visuals.CTcham_red, 255, 0, vars.colors.ctchams);
    this->renderSlider_c(x + 5, y + 40, 150, "Green", vars.visuals.CTcham_green, 255, 0, vars.colors.ctchams);
    this->renderSlider_c(x + 5, y + 60, 150, "Blue", vars.visuals.CTcham_blue, 255, 0, vars.colors.ctchams);
    draw->drawstring(x, y, FontColor, mFont, "Visible CT Chams");
    
    vars.colors.ctchams_ign = Color(vars.visuals.CTchamhid_red, vars.visuals.CTchamhid_green, vars.visuals.CTchamhid_blue, 255);
    this->renderSlider_c(x + 259, y + 20, 150, "Red", vars.visuals.CTchamhid_red, 255, 0, vars.colors.ctchams_ign);
    this->renderSlider_c(x + 259, y + 40, 150, "Green", vars.visuals.CTchamhid_green, 255, 0, vars.colors.ctchams_ign);
    this->renderSlider_c(x + 259, y + 60, 150, "Blue", vars.visuals.CTchamhid_blue, 255, 0, vars.colors.ctchams_ign);
    draw->drawstring(x + 250, y, FontColor, mFont, "Hidden CT Chams");
    
    vars.colors.tchams = Color(vars.visuals.Tcham_red, vars.visuals.Tcham_green, vars.visuals.Tcham_blue, 255);
    this->renderSlider_c(x + 5, y + 100, 150, "Red", vars.visuals.Tcham_red, 255, 0, vars.colors.tchams);
    this->renderSlider_c(x + 5, y + 120, 150, "Green", vars.visuals.Tcham_green, 255, 0, vars.colors.tchams);
    this->renderSlider_c(x + 5, y + 140, 150, "Blue", vars.visuals.Tcham_blue, 255, 0, vars.colors.tchams);
    draw->drawstring(x, y + 80, FontColor, mFont, "Visible T Chams");
    
    vars.colors.tchams_ign = Color(vars.visuals.Tchamhid_red, vars.visuals.Tchamhid_green, vars.visuals.Tchamhid_blue, 255);
    this->renderSlider_c(x + 259, y + 100, 150, "Red", vars.visuals.Tchamhid_red, 255, 0, vars.colors.tchams_ign);
    this->renderSlider_c(x + 259, y + 120, 150, "Green", vars.visuals.Tchamhid_green, 255, 0, vars.colors.tchams_ign);
    this->renderSlider_c(x + 259, y + 140, 150, "Blue", vars.visuals.Tchamhid_blue, 255, 0, vars.colors.tchams_ign);
    draw->drawstring(x + 250, y + 80, FontColor, mFont, "Hidden T Chams");
    
    
    
    
    vars.colors.hands = Color(vars.visuals.arm_red, vars.visuals.arm_green, vars.visuals.arm_blue, 255);
    this->renderSlider_c(x + 5, y + 180, 150, "Red", vars.visuals.arm_red, 255, 0, vars.colors.hands);
    this->renderSlider_c(x + 5, y + 200, 150, "Green", vars.visuals.arm_green, 255, 0, vars.colors.hands);
    this->renderSlider_c(x + 5, y + 220, 150, "Blue", vars.visuals.arm_blue, 255, 0, vars.colors.hands);
    draw->drawstring(x, y + 160, FontColor, mFont, "Hands");
    
    vars.colors.weapon = Color(vars.visuals.weapon_red, vars.visuals.weapon_green, vars.visuals.weapon_blue, 255);
    this->renderSlider_c(x + 259, y + 180, 150, "Red", vars.visuals.weapon_red, 255, 0, vars.colors.weapon);
    this->renderSlider_c(x + 259, y + 200, 150, "Green", vars.visuals.weapon_green, 255, 0, vars.colors.weapon);
    this->renderSlider_c(x + 259, y + 220, 150, "Blue", vars.visuals.weapon_blue, 255, 0, vars.colors.weapon);
    draw->drawstring(x + 250, y + 160, FontColor, mFont, "Weapons");
    
    vars.colors.menu = Color(vars.visuals.menu_red, vars.visuals.menu_blue, vars.visuals.menu_green, 242);
    this->renderSlider_c(x + 5, y + 260, 150, "Red", vars.visuals.menu_red, 255, 0, vars.colors.menu);
    this->renderSlider_c(x + 5, y + 280, 150, "Green", vars.visuals.menu_blue, 255, 0, vars.colors.menu);
    this->renderSlider_c(x + 5, y + 300, 150, "Blue", vars.visuals.menu_green, 255, 0, vars.colors.menu);
    draw->drawstring(x, y + 240, FontColor, mFont, "Menu");
    
    /* vars.colors.arrow = Color(vars.visuals.fov_arrows_esp_color_r, vars.visuals.fov_arrows_esp_color_g, vars.visuals.fov_arrows_esp_color_b, 255);
     this->renderSlider_c(x + 235, y + 240, 160, "Red", vars.visuals.fov_arrows_esp_color_r, 255, 0, vars.colors.arrow);
     this->renderSlider_c(x + 235, y + 260, 160, "Green", vars.visuals.fov_arrows_esp_color_g, 255, 0, vars.colors.arrow);
     this->renderSlider_c(x + 235, y + 280, 160, "Blue", vars.visuals.fov_arrows_esp_color_b, 255, 0, vars.colors.arrow);
     draw->drawstring(x, y + 220, FontColor, mFont, "Player Indicator");*/
    
    
    // add slider for menu colour, save all these values in cfg.cpp
    
    // this->drawcolorpicker(x, y + 20, "World", vars.colors.world);
    // this->drawcolorpicker(x + 235, y + 20, "Sky", vars.colors.sky);
}

// Menu tabs
enum mTab
{
    Main     = 0,
    tab_1    = 1,//rage
    tab_2    = 2,//aa
    tab_3    = 3,//legit
    tab_4    = 4,//visuals
    tab_5    = 5,//misc
    tab_6    = 6//colours

};

static int curTab = mTab::Main;

// This is where the menu is "put together"



void cMenu::renderMenu() {
    
    static int x = 100;
    static int y = 100;
    int w = 489;//489
    int h = 477;
    int hh = 22; // The height of the dragable area
    
    
    draw->fillrgba(x, y, w, h, Color(28, 28, 28, 255));
    draw->fillrgba(x, y + 19, w, 3, Color(163, 12, 224, 255));
    draw->drawstring(x + ( ( w - 4 ) / 2 ) - 2, y + 10, Color::White(), mFont, "-Breathless v2", true);
    
    if(curTab != 0){

        draw->drawline(x + 5, y + h - 10, x + 15, y + h - 13, FontColor);
        draw->drawline(x + 5, y + h - 10, x + 15, y + h - 7, FontColor);
        
        draw->drawline(x + 5, y + h - 10, x + 25, y + h - 10, FontColor);

        //draw->drawline(x + 15, y + h - 10, x + 15, y + h - 4, FontColor);
        
        if(draw->inArea(x - 5, y + h - 30, 30, 50)) {
            
            
            
            if(WasReleased)
                
                curTab = 0;
            
            
        }
        
        

    //draw->drawstring(x + 5, y + h - 13, FontColor, mFont, "back");
    }
    // Handles tabs
    
    //top
    
if(curTab == 0){

    if(draw->inArea(x + 15, y + 37, 143, 200)) {
        
        
        
        if(WasReleased)
            
            curTab = 1;
        
        
    } else if(draw->inArea(x + 173, y + 37, 143, 200)) {
        
        
        
        if(WasReleased)
            
            curTab = 2;
        
        
    } else if(draw->inArea(x + 331, y + 37, 143, 200)) {
        
        
        
        if(WasReleased)
            
            curTab = 3;
        
    }
    
    //bottom
    
    else if(draw->inArea(x + 15, y + 262, 143, 200)) {
        
        
        if(WasReleased)
            
            curTab = 4;
        
    } else if(draw->inArea(x + 173, y + 262, 143, 200)) {
        
        
        if(WasReleased)
            
            curTab = 5;
        
    }
    else if(draw->inArea(x + 331, y + 262, 143, 200)) {
        
        
        if(WasReleased)
            
            curTab = 6;
        
    }
}
    
    switch (curTab) {
            
        case 0:
            //top
            
            this->render_tab_section(x + 15, y + 37, 143, 200);
            draw->drawstring(x + 85, y + 135, Avoz, iFont, "A", true);
            
            this->render_tab_section(x + 173, y + 37, 143, 200);
            draw->drawstring(x + 243, y + 135, Avoz, iFont, "B", true);
            
            this->render_tab_section(x + 331, y + 37, 143, 200);
            draw->drawstring(x + 401, y + 135, Avoz, iFont2, "G", true);
            
            //bottom
            
            this->render_tab_section(x + 15, y + 262, 143, 200);
            draw->drawstring(x + 85, y + 360, Avoz, iFont, "C", true);
            
            this->render_tab_section(x + 173, y + 262, 143, 200);
            draw->drawstring(x + 243, y + 360, Avoz, iFont, "D", true);
            
            this->render_tab_section(x + 331, y + 262, 143, 200);
            draw->drawstring(x + 401, y + 360, Avoz, iFont3, "H", true);
            break;
            
            
        case 1:
            render_section(x + 15, y + 36, 220, h - 60, "Main");
            render_section(x + 254, y + 36, 220, h - 60, "Other");
            this->renderAim(x + 35, y + 30 + 20 + 5);
            break;
            
        case 2:
            render_section(x + 15, y + 36, 220, h - 60, "Main");
            render_section(x + 254, y + 36, 220, h - 60, "Other");
            this->renderLegit(x + 35, y + 30 + 20 + 5);
            break;
            
        case 3:
            render_section(x + 15, y + 36, 220, h - 60, "Main");
            render_section(x + 254, y + 36, 220, h - 60, "Other");
            this->renderAntiAim(x + 35, y + 30 + 20 + 5);
            break;
            
        case 4:
            render_section(x + 15, y + 36, 220, h - 60, "Main");
            render_section(x + 254, y + 36, 220, h - 60, "Other");
            this->renderPlayer(x + 35, y + 30 + 20 + 5);
            break;
            
        case 5://         |     players     |     other     |
            render_section(x + 15, y + 36, 220, h - 60, "Main");
            render_section(x + 254, y + 36, 220, h - 60, "Other");
            this->renderMisc(x + 35, y + 30 + 20 + 5);
            break;
            
        case 6:
            render_section(x + 15, y + 36, 220, h - 60, "Main");
            render_section(x + 254, y + 36, 220, h - 60, "Other");
            this->renderColors(x + 35, y + 30 + 20 + 5);
            break;
            
        default:
            break;
            
    }
    
    //this->renderConfigs(x + 25, y + h - 56);
    
    config->getConfig(cfg.cfgcombo);
    
    if(!vars.cfgInit) {
        skins_cfg->LoadSkins();
        config->LoadConfig();
        vars.cfgInit = true;
    }
    
    if(cfg.loadconfig) {
        skins_cfg->LoadSkins();
        config->LoadConfig();
    }
    
    if(cfg.saveconfig) {
        config->SaveConfig();
    }
    
    // Render strings last so they're on top
    //draw->drawstring(x + 50, y + 22 + 16, Avoz, osFont, "A", true);
    //draw->drawstring(x + 150, y + 22 + 17, Avoz, osFont, "J", true);
    //draw->drawstring(x + 250, y + 22 + 16, Avoz, osFont, "B", true);
    //draw->drawstring(x + 350, y + 22 + 17, Avoz, osFont, "C", true);
    //draw->drawstring(x + 450, y + 22 + 15, Avoz, osFont, "G", true);
    
    
    Pressed(MOUSE_LEFT);
    draw->MoveMenu(x, y, w, hh, 1);
    
}

