#ifndef MORTAL_KOMBAT_H
#define MORTAL_KOMBAT_H

// Using[] PROGMEM here to save some space for variables

const char mk_Alien[] PROGMEM = "Alien";
const char mk_BoRaiCho[] PROGMEM = "Bo'Rai Cho";
const char mk_CassieCage[] PROGMEM = "Cassie Cage";
const char mk_DVorah[] PROGMEM = "D'Vorah";
const char mk_Ermac[] PROGMEM = "Ermac";
const char mk_ErronBlack[] PROGMEM = "Erron Black";
const char mk_FerraTorr[] PROGMEM = "Ferra/Torr";
const char mk_Goro[] PROGMEM = "Goro";
const char mk_JacquiBriggs[] PROGMEM = "Jacqui Briggs";
const char mk_Jason[] PROGMEM = "Jason";
const char mk_Jax[] PROGMEM = "Jax";
const char mk_JohnnyCage[] PROGMEM = "Johnny Cage";
const char mk_Kano[] PROGMEM = "Kano";
const char mk_Kenshi[] PROGMEM = "Kenshi";
const char mk_Kitana[] PROGMEM = "Kitana";
const char mk_KotalKahn[] PROGMEM = "Kotal Kahn";
const char mk_KungJin[] PROGMEM = "Kung Jin";
const char mk_KungLao[] PROGMEM = "Kung Lao";
const char mk_Leatherface[] PROGMEM = "Leatherface";
const char mk_LiuKang[] PROGMEM = "Liu Kang";
const char mk_Mileena[] PROGMEM = "Mileena";
const char mk_Predator[] PROGMEM = "Predator";
const char mk_QuanChi[] PROGMEM = "Quan Chi";
const char mk_Raiden[] PROGMEM = "Raiden";
const char mk_Reptile[] PROGMEM = "Reptile";
const char mk_Scorpion[] PROGMEM = "Scorpion";
const char mk_Shinnok[] PROGMEM = "Shinnok";
const char mk_Sonya[] PROGMEM = "Sonya";
const char mk_SubZero[] PROGMEM = "Sub-Zero";
const char mk_Takeda[] PROGMEM = "Takeda";
const char mk_Tanya[] PROGMEM = "Tanya";
const char mk_Tremor[] PROGMEM = "Tremor";
const char mk_Triborg[] PROGMEM = "Triborg";

const char *const mortal_kombat[] PROGMEM = {
    mk_Alien,
    mk_BoRaiCho,
    mk_CassieCage,
    mk_DVorah,
    mk_Ermac,
    mk_ErronBlack,
    mk_FerraTorr,
    mk_Goro,
    mk_JacquiBriggs,
    mk_Jason,
    mk_Jax,
    mk_JohnnyCage,
    mk_Kano,
    mk_Kenshi,
    mk_Kitana,
    mk_KotalKahn,
    mk_KungJin,
    mk_KungLao,
    mk_Leatherface,
    mk_LiuKang,
    mk_Mileena,
    mk_Predator,
    mk_QuanChi,
    mk_Raiden,
    mk_Reptile,
    mk_Scorpion,
    mk_Shinnok,
    mk_Sonya,
    mk_SubZero,
    mk_Takeda,
    mk_Tanya,
    mk_Tremor,
    mk_Triborg,
};

#define n_mortal_kombat (sizeof(mortal_kombat) / sizeof(const char *))

#endif // MORTAL_KOMBAT_H
