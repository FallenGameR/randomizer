#ifndef GUILTY_GEAR_XRD_REV2_H
#define GUILTY_GEAR_XRD_REV2_H

// Using[] PROGMEM here to save some space for variables

const char ggx_SolBadguy[] PROGMEM = "Sol Badguy";
const char ggx_KyKiske[] PROGMEM = "Ky Kiske";
const char ggx_MilliaRage[] PROGMEM = "Millia Rage";
const char ggx_Zato1[] PROGMEM = "Zato-1";
const char ggx_May[] PROGMEM = "May";
const char ggx_Potemkin[] PROGMEM = "Potemkin";
const char ggx_ChippZanuff[] PROGMEM = "Chipp Zanuff";
const char ggx_Venom[] PROGMEM = "Venom";
const char ggx_AxlLow[] PROGMEM = "Axl Low";
const char ggx_INo[] PROGMEM = "I-No";
const char ggx_Faust[] PROGMEM = "Faust";
const char ggx_Slayer[] PROGMEM = "Slayer";
const char ggx_Ramlethal[] PROGMEM = "Ramlethal";
const char ggx_Bedman[] PROGMEM = "Bedman";
const char ggx_SinKiske[] PROGMEM = "Sin Kiske";
const char ggx_Elphelt[] PROGMEM = "Elphelt";
const char ggx_LeoWhitefang[] PROGMEM = "Leo Whitefang";
const char ggx_Johnny[] PROGMEM = "Johnny";
const char ggx_JackOValentine[] PROGMEM = "Jack-O Valentine";
const char ggx_JamKuradoberi[] PROGMEM = "Jam Kuradoberi";
const char ggx_Raven[] PROGMEM = "Raven";
const char ggx_KumHaehyun[] PROGMEM = "Kum Haehyun";
const char ggx_Dizzy[] PROGMEM = "Dizzy";

const char *const guilty_gear[] PROGMEM = {
    ggx_SolBadguy,
    ggx_KyKiske,
    ggx_MilliaRage,
    ggx_Zato1,
    ggx_May,
    ggx_Potemkin,
    ggx_ChippZanuff,
    ggx_Venom,
    ggx_AxlLow,
    ggx_INo,
    ggx_Faust,
    ggx_Slayer,
    ggx_Ramlethal,
    ggx_Bedman,
    ggx_SinKiske,
    ggx_Elphelt,
    ggx_LeoWhitefang,
    ggx_Johnny,
    ggx_JackOValentine,
    ggx_JamKuradoberi,
    ggx_Raven,
    ggx_KumHaehyun,
    ggx_Dizzy,
};

#define n_guilty_gear (sizeof(guilty_gear) / sizeof(const char *))

#endif // GUILTY_GEAR_XRD_REV2_H
