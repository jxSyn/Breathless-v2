#include "clantag.h"

void clantag() {
    if (!vars.misc.clantag)
        return;
    
    static int counter = 0;
    static std::string clantag = "Breathless                      ";
    if (++counter > 25) {
        std::rotate(clantag.begin(), clantag.begin() + 1, clantag.end());
        SetClanTag(clantag.c_str(), clantag.c_str());
        counter = 0;
    }
}

