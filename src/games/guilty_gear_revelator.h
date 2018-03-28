#ifndef GUILTY_GEAR_REVELATOR_H
#define

// Using[] PROGMEM here to save some space for variables

const char ggx_Aganos[] PROGMEM = "Aganos";

const char *const guilty_gear[] PROGMEM = {
    ki_Aganos,
};

#define n_guilty_gear (sizeof(guilty_gear) / sizeof(const char *))

#endif // GUILTY_GEAR_REVELATOR_H