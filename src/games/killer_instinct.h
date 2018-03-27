#ifndef KILLER_INSTINCT_H
#define KILLER_INSTINCT_H

// Using PROGMEM here to save some space for variables

const char killer_instinct_Aganos = "Aganos";
const char killer_instinct_Arbiter = "Arbiter";
const char killer_instinct_ARIA = "ARIA";
const char killer_instinct_BlackOrchid = "Black Orchid";
const char killer_instinct_ChiefThunder = "Chief Thunder";
const char killer_instinct_Cinder = "Cinder";
const char killer_instinct_Eyedol = "Eyedol";
const char killer_instinct_Eagle = "Eagle";
const char killer_instinct_Fulgore = "Fulgore";
const char killer_instinct_Gargos = "Gargos";
const char killer_instinct_GeneralRAAM = "General RAAM";
const char killer_instinct_Glacius = "Glacius";
const char killer_instinct_Hisako = "Hisako";
const char killer_instinct_Jago = "Jago";
const char killer_instinct_KanRa = "Kan-Ra";
const char killer_instinct_Kilgore = "Kilgore";
const char killer_instinct_KimWu = "Kim Wu";
const char killer_instinct_Maya = "Maya";
const char killer_instinct_Mira = "Mira";
const char killer_instinct_Omen = "Omen";
const char killer_instinct_Rash = "Rash";
const char killer_instinct_Riptor = "Riptor";
const char killer_instinct_Sabrewulf = "Sabrewulf";
const char killer_instinct_Sadira = "Sadira";
const char killer_instinct_ShadowJago = "Shadow Jago";
const char killer_instinct_ShinHisako = "Shin Hisako";
const char killer_instinct_Spinal = "Spinal";
const char killer_instinct_TJCombo = "TJ Combo";
const char killer_instinct_Tusk = "Tusk";

const char *const killer_instinct[] PROGMEM = {
    killer_instinct_Aganos,
    killer_instinct_Arbiter,
    killer_instinct_ARIA,
    killer_instinct_BlackOrchid,
    killer_instinct_ChiefThunder,
    killer_instinct_Cinder,
    killer_instinct_Eyedol,
    killer_instinct_Eagle,
    killer_instinct_Fulgore,
    killer_instinct_Gargos,
    killer_instinct_GeneralRAAM,
    killer_instinct_Glacius,
    killer_instinct_Hisako,
    killer_instinct_Jago,
    killer_instinct_KanRa,
    killer_instinct_Kilgore,
    killer_instinct_KimWu,
    killer_instinct_Maya,
    killer_instinct_Mira,
    killer_instinct_Omen,
    killer_instinct_Rash,
    killer_instinct_Riptor,
    killer_instinct_Sabrewulf,
    killer_instinct_Sadira,
    killer_instinct_ShadowJago,
    killer_instinct_ShinHisako,
    killer_instinct_Spinal,
    killer_instinct_TJCombo,
    killer_instinct_Tusk,
}

#define n_killer_instinct (sizeof(killer_instinct) / sizeof(const char *))

#endif // KILLER_INSTINCT_H
