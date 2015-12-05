#include <iostream>
#include <termios.h>
#include <string.h>
//#include <ncurses.h>

void interpret(std::string str);

int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main()
{
    int c;

    std::cout << "Starting up.." << std::endl;

    while (1) {
        std::cout << "#> ";
        std::string input_line;
        //c = getch();

        do {
            c = getch();
            if ( c == 27 ) { // ESC
                getch();
                switch(getch()) {// THIS IS THE REAL BATTLES // injoke with Keung and Matr77
                    case 65:
                        printf("UP\n");
                        break;
                    case 66:
                        printf("DOWN\n");
                        break;
                    case 67:
                        printf("RIGHT\n");
                        break;
                    case 68:
                        printf("LEFT\n");
                        break;
                    default:
                        break;
                }
            }

            if ( c == 4 ) {
                printf("\nLater, l0ser...\n");
                exit(EXIT_SUCCESS);
            } else {
                std::cout << (char)c;
                input_line += c;
            }
        } while ( c != '\n');

        interpret(input_line);
    }
}

void interpret(std::string str)
{
    if (str.length() != 0)
        std::cout << "FInal string : " << str << std::endl;
    else 
        std::cout << std::endl;
}

