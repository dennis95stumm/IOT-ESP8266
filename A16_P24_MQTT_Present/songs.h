//#include "pitches.h"
//Songs SOUCE: https://github.com/rmadhuram/ArduinoChristmasTunes/blob/master/christmas_tunes/christmas_tunes.ino
typedef struct {
  const int *melody;
  const byte *durations;
  int numCount;
  int tempo;
  int low, high;
} tune;

tune tunes[6];


// AWe Wish You a Merry Christmas
PROGMEM const int  weWish[] = {
  N_D5, N_G5, N_G5, N_A5, N_G5, N_FS5,
  N_E5, N_C5, N_E5, N_A5, N_A5, N_B5, N_A5,
  N_G5, N_FS5, N_D5, N_FS5, N_B5, N_B5,
  N_C6, N_B5, N_A5, N_G5, N_E5, N_D5,
  N_D5, N_E5, N_A5, N_FS5, N_G5,
};


const byte PROGMEM weWishDurations[] = {4, 4, 2, 2, 2, 2,
                                           4, 4, 4, 4, 2, 2, 2,
                                           2, 4, 4, 4, 4, 2,
                                           2, 2, 2, 4, 4, 2,
                                           2, 4, 4, 4, 8, 8
                                          };


// Alle Jahre wieder
PROGMEM const int  alleJahre[] = {
  N_G5, N_A5, N_G5, N_F5, N_E5, N_D5, N_C5, N_D5, N_E5, N_F5, N_E5, N_D5, N_REST,
  N_E5, N_G5, N_A5, N_F5, N_C6, N_B5, N_A5, N_G5, N_F5, N_E5, N_F5, N_G5, N_E5, N_REST
};

const byte PROGMEM alleJahreDurations[] = {6, 2, 4, 4, 8, 8, 4, 2, 2, 4, 4, 8, 4, 4,
                                           4, 4, 4, 8, 4, 4, 4, 2, 2, 4, 4, 8, 4
                                          };

// Jingle Bells
PROGMEM const int  jingleBells[] = { N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_G5, N_C5, N_D5, N_E5,
                                     N_F5, N_F5, N_F5, N_F5, N_F5, N_E5, N_E5, N_E5, N_E5, N_D5, N_D5, N_E5, N_D5, N_G5,
                                     N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_G5, N_C5, N_D5, N_E5,
                                     N_F5, N_F5, N_F5, N_F5, N_F5, N_E5, N_E5, N_E5, N_G5, N_G5, N_F5, N_D5, N_C5
                                   };
const byte PROGMEM jingleBellsDurations[] = { 4, 4, 8, 4, 4, 8, 4, 4, 4, 4, 16,
                                              4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8, 8,
                                              4, 4, 8, 4, 4, 8, 4, 4, 4, 4, 16,
                                              4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 16
                                            };

// The first noel
// http://www.music-for-music-teachers.com/support-files/first-noel-broken-chord-stretch-key-of-c.pdf

const int PROGMEM firstNoel[] = { N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4,
                                  N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, N_F4,
                                  N_E4, N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4,
                                  N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, N_F4,
                                  N_E4, N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, N_G4, N_C5, N_B4, N_A4, N_A4,
                                  N_G4, N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, N_F4, N_E4
                                };

const byte PROGMEM firstNoelDurations[] = { 2, 2, 6, 2, 2, 2, 8, 2, 2, 4, 4, 4,
                                            8, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                                            8, 2, 2, 6, 2, 2, 2, 8, 2, 2, 4, 4, 4,
                                            8, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                                            8, 2, 2, 6, 2, 2, 2, 8, 2, 2, 8, 4,
                                            12, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8
                                          };

// O Holy Night
// http://www.music-for-music-teachers.com/support-files/o-holy-night-lead-sheet-c.pdf

const int PROGMEM oHolyNight[] = { N_E4, N_E4, N_E4, N_G4, N_REST, N_G4, N_A4, N_A4, N_F4, N_A4, N_C5,
                                   N_G4, N_G4, N_E4, N_D4, N_C4, N_E4, N_F4, N_G4, N_F4, N_D4, N_C4,
                                   N_E4, N_E4, N_E4, N_G4, N_REST, N_G4, N_A4, N_A4, N_F4, N_A4, N_C5,
                                   N_G4, N_G4, N_FS4, N_E4, N_B4, N_G4, N_A4, N_B4, N_C5, N_B4, N_E4, N_REST, N_G4,
                                   N_G4, N_A4, N_D4, N_G4, N_A4, N_G4, N_C5, N_E4, N_A4, N_G4, N_G4, N_G4, N_A4,
                                   N_D4, N_G4, N_A4, N_G4, N_C5, N_E4, N_G4, N_C5, N_C5, N_B4, N_A4,
                                   N_B4, N_A4, N_REST, N_A4, N_D5, N_D5, N_A4, N_A4, N_A4, N_C5,
                                   N_C5, N_REST, N_C5, N_E5, N_D5, N_D5, N_G4, N_C5, N_C5, N_B4, N_A4,
                                   N_G4, N_G4, N_G4, N_A4, N_G4, N_G4, N_G4, N_C5, N_D5,
                                   N_D5, N_G4, N_E5, N_E5, N_D5, N_C5, N_B4, N_C5, N_D5,
                                   N_C5
                                 };

const byte PROGMEM oHolyNightDurations[] = { 6, 4, 2, 8, 2, 2 , 4, 2, 4, 2, 12,
                                             4, 2, 4, 2, 6, 4, 2, 6, 4, 2, 24,
                                             6, 4, 2, 8, 2, 2 , 4, 2, 4, 2, 12,
                                             4, 2, 4, 2, 6, 4, 2, 6, 4, 2, 20, 2, 2,
                                             6, 6, 6, 6, 4, 2, 4, 2, 6, 4, 2, 6, 6,
                                             6, 6, 4, 2, 4, 2, 12, 12, 6, 4, 2,
                                             12, 8, 2, 2, 12, 4, 2, 4, 2, 12,
                                             8, 2, 2, 12, 8, 2, 2, 12, 6, 4, 2,
                                             12, 4, 2, 4, 2, 12, 6, 6, 12,
                                             6, 6, 12, 6, 6, 12, 6, 4, 2,
                                             24
                                           };

// http://www.christmas-carol-music.org/Lead_Sheets/WeThreeKings.html

const int PROGMEM weThreeKings[] = { N_B4, N_A4, N_G4, N_E4, N_FS4, N_G4, N_FS4, N_E4,
                                     N_B4, N_A4, N_G4, N_E4, N_FS4, N_G4, N_FS4, N_E4,
                                     N_G4, N_G4, N_G4, N_A4, N_A4, N_B4, N_B4, N_D5, N_C5, N_B4,
                                     N_A4, N_B4, N_A4, N_G4, N_FS4, N_E4,
                                     N_FS4, N_A4, N_G4, N_G4, N_G4, N_D4, N_G4, N_E4, N_G4, N_G4, N_G4, N_G4, N_D4, N_G4, N_E4, N_G4,
                                     N_G4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_B4, N_G4, N_G4, N_G4, N_D4, N_G4, N_E4, N_G4
                                   };

const byte PROGMEM weThreeKingsDurations[] = { 4, 2, 4, 2, 2, 2, 2, 6,
                                               4, 2, 4, 2, 2, 2, 2, 6,
                                               2, 2, 2, 4, 2, 4, 2, 2, 2, 2,
                                               2, 2, 2, 4, 2, 6,
                                               6, 6, 4, 2, 4, 2, 4, 2, 6, 4, 2, 4, 2, 4, 2, 6,
                                               4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 6
                                             };

// What child is this
// http://www.free-scores.com/PDF_EN/traditional-what-child-is-this-39593.pdf

const int PROGMEM whatChild[] = { N_E4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_E4, N_E4, N_DS4, N_E4, N_FS4, N_B3, N_REST,  N_E4,
                                  N_G4, N_A4, N_B4, N_C4, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_FS4, N_E4, N_DS4, N_CS4, N_D4, N_E4, N_E4, N_REST,
                                  N_D5, N_D5, N_C5, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_E4, N_E4, N_DS4, N_E4, N_FS4, N_DS4, N_B3, N_REST,
                                  N_D5, N_D5, N_C5, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_FS4, N_E4, N_DS4, N_CS4, N_D4, N_E4, N_E4
                                } ;

const byte PROGMEM whatChildDurations[] = { 2, 4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 6, 2, 2, 2,
                                            4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 6, 4, 2,
                                            6, 3, 1, 2, 4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 4, 2, 4, 2,
                                            6, 3, 1, 2, 4, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 6, 4
                                          };
