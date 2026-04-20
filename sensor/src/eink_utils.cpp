#include "GxEPD2_BW.h"
#include "eink_utils.h"

// pinout used:
//
// - BUSY - 18
// - RST - 19
// - DC - 20
// - CS - 21
// - CLK - 23
// - DIN - 22
// - GND - eh, GND?
// - VCC - 3.3V (cause esp32c6 is 3.3 native)

GxEPD2_BW<GxEPD2_154_GDEY0154D67, GxEPD2_154_GDEY0154D67::HEIGHT> display(GxEPD2_154_GDEY0154D67(/*CS*/ 21, /*DC*/ 20, /*RST*/ 19, /*BUSY*/ 18));

void setupEink() {
    display.init(115200, true, 2, false);
}

void einkDrawLogo() {
    display.setFullWindow();
    display.firstPage();
    do {
        display.drawBitmap(0, 0, LOGO, 200, 200, GxEPD_BLACK);
    } while (display.nextPage());
}
