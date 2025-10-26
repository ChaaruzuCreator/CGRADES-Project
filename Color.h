#ifndef COLOR_H
#define COLOR_H

#define HAGGANGDITO "\x1b[0m" // Reset to default

// Regular Colors
#define BLK "\x1b[0;30m"
#define RED "\x1b[0;31m"
#define GRN "\x1b[0;32m"
#define YEL "\x1b[0;33m"
#define BLU "\x1b[0;34m"
#define MAG "\x1b[0;35m"
#define CYN "\x1b[0;36m"
#define WHT "\x1b[0;37m"

// Bold Colors
#define BBLK "\x1b[1;30m"  // Bold Black
#define BRED "\x1b[1;31m"  // Bold Red
#define BGRN "\x1b[1;32m"  // Bold Green
#define BYEL "\x1b[1;33m"  // Bold Yellow
#define BBLU "\x1b[1;34m"  // Bold Blue
#define BMAG "\x1b[1;35m"  // Bold Magenta
#define BCYN "\x1b[1;36m"  // Bold Cyan
#define BWHT "\x1b[1;37m"  // Bold White

// Underline Colors
#define UBLK "\x1b[4;30m"  // Underline Black
#define URED "\x1b[4;31m"  // Underline Red
#define UGRN "\x1b[4;32m"  // Underline Green
#define UYEL "\x1b[4;33m"  // Underline Yellow
#define UBLU "\x1b[4;34m"  // Underline Blue
#define UMAG "\x1b[4;35m"  // Underline Magenta
#define UCYN "\x1b[4;36m"  // Underline Cyan
#define UWHT "\x1b[4;37m"  // Underline White

// Background Colors
#define BLKB "\x1b[40m"  // Black Background
#define REDB "\x1b[41m"  // Red Background
#define GRNB "\x1b[42m"  // Green Background
#define YELB "\x1b[43m"  // Yellow Background
#define BLUB "\x1b[44m"  // Blue Background
#define MAGB "\x1b[45m"  // Magenta Background
#define CYNB "\x1b[46m"  // Cyan Background
#define WHTB "\x1b[47m"  // White Background

// High Intensity Background Colors
#define BLKHB "\x1b[0;100m"  // Black High Intensity Background
#define REDHB "\x1b[0;101m"  // Red High Intensity Background
#define GRNHB "\x1b[0;102m"  // Green High Intensity Background
#define YELHB "\x1b[0;103m"  // Yellow High Intensity Background
#define BLUHB "\x1b[0;104m"  // Blue High Intensity Background
#define MAGHB "\x1b[0;105m"  // Magenta High Intensity Background
#define CYNHB "\x1b[0;106m"  // Cyan High Intensity Background
#define WHTHB "\x1b[0;107m"  // White High Intensity Background

// High Intensity Colors
#define HBLK "\x1b[0;90m"  // High Intensity Black (Gray)
#define HRED "\x1b[0;91m"  // High Intensity Red
#define HGRN "\x1b[0;92m"  // High Intensity Green
#define HYEL "\x1b[0;93m"  // High Intensity Yellow
#define HBLU "\x1b[0;94m"  // High Intensity Blue
#define HMAG "\x1b[0;95m"  // High Intensity Magenta
#define HCYN "\x1b[0;96m"  // High Intensity Cyan
#define HWHT "\x1b[0;97m"  // High Intensity White

// Bold High Intensity Colors
#define BHBLK "\x1b[1;90m"  // Bold High Intensity Black (Gray)
#define BHRED "\x1b[1;91m"  // Bold High Intensity Red
#define BHGRN "\x1b[1;92m"  // Bold High Intensity Green
#define BHYEL "\x1b[1;93m"  // Bold High Intensity Yellow
#define BHBLU "\x1b[1;94m"  // Bold High Intensity Blue
#define BHMAG "\x1b[1;95m"  // Bold High Intensity Magenta
#define BHCYN "\x1b[1;96m"  // Bold High Intensity Cyan
#define BHWHT "\x1b[1;97m"  // Bold High Intensity White

#include <stdio.h>
#include <windows.h>

void enableANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

#endif

