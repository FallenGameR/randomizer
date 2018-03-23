#ifndef TEKKEN7_H
#define TEKKEN7_H

// Using PROGMEM here to save some spavce for variables

const char tekken7_Akuma[] PROGMEM = "Akuma";
const char tekken7_Alisa[] PROGMEM = "Alisa";
const char tekken7_AsukaKazama[] PROGMEM = "Asuka Kazama";
const char tekken7_Bob[] PROGMEM = "Bob";
const char tekken7_BryanFury[] PROGMEM = "Bryan Fury";
const char tekken7_ClaudioSerafino[] PROGMEM = "Claudio Serafino";
const char tekken7_DevilJin[] PROGMEM = "Devil Jin";
const char tekken7_EddyGordo[] PROGMEM = "Eddy Gordo";
const char tekken7_Eliza[] PROGMEM = "Eliza";
const char tekken7_FengWei[] PROGMEM = "Feng Wei";
const char tekken7_GeeseHoward[] PROGMEM = "Geese Howard";
const char tekken7_Gigas[] PROGMEM = "Gigas";
const char tekken7_HeihachiMishima[] PROGMEM = "Heihachi Mishima";
const char tekken7_Hwoarang[] PROGMEM = "Hwoarang";
const char tekken7_Jack7[] PROGMEM = "Jack-7";
const char tekken7_JinKazama[] PROGMEM = "Jin Kazama";
const char tekken7_JosieRizal[] PROGMEM = "Josie Rizal";
const char tekken7_KatarinaAlves[] PROGMEM = "Katarina Alves";
const char tekken7_KazumiMishima[] PROGMEM = "Kazumi Mishima";
const char tekken7_KazuyaMishima[] PROGMEM = "Kazuya Mishima";
const char tekken7_King[] PROGMEM = "King";
const char tekken7_Kuma[] PROGMEM = "Kuma";
const char tekken7_Lars[] PROGMEM = "Lars";
const char tekken7_LeeChaolan[] PROGMEM = "Lee Chaolan";
const char tekken7_Leo[] PROGMEM = "Leo";
const char tekken7_Lili[] PROGMEM = "Lili";
const char tekken7_LingXiaoyu[] PROGMEM = "Ling Xiaoyu";
const char tekken7_LuckyChloe[] PROGMEM = "Lucky Chloe";
const char tekken7_MarshallLaw[] PROGMEM = "Marshall Law";
const char tekken7_MasterRaven[] PROGMEM = "Master Raven";
const char tekken7_Miguel[] PROGMEM = "Miguel";
const char tekken7_NinaWilliams[] PROGMEM = "Nina Williams";
const char tekken7_NoctisLucis[] PROGMEM = "Noctis Lucis";
const char tekken7_Panda[] PROGMEM = "Panda";
const char tekken7_PaulPhoenix[] PROGMEM = "Paul Phoenix";
const char tekken7_Shaheen[] PROGMEM = "Shaheen";

const char *const tekken7[] PROGMEM = {
    tekken7_Akuma,
    tekken7_Alisa,
    tekken7_AsukaKazama,
    tekken7_Bob,
    tekken7_BryanFury,
    tekken7_ClaudioSerafino,
    tekken7_DevilJin,
    tekken7_EddyGordo,
    tekken7_Eliza,
    tekken7_FengWei,
    tekken7_GeeseHoward,
    tekken7_Gigas,
    tekken7_HeihachiMishima, // The longest name that fit LCD
    tekken7_Hwoarang,
    tekken7_Jack7,
    tekken7_JinKazama,
    tekken7_JosieRizal,
    tekken7_KatarinaAlves,
    tekken7_KazumiMishima, // Tiger girl
    tekken7_KazuyaMishima,
    tekken7_King,
    tekken7_Kuma,
    tekken7_Lars,
    tekken7_LeeChaolan,
    tekken7_Leo,
    tekken7_Lili,
    tekken7_LingXiaoyu,
    tekken7_LuckyChloe,
    tekken7_MarshallLaw,
    tekken7_MasterRaven,
    tekken7_Miguel,
    tekken7_NinaWilliams,
    tekken7_NoctisLucis,
    tekken7_Panda,
    tekken7_PaulPhoenix,
    tekken7_Shaheen,
};

#define n_tekken7 (sizeof(tekken7) / sizeof(const char *))

#endif // TEKKEN7_H
