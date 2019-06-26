#include "main.h"

cDrawings* draw = new cDrawings();

HFONT supremacy, subtitleFont, slider, pFont, framefont, mFont, lbyfont, eFont, sFont, specfont, xFont, cFont, xFontGay, iFont, mSection, iFont2, iFont3, weapfont, test, LBY; // if you want to add more fonts add them here and in drawings.h
bool bWasPressed, bWasReleased;


typedef struct {
    
    char    m_szDefinition[ 12 ];
    char    m_szShiftDefinition[ 12 ];
    char    m_szAltDefinition[ 12 ];
    
}KeyStroke_t;

template<class T, class U>
inline T clamp(T in, U low, U high)
{
    if (in <= low)
        return low;
    else if (in >= high)
        return high;
    else
        return in;
}

void cDrawings::DrawTriangle(Vector pos, float size, Color color)
{
    // Drawing a Triangle
    Vector up, right, left, up_right, up_left;
    Vector s_up, s_right, s_left, s_up_right, s_up_left;
    
    up[0] = pos[0];
    up[1] = pos[1];
    up[2] = pos[2] + size / 2;
    
    WorldToScreen(up, s_up);
    
    up_left[0] = pos[0] - size / 2;
    up_left[1] = pos[1] + size / 2;
    up_left[2] = pos[2] - size / 2;
    
    WorldToScreen(up_left, s_up_left);
    
    up_right[0] = pos[0] + size / 2;
    up_right[1] = pos[1] + size / 2;
    up_right[2] = pos[2] - size / 2;
    
    WorldToScreen(up_right, s_up_right);
    
    right[0] = pos[0] + size / 2;
    right[1] = pos[1] - size / 2;
    right[2] = pos[2] - size / 2;
    
    WorldToScreen(right, s_right);
    
    left[0] = pos[0] - size / 2;
    left[1] = pos[1] - size / 2;
    left[2] = pos[2] - size / 2;
    
    WorldToScreen(left, s_left);
    
    
    draw->drawline(s_right[0], s_right[1], s_left[0], s_left[1], color);
    
    draw->drawline(s_right[0], s_right[1], s_up_right[0], s_up_right[1], color);
    draw->drawline(s_left[0], s_left[1], s_up_left[0], s_up_left[1], color);
    
    draw->drawline(s_up_right[0], s_up_right[1], s_up_left[0], s_up_left[1], color);
    
    draw->drawline(s_right[0], s_right[1], s_up[0], s_up[1], color);
    draw->drawline(s_left[0], s_left[1], s_up[0], s_up[1], color);
    draw->drawline(s_up_left[0], s_up_left[1], s_up[0], s_up[1], color);
    draw->drawline(s_up_right[0], s_up_right[1], s_up[0], s_up[1], color);
}

void cDrawings::rotate_triangle(std::vector<Vector2D>& points, float rotation)
{
    const auto points_center = (points.at(0) + points.at(1) + points.at(2)) / 3;
    for (auto& point : points)
    {
        point -= points_center;
        
        const auto temp_x = point.x;
        const auto temp_y = point.y;
        
        const auto theta = degrees_to_radians(rotation);
        const auto c = cosf(theta);
        const auto s = sinf(theta);
        
        point.x = temp_x * c - temp_y * s;
        point.y = temp_x * s + temp_y * c;
        
        point += points_center;
    }
}

void cDrawings::add_textured_polygon(int n, Vertex_t * vertice, Color color)
{
    static auto texture_id = pSurface->CreateNewTextureID(true);
    
    static unsigned char buf[4] = { 255, 255, 255, 255 };
    
    pSurface->DrawSetTextureRGBA(texture_id, buf, 1, 1);
    pSurface->DrawSetColor(color);
    pSurface->DrawSetTexture(texture_id);
    
    pSurface->DrawTexturedPolygon(n, vertice);
}

void cDrawings::Triangle(std::vector<Vector2D> points){
    std::vector<Vertex_t>vertices{ Vertex_t(points.at(0)), Vertex_t(points.at(1)), Vertex_t(points.at(2)) };
}

void cDrawings::Circle(float x, float y, float r, float s, Color color)
{
    float Step = PI * 2.0 / s;
    for (float a = 0; a < (PI*2.0); a += Step)
    {
        float x1 = r * cos(a) + x;
        float y1 = r * sin(a) + y;
        float x2 = r * cos(a + Step) + x;
        float y2 = r * sin(a + Step) + y;
        pSurface->DrawSetColor(color);
        pSurface->DrawLine(x1, y1, x2, y2);
        
    }
}

void cDrawings::DrawTexturedPoly(int n, Vertex_t* vertice, Color col)
{
    static int texture_id = pSurface->CreateNewTextureID(true);
    static unsigned char buf[4] = { 255, 255, 255, 255 };
    pSurface->DrawSetTextureRGBA(texture_id, buf, 1, 1);
    pSurface->DrawSetColor(col);
    pSurface->DrawSetTexture(texture_id);
    pSurface->DrawTexturedPolygon(n, vertice);
}

void cDrawings::DrawFilledCircle(Vector2D center, Color color, float radius, float points)
{
    std::vector<Vertex_t> vertices;
    float step = (float)M_PI * 2.0f / points;
    
    for (float a = 0; a < (M_PI * 2.0f); a += step)
        vertices.push_back(Vertex_t(Vector2D(radius * cosf(a) + center.x, radius * sinf(a) + center.y)));
    
    DrawTexturedPoly((int)points, vertices.data(), color);
}

void cDrawings::add_triangle_filled(std::vector<Vector2D>points, Color color)
{
    std::vector<Vertex_t>vertices{ Vertex_t(points.at(0)), Vertex_t(points.at(1)), Vertex_t(points.at(2)) };
    add_textured_polygon(3, vertices.data(), color);
}

wstring cDrawings::StringToWstring(string str) {
    
    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;
    
    try {
        
        return converter.from_bytes(str);
        
    } catch (range_error) {
        
        wostringstream s;
        s << str.c_str();
        
        return s.str();
        
    }
    
}


wstring cDrawings::wstringtostring(string str) {
    
    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;
    
    try {
        
        return converter.from_bytes(str);
        
    } catch (range_error) {
        
        wostringstream s;
        s << str.c_str();
        
        return s.str();
        
    }
    
}


/* Checks if button was pressed */
auto WasPressed (ButtonCode_t code) -> void {
    
    if (pInputSystem->IsButtonDown(code)) {
        
        bWasPressed = true;
        
    } else if ( ! ( pInputSystem->IsButtonDown( code ) ) ) {
        
        if (bWasPressed)
            bWasReleased = true;
            else
                bWasReleased = false;
                
                bWasPressed = false;
                }
    
}

void cDrawings::drawbox(int x, int y, int w, int h, Color color) {
    
    pSurface->DrawSetColor(color);
    pSurface->DrawOutlinedRect(x, y, x + w, y + h);
    
}


void cDrawings::drawboxoutline(int x, int y, int w, int h, Color color) {
    
    this->drawbox(x, y, w, h, color);
    this->drawbox(x - 1, y - 1, w + 2, h + 2, Color(0, 0, 0, 180));
    this->drawbox(x + 1, y + 1, w - 2, h - 2, Color(0, 0, 0, 180));
    
}


void cDrawings::fillrgba(int x, int y, int w, int h, Color color) {
    
    pSurface->DrawSetColor(color);
    pSurface->DrawFilledRect(x, y, x + w, y + h);
    
}


void cDrawings::drawline(int x, int y, int xx, int yy, Color color) {
    
    pSurface->DrawSetColor(color);
    pSurface->DrawLine(x, y, xx, yy);
    
}


void cDrawings::BorderBox(int x, int y, int w, int h, int thickness, Color color) {
    
    this->fillrgba(x, y, w, thickness, color);
    this->fillrgba(x, y, thickness, h, color);
    this->fillrgba(x + w, y, thickness, h, color);
    this->fillrgba(x, y + h, w + thickness, thickness, color);
    
}


void cDrawings::RectOutlined(int x, int y, int w, int h, int thickness, Color color, Color outlined) {
    
    this->fillrgba(x, y, w, h, color);
    this->BorderBox(x - thickness, y - thickness, w + thickness, h + thickness, thickness, outlined);
    
}


Vector2D cDrawings::GetTextSize(const char* text, HFONT font) {
    
    std::wstring wc = StringToWstring(text);
    
    int x_res, y_res;
    pSurface->GetTextSize(font, wc.c_str(), x_res, y_res);
    
    return Vector2D(x_res, y_res);
    
}


HFONT cDrawings::createfont(HFONT font, const char *szFont, int tall, int flags) {
    
    font = pSurface->CreateFont();
    pSurface->SetFontGlyphSet(font, szFont, tall, 150, 0, 0, flags);
    
    return font;
    
}


void cDrawings::drawstring(int x, int y, Color color, HFONT font, const char *szString, bool bCenter) {
    
    if(szString != NULL) {
        
        wstring wString = this->wstringtostring(szString);
        
        if(bCenter) {
            
            int wide, tall;
            pSurface->GetTextSize(font, wString.c_str(), wide, tall);
            x -= wide / 2;
            y -= tall / 2;
            
        }
        
        pSurface->DrawSetTextPos(x, y);
        pSurface->DrawSetTextFont(font);
        pSurface->DrawSetTextColor(color);
        pSurface->DrawPrintText(wString.c_str(), (int)wcslen(wString.c_str()));
        
    }
    
}


//=====================================


void cDrawings::drawCrosshair(int x, int y, Color col) {
    
    this->drawline(x - 5, y, x + 5, y, col);
    this->drawline(x, y - 5, x, y + 5, col);
    
}


ViVecMouse::ViVecMouse(void) {
    
}


ViVecMouse::ViVecMouse(int X, int Y) {
    
    x = X;
    y = Y;
    
}


ViVecMouse cDrawings::GetMouse() {
    
    int x, y;
    pInputSystem->GetCursorPosition(&x, &y);
    
    ViVecMouse pPosition = ViVecMouse(x, y);
    return pPosition;
}


int cDrawings::CalcPos(int x) { // Not really sure who made this but shout out to you
    
    int iRealXStart = ((1920 / 2) - (1920 / 2)) + x;
    
    return GetMouse().x - iRealXStart;
    
}


bool cDrawings::inArea(int x, int y, int w, int h) {
    
    if(GetMouse().x > x && GetMouse().y > y && GetMouse().x < x + w && GetMouse().y < y + h)
        return true;
    else
        return false;
    
}


void cDrawings::drawgradient(int x, int y, int w, int h, Color col1, Color col2) {
    
    this->fillrgba(x, y, w, h, col1);
    
    Byte first = col2.r();
    Byte second = col2.g();
    Byte third = col2.b();
    
    for (int i = 0; i < h; i++) {
        
        float fi = i, fh = h;
        float a = fi / fh;
        int ia = a * 255;
        
        this->fillrgba(x, y + i, w, 1, Color(first, second, third, ia));
        
    }
    
}


void cDrawings::GradientH(int x, int y, int width, int height, Color color1, Color color2) {
    
    float flDifferenceR = (float)(color2.r() - color1.r()) / (float)width;
    float flDifferenceG = (float)(color2.g() - color1.g()) / (float)width;
    float flDifferenceB = (float)(color2.b() - color1.b()) / (float)width;
    
    for (float i = 0.f; i < width; i++) {
        
        Color colGradient = Color(color1.r() + (flDifferenceR * i), color1.g() + (flDifferenceG * i), color1.b() + (flDifferenceB * i), color1.a());
        
        this->fillrgba(x + i, y, 1, height, colGradient);
        
    }
    
}


void cDrawings::drawmouse() { // Draws mouse
    
    int mouse_x = this->GetMouse().x;
    int mouse_y = this->GetMouse().y;
    
    this->fillrgba(mouse_x + 1, mouse_y, 1, 17, Color(0, 0, 0, 255));
    
    
    for(int i = 0; i < 11; i++)
        this->fillrgba(mouse_x + 2 + i, mouse_y + 1 + i, 1, 1, Color(0, 0, 0, 255));
    
    this->fillrgba(mouse_x + 7, mouse_y + 12, 6, 1, Color(0, 0, 0, 255));
    this->fillrgba(mouse_x + 6, mouse_y + 12, 1, 1, Color(0, 0, 0, 255));
    this->fillrgba(mouse_x + 5, mouse_y + 13, 1, 1, Color(0, 0, 0, 255));
    this->fillrgba(mouse_x + 4, mouse_y + 14, 1, 1, Color(0, 0, 0, 255));
    this->fillrgba(mouse_x + 3, mouse_y + 15, 1, 1, Color(0, 0, 0, 255));
    this->fillrgba(mouse_x + 2, mouse_y + 16, 1, 1, Color(0, 0, 0, 255));
    
    
    for(int i = 0; i < 4; i++)
        this->fillrgba(mouse_x + 2 + i, mouse_y + 2 + i, 1, 14 - (i * 2), Color(150, 20, 20, 230));
    
    this->fillrgba(mouse_x + 6, mouse_y + 6, 1, 6, Color(150, 20, 20, 230));
    this->fillrgba(mouse_x + 7, mouse_y + 7, 1, 5, Color(150, 20, 20, 230));
    this->fillrgba(mouse_x + 8, mouse_y + 8, 1, 4, Color(150, 20, 20, 230));
    this->fillrgba(mouse_x + 9, mouse_y + 9, 1, 3, Color(150, 20, 20, 230));
    this->fillrgba(mouse_x + 10, mouse_y + 10, 1, 2, Color(150, 20, 20, 230));
    this->fillrgba(mouse_x + 11, mouse_y + 11, 1, 1, Color(150, 20, 20, 230));
    
}


ViVecMouse ClickPosicao;
bool Janela[8][2];
bool cDrawings::MoveMenu(int & x, int & y, int w, int h, int index) {
    //Credits: Code64/CodeRed
    for (int i = 0; i < 8; i++)
        if (Janela[i][0] && i != index)
            return false;
    
    if (pInputSystem->IsButtonDown(MOUSE_LEFT))
    {
        /* GetMouse().x > x && GetMouse().x < x + w && GetMouse().y >(y - 3) && GetMouse().y < (y - 3) + h */
        if ((GetMouse().x > x && GetMouse().y > y && GetMouse().x < x + w && GetMouse().y < y + h) || Janela[index][0])
        {
            Janela[index][0] = true;
            
            if (!Janela[index][1])
            {
                ClickPosicao.x = GetMouse().x - x;
                ClickPosicao.y = GetMouse().y - y;
                Janela[index][1] = true;
                
            }
        }
        else
        {
            Janela[index][0] = false;
            Janela[index][1] = false;
        }
    }
    
    if (!(pInputSystem->IsButtonDown(MOUSE_LEFT)) && Janela[index][0])
    {
        Janela[index][0] = false;
        Janela[index][1] = false;
    }
    
    if (Janela[index][0])
    {
        x = GetMouse().x - ClickPosicao.x;
        y = GetMouse().y - ClickPosicao.y;
    }
    
    return true;
}



// For handling text boxes and input

KeyStroke_t m_KeyStroke[MOUSE_COUNT + KEY_COUNT] = {
    { "", "", "" },
    { "0", "=", "}" },                      //KEY_0
    { "1", "!", "" },                       //KEY_1
    { "2", "'", "" },                       //KEY_2
    { "3", "", "" },                        //KEY_3
    { "4", "$", "" },                       //KEY_4
    { "5", "%", "" },                       //KEY_5
    { "6", "&", "" },                       //KEY_6
    { "7", "/", "{" },                      //KEY_7
    { "8", "(", "[" },                      //KEY_8
    { "9", ")", "]" },                      //KEY_9
    { "a", "A", "" },                       //KEY_A,
    { "b", "B", "" },                       //KEY_B,
    { "c", "C", "" },                       //KEY_C,
    { "d", "D", "" },                        //KEY_D,
    { "e", "E", "" },                        //KEY_E,
    { "f", "F", "" },                        //KEY_F,
    { "g", "G", "" },                        //KEY_G,
    { "h", "H", "" },                        //KEY_H,
    { "i", "I", "" },                        //KEY_I,
    { "j", "J", "" },                        //KEY_J,
    { "k", "K", "" },                        //KEY_K,
    { "l", "L", "" },                        //KEY_L,
    { "m", "M", "" },                        //KEY_M,
    { "n", "N", "" },                        //KEY_N,
    { "o", "O", "" },                        //KEY_O,
    { "p", "P", "" },                        //KEY_P,
    { "q", "Q", "" },                        //KEY_Q,
    { "r", "R", "" },                        //KEY_R,
    { "s", "S", "" },                        //KEY_S,
    { "t", "T", "" },                        //KEY_T,
    { "u", "U", "" },                        //KEY_U,
    { "v", "V", "" },                        //KEY_V,
    { "w", "W", "" },                        //KEY_W,
    { "x", "X", "" },                        //KEY_X,
    { "y", "Y", "" },                        //KEY_Y,
    { "z", "Z", "" },                        //KEY_Z,
    { "0", "0", "" },                        //KEY_PAD_0,
    { "1", "1", "" },                        //KEY_PAD_1,
    { "2", "2", "" },                        //KEY_PAD_2,
    { "3", "3", "" },                        //KEY_PAD_3,
    { "4", "4", "" },                        //KEY_PAD_4,
    { "5", "5", "" },                        //KEY_PAD_5,
    { "6", "6", "" },                        //KEY_PAD_6,
    { "7", "7", "" },                        //KEY_PAD_7,
    { "8", "8", "" },                        //KEY_PAD_8,
    { "9", "9", "" },                        //KEY_PAD_9,
    { "/", "/", "" },                        //KEY_PAD_DIVIDE,
    { "*", "*", "" },                        //KEY_PAD_MULTIPLY,
    { "-", "-", "" },                        //KEY_PAD_MINUS,
    { "+", "+", "" },                        //KEY_PAD_PLUS,
    { "enter", "enter", "" },                //KEY_PAD_ENTER,
    { ".", ">", "" },                        //KEY_PAD_DECIMAL,
    { "[", "{", "" },                        //KEY_LBRACKET,
    { "]", "}", "" },                        //KEY_RBRACKET,
    { ";", ":", "" },                        //KEY_SEMICOLON,
    { "'", "@", "" },                        //KEY_APOSTROPHE,
    { "`", "", "" },                        //KEY_BACKQUOTE,
    { ",", "<", "" },                        //KEY_COMMA,
    { ".", ">", "" },                        //KEY_PERIOD,
    { "/", "?", "" },                        //KEY_SLASH,
    { "\\", "|", "" },                        //KEY_BACKSLASH,
    { "-", "_", "" },                        //KEY_MINUS,
    { "=", "+", "" },                        //KEY_EQUAL,
    { "enter", "enter", "" },                //KEY_ENTER,
    { "space", "space", "" },                //KEY_SPACE,
    { "backspace", "backspace", "" },        //KEY_BACKSPACE,
    { "tab", "tab", "" },                    //KEY_TAB,
    { "caps", "caps", "" },                    //KEY_CAPSLOCK,
    { "numlock", "numlock", "" },            //KEY_NUMLOCK,
    { "escape", "escape", "" },                //KEY_ESCAPE,
    { "scrlock", "scrlock", "" },            //KEY_SCROLLLOCK,
    { "insert", "insert", "" },                //KEY_INSERT,
    { "delete", "delete", "" },                //KEY_DELETE,
    { "home", "home", "" },                    //KEY_HOME,
    { "end", "end", "" },                    //KEY_END,
    { "pageup", "pageup", "" },                //KEY_PAGEUP,
    { "pagedown", "pagedown", "" },            //KEY_PAGEDOWN,
    { "break", "break", "" },                //KEY_BREAK,
    { "lshift", "lshift", "" },                //KEY_LSHIFT,
    { "rshift", "rshift", "" },                //KEY_RSHIFT,
    { "lalt", "lalt", "" },                    //KEY_LALT,
    { "ralt", "ralt", "" },                    //KEY_RALT,
    { "lctrl", "lctrl", "" },                //KEY_LCONTROL,
    { "rctrl", "rctrl", "" },                //KEY_RCONTROL,
    { "lwin", "lwin", "" },                    //KEY_LWIN,
    { "rwin", "rwin", "" },                    //KEY_RWIN,
    { "app", "app", "" },                    //KEY_APP,
    { "up", "up", "" },                        //KEY_UP,
    { "left", "left", "" },                    //KEY_LEFT,
    { "down", "down", "" },                    //KEY_DOWN,
    { "right", "right", "" },                //KEY_RIGHT,
    { "f1", "f1", "" },                        //KEY_F1,
    { "f2", "f2", "" },                        //KEY_F2,
    { "f3", "f3", "" },                        //KEY_F3,
    { "f4", "f4", "" },                        //KEY_F4,
    { "f5", "f5", "" },                        //KEY_F5,
    { "f6", "f6", "" },                        //KEY_F6,
    { "f7", "f7", "" },                        //KEY_F7,
    { "f8", "f8", "" },                        //KEY_F8,
    { "f9", "f9", "" },                        //KEY_F9,
    { "f10", "f10", "" },                    //KEY_F10,
    { "f11", "f11", "" },                    //KEY_F11,
    { "f12", "f12", "" },                    //KEY_F12,
    { "caps", "capstoggle", "" },            //KEY_CAPSLOCKTOGGLE,
    { "numlock", "numlock", "" },            //KEY_NUMLOCKTOGGLE,
    { "scrlock", "scrlock", "" },            //KEY_SCROLLLOCKTOGGLE,
    
    // Mouse
    { "mouse1", "mouse1", "" },                //MOUSE_LEFT = MOUSE_FIRST,
    { "mouse2", "mouse2", "" },                //MOUSE_RIGHT,
    { "mouse3", "mouse3", "" },                //MOUSE_MIDDLE,
    { "mouse4", "mouse4", "" },                //MOUSE_4,
    { "mouse5", "mouse5", "" },                //MOUSE_5,
    { "mwheelup", "mwheelup", "" },            //MOUSE_WHEEL_UP, A fake button which is 'pressed' and 'released' when the wheel is moved up
    { "mwheeldown", "mwheeldown", "" },        //MOUSE_WHEEL_DOWN, A fake button which is 'pressed' and 'released' when the wheel is moved down
};


int activeIndex = 0;


void cDrawings::textbox(int x, int y, int w, const char* szString, string szValue[100], int inputIndex, int index, bool* var) {
    
    y += index * vars.buttonPadding;
    
    int h = 15;
    
    if(inArea(x, y, w, h)) {
        
        *var = true;
        activeIndex = inputIndex;
        
    } else {
        
        *var = false;
        
    }
    
    this->fillrgba(x, y, w, h, Color(50, 50, 50, 230));
    
    if(inArea(x, y, w, h)) {
        
        this->drawbox(x, y, w, h, Color::Black());
        
    } else {
        
        this->drawbox(x, y, w, h, Color(90, 90, 90, 255));
        
    }
    
    this->drawstring(x + 2, y - 1, Color(160, 160, 160, 255), mFont, ">");
    
    if(szValue[inputIndex].length() > 32) {
        
        size_t getLength = szValue[inputIndex].length();
        szValue[inputIndex].erase(getLength - 1);
        m_nCurrentPos[inputIndex]--;
        
    }
    
    
    if(szValue[inputIndex].length() > 0)
        this->drawstring(x + 15, y - 1, Color(160, 160, 160, 255), mFont, szValue[inputIndex].c_str());
    
    
    this->drawstring(x + w + 3, y - 1, Color(160, 160, 160, 255), mFont, szString);
    
}

void cDrawings::handleinput(int eventcode, string arr[100]) {
    
    if (IsKeyPressed(eventcode, KEY_BACKSPACE)) {
        
        size_t nLength = arr[activeIndex].length();
        
        if (nLength > 0) {
            
            arr[activeIndex].erase(nLength - 1);
            m_nCurrentPos[activeIndex]--;
            
            return;
            
        }
        
    }
    
    
    if(IsKeyPressed(eventcode, KEY_ENTER)) {
        
        m_szChangedValue[activeIndex] = arr[activeIndex];
        
        return;
        
    }
    
    
    if (IsKeyPressed(eventcode, KEY_SPACE)) {
        
        arr[activeIndex].append(" ");
        
        return;
        
    }
    
    
    if (eventcode >= KEY_0 && eventcode <= KEY_EQUAL && arr[activeIndex].length() <= 114) {
        
        if (pInputSystem->IsButtonDown(KEY_LSHIFT) || pInputSystem->IsButtonDown(KEY_RSHIFT)) {
            
            arr[activeIndex].append(m_KeyStroke[eventcode].m_szShiftDefinition);
            m_nCurrentPos[activeIndex]++;
            
        } else {
            
            arr[activeIndex].append(m_KeyStroke[eventcode].m_szDefinition);
            m_nCurrentPos[activeIndex]++;
            
        }
        
    }
    
}
