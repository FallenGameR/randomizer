#ifndef KILLER_INSTINCT_H
#define KILLER_INSTINCT_H

// Using[] PROGMEM here to save some space for variables

const char ki_Aganos[] PROGMEM = "Aganos";
const char ki_Arbiter[] PROGMEM = "Arbiter";
const char ki_ARIA[] PROGMEM = "ARIA";
const char ki_BlackOrchid[] PROGMEM = "Black Orchid";
const char ki_ChiefThunder[] PROGMEM = "Chief Thunder";
const char ki_Cinder[] PROGMEM = "Cinder";
const char ki_Eyedol[] PROGMEM = "Eyedol";
const char ki_Eagle[] PROGMEM = "Eagle";
const char ki_Fulgore[] PROGMEM = "Fulgore";
const char ki_Gargos[] PROGMEM = "Gargos";
const char ki_GeneralRAAM[] PROGMEM = "General RAAM";
const char ki_Glacius[] PROGMEM = "Glacius";
const char ki_Hisako[] PROGMEM = "Hisako";
const char ki_Jago[] PROGMEM = "Jago";
const char ki_KanRa[] PROGMEM = "Kan-Ra";
const char ki_Kilgore[] PROGMEM = "Kilgore";
const char ki_KimWu[] PROGMEM = "Kim Wu";
const char ki_Maya[] PROGMEM = "Maya";
const char ki_Mira[] PROGMEM = "Mira";
const char ki_Omen[] PROGMEM = "Omen";
const char ki_Rash[] PROGMEM = "Rash";
const char ki_Riptor[] PROGMEM = "Riptor";
const char ki_Sabrewulf[] PROGMEM = "Sabrewulf";
const char ki_Sadira[] PROGMEM = "Sadira";
const char ki_ShadowJago[] PROGMEM = "Shadow Jago";
const char ki_ShinHisako[] PROGMEM = "Shin Hisako";
const char ki_Spinal[] PROGMEM = "Spinal";
const char ki_TJCombo[] PROGMEM = "TJ Combo";
const char ki_Tusk[] PROGMEM = "Tusk";

const char *const killer_instinct[] PROGMEM = {
    ki_Aganos,
    ki_Arbiter,
    ki_ARIA,
    ki_BlackOrchid,
    ki_ChiefThunder,
    ki_Cinder,
    ki_Eyedol,
    ki_Eagle,
    ki_Fulgore,
    ki_Gargos,
    ki_GeneralRAAM,
    ki_Glacius,
    ki_Hisako,
    ki_Jago,
    ki_KanRa,
    ki_Kilgore,
    ki_KimWu,
    ki_Maya,
    ki_Mira,
    ki_Omen,
    ki_Rash,
    ki_Riptor,
    ki_Sabrewulf,
    ki_Sadira,
    ki_ShadowJago,
    ki_ShinHisako,
    ki_Spinal,
    ki_TJCombo,
    ki_Tusk,
};

#define n_killer_instinct (sizeof(killer_instinct) / sizeof(const char *))

#endif // KILLER_INSTINCT_H
