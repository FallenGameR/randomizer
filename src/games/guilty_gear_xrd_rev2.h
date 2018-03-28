#ifndef GUILTY_GEAR_XRD_REV2_H
#define GUILTY_GEAR_XRD_REV2_H

// Using[] PROGMEM here to save some space for variables

const char ggx_Aganos[] PROGMEM = "Aganos";

/*
Sol Badguy
Ky Kiske
Millia Rage
Zato-1
May
Potemkin
Chipp Zanuff
Venom
Axl Low
I-No
Faust
Slayer
Ramlethal
Bedman
Sin Kiske
Elphelt
Leo Whitefang
Johnny
Jack-O Valentine
Jam Kuradoberi
Raven
Kum Haehyun
Dizzy
/**/

const char *const guilty_gear[] PROGMEM = {
    ki_Aganos,
};

#define n_guilty_gear (sizeof(guilty_gear) / sizeof(const char *))

#endif // GUILTY_GEAR_XRD_REV2_H