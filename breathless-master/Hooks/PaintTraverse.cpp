#include "main.h"
#include "../Drawings/menu.h"
#include "../Hacks/crosshair.h"
#include "../Hacks/esp.h"
#include "../Hacks/spectators.h"
#include "../Hacks/antiaiminfos.h"
#include "../Hacks/hitmarker.h"

void hkPaintTraverse(void* thisptr, VPANEL panel, bool forceRepaint, bool allowForce)
{
    
    if (vars.misc.noscope && !strcmp("HudZoom", pPanel->GetName(panel)))
        return;
    
    paintVMT->GetOriginalMethod<tPaintTraverse>(42)(thisptr, panel, forceRepaint, allowForce);
    
    C_BaseEntity* local = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    static VPANEL last = 0;
    
    if(!last)
    {
        if(strstr(pPanel->GetName(panel), "FocusOverlayPanel"))
        {
            framefont       = draw->createfont(framefont, "Verdana", 11, FONTFLAG_ANTIALIAS); // v
            specfont    = draw->createfont(specfont, "Verdana Bold", 11, FONTFLAG_OUTLINE);   // Used for spectatorwindow // v
            mFont       = draw->createfont(mFont, "Verdana", 12, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);         // Menu font // v
            cFont           = draw->createfont(cFont, "Verdana Bold", 13, FONTFLAG_ANTIALIAS); // Combos // v
            sFont           = draw->createfont(sFont, "Verdana Bold", 12, FONTFLAG_ANTIALIAS);     // Used for sliders // v
            eFont       = draw->createfont(eFont, "Verdana Bold", 11, FONTFLAG_DROPSHADOW);  // ESP font // v
            //       sFont       = draw->createfont(sFont, "Verdana", 11, FONTFLAG_OUTLINE);     // Used for sliders
            xFont          = draw->createfont(xFont, "osmiummenufont", 60, FONTFLAG_ANTIALIAS);
            xFontGay          = draw->createfont(xFontGay, "tabs-monarch", 60, FONTFLAG_ANTIALIAS);
            lbyfont         = draw->createfont(lbyfont, "Verdana Bold", 30, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);
            pFont           = draw->createfont(pFont, "Verdana Bold", 50, FONTFLAG_ANTIALIAS);
            supremacy           = draw->createfont(supremacy, "Verdana", 12, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);     // Used for sliders // v
            slider           = draw->createfont(slider, "Verdana Bold", 12, FONTFLAG_ANTIALIAS);     // Used for sliders // v // fontflag_none
            subtitleFont    = draw->createfont(cFont, "Verdana Bold", 30, FONTFLAG_ANTIALIAS);     // vlone.cc Subtitle
            iFont    = draw->createfont(cFont, "skeet_tab_font_by_lemon", 90, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);     // skrrt
            mSection    = draw->createfont(cFont, "Verdana Bold", 14, FONTFLAG_ANTIALIAS);     // vlone.cc Subtitle
            iFont2    = draw->createfont(cFont, "Calligraphr", 90, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);     //
            iFont3    = draw->createfont(cFont, "badcache", 90, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);     //skrrt
            
            weapfont        = draw->createfont(cFont, "csgo_icons", 20,FONTFLAG_ANTIALIAS);                              // Weapon Font
            test        = draw->createfont(cFont, "Furious Styles", 20,FONTFLAG_ANTIALIAS);                              // Weapon Font
            LBY        = draw->createfont(LBY, "Verdana", 37,FONTFLAG_ANTIALIAS);                              // Weapon Font
            
            
            
            // Interfaces::Surface->SetFontGlyphSet(Fonts::Slider, "Verdana", 12, 100, 0, 0, FONTFLAG_OUTLINE);
            
            
            last = panel;
        }
        
        {   // Initialisation
            vars.colors.ctchams     = Color::White();
            vars.colors.ctchams_ign = Color::Red();
            
            vars.colors.tchams      = Color::White();
            vars.colors.tchams_ign  = Color::Red();
            
            vars.colors.tbox        = Color(18, 18, 18, 255);
            vars.colors.tbox_ign    = Color(18, 18, 18, 255);
            
            vars.colors.ctbox       = Color(18, 18, 18, 255);
            vars.colors.ctbox_ign   = Color(18, 18, 18, 255);
            
            vars.colors.hands       = Color(255, 0, 83, 255);
            vars.colors.weapon      = Color(18, 18, 18, 255);
            
            vars.colors.scope       = Color::Red();
            vars.colors.world       = Color::Test();
            vars.colors.sky         = Color::Red();
        }
        
    }
    
    
    if(panel == last)
    {
        
        if(vars.misc.antiscreenshot && pEngine->IsTakingScreenshot())
            return;
        
        pwnmymenu();
        
        {   // Drawing features / own scope just for readablity
            
            DrawOtherESP();     // Other ESP
            
            DrawPlayerESP();    // Player esp
            
            DrawScope(local);   // Draws the crosshar for noscope
            
            rCrosshair(local);  // Draws recoil crosshair
            
            //manualaa(local);        // Manual AA idicator
            
            manualAAIndicators();
            
            Spectatorlist();    // Draws speclist
            
            //aw_hitmarker->initilisze();
        }
        
        if(vars.menu)
        {   // Draw menu items
            menu->renderMenu();
            draw->drawmouse();
            pCvar->FindVar("cl_mouseenable");
        }
        

    }
}

