#ifndef STREET_FIGHTER_5_H
#define STREET_FIGHTER_5_H

// Using[] PROGMEM here to save some space for variables

const char sf5_Abigail[] PROGMEM = "Abigail";
const char sf5_Akuma[] PROGMEM = "Akuma";
const char sf5_Alex[] PROGMEM = "Alex";
const char sf5_Balrog[] PROGMEM = "Balrog";
const char sf5_Birdie[] PROGMEM = "Birdie";
const char sf5_Cammy[] PROGMEM = "Cammy";
const char sf5_ChunLi[] PROGMEM = "Chun-Li";
const char sf5_Dhalsim[] PROGMEM = "Dhalsim";
const char sf5_Ed[] PROGMEM = "Ed";
const char sf5_FANG[] PROGMEM = "F.A.N.G";
const char sf5_Guile[] PROGMEM = "Guile";
const char sf5_Ibuki[] PROGMEM = "Ibuki";
const char sf5_Juri[] PROGMEM = "Juri";
const char sf5_Karin[] PROGMEM = "Karin";
const char sf5_Ken[] PROGMEM = "Ken";
const char sf5_Kolin[] PROGMEM = "Kolin";
const char sf5_Laura[] PROGMEM = "Laura";
const char sf5_Bison[] PROGMEM = "Bison";
const char sf5_Menat[] PROGMEM = "Menat";
const char sf5_Nash[] PROGMEM = "Nash";
const char sf5_Necalli[] PROGMEM = "Necalli";
const char sf5_RMika[] PROGMEM = "R. Mika";
const char sf5_Rashid[] PROGMEM = "Rashid";
const char sf5_Ryu[] PROGMEM = "Ryu";
const char sf5_Urien[] PROGMEM = "Urien";
const char sf5_Vega[] PROGMEM = "Vega";
const char sf5_Zangief[] PROGMEM = "Zangief";
const char sf5_Zeku[] PROGMEM = "Zeku";

//const char sf5_Blanka[] PROGMEM = "Blanka";
//const char sf5_Cody[] PROGMEM = "Cody";
//const char sf5_Falke[] PROGMEM = "Falke";
//const char sf5_G[] PROGMEM = "G";
//const char sf5_Sagat[] PROGMEM = "Sagat";
//const char sf5_Sakura[] PROGMEM = "Sakura";

const char *const street_fighter_5[] PROGMEM = {
    sf5_Abigail,
    sf5_Akuma,
    sf5_Alex,
    sf5_Balrog,
    sf5_Birdie,
    sf5_Cammy,
    sf5_ChunLi,
    sf5_Dhalsim,
    sf5_Ed,
    sf5_FANG,
    sf5_Guile,
    sf5_Ibuki,
    sf5_Juri,
    sf5_Karin,
    sf5_Ken,
    sf5_Kolin,
    sf5_Laura,
    sf5_Bison,
    sf5_Menat,
    sf5_Nash,
    sf5_Necalli,
    sf5_RMika,
    sf5_Rashid,
    sf5_Ryu,
    sf5_Urien,
    sf5_Vega,
    sf5_Zangief,
    sf5_Zeku,
};

#define n_street_fighter_5 (sizeof(street_fighter_5) / sizeof(const char *))

#endif // STREET_FIGHTER_5_H    
