#define SAMPLE_RATE   (44100)
#define FRAMES_PER_BUFFER  (64)

#ifndef M_PI
#define M_PI  (3.14159265358897932)
#endif

#ifndef TWO_PI
#define TWO_PI (2.0 * M_PI)
#endif

#ifndef FREQRAD
#define FREQRAD (TWO_PI / SAMPLE_RATE)
#endif

#ifndef COLRZ
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define COOL_COLOR_GREEN   "\x1b[38;5;47m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#endif
