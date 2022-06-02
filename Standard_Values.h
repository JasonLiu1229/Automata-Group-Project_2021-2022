#ifndef AUTOMATA_GROUP_PROJECT_2021_2022_STANDARD_VALUES_H
#define AUTOMATA_GROUP_PROJECT_2021_2022_STANDARD_VALUES_H

// Level layout text filenames
#define LEV1TXT                    "Level1.txt"
#define LEV2TXT                    "Level2.txt"
#define LEV3TXT                    "Level3.txt"
#define LEV4TXT                    "Level4.txt"
#define LEV5TXT                    "Level5.txt"

// Level layout json filenames
#define LEV1JSON                   "Level1.json"
#define LEV2JSON                   "Level2.json"
#define LEV3JSON                   "Level3.json"
#define LEV4JSON                   "Level4.json"
#define LEV5JSON                   "Level5.json"

enum tileSettings {path, wall};
enum gameStatus {play, pause};
enum movement {UP, DOWN, LEFT, RIGHT, IDLE};

#define SVG1                        "../SavedGames/"
#define TXT                        ".txt"
#define JSON                       ".json"

// Working directories
#define LEVDIR                     "../TXT-Files/"

#endif //AUTOMATA_GROUP_PROJECT_2021_2022_STANDARD_VALUES_H