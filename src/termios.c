//#include "minishell.h"

#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/select.h>
#include <sys/ioctl.h>

#define ESC          27
#define INSERT       50
#define DELETE       51
#define ARROWRIGHT   67
#define ARROWLEFT    68
#define END          70
#define HOME         72
#define OTHER        79
#define BRACKETLEFT  91
#define TILDE       126
#define BACKSPACE   127

#define SIZE         30

static const int STDIN = 0;

int kbhit(void)
{
	int bytesWaiting;

	ioctl(STDIN, FIONREAD, &bytesWaiting);
	return bytesWaiting;
}
//
//int main ( ) {
//	char input[SIZE] = {'\0'};
//	int insert = 0;
//	int each = 0;
//	int end = 0;
//	int to = 0;
//	int ch = 0;
//	int row = 0;
//	int col = 0;
//	struct termios oldattr, newattr;
//
//	//set terminal
//	tcgetattr( STDIN, &oldattr );
//	newattr = oldattr;
//	newattr.c_lflag &= ~( ICANON | ECHO );
//	tcsetattr( STDIN, TCSANOW, &newattr );
//	setbuf(stdin, NULL);
//
//	clear();
////	printf ( "\033[2J");//clear screen
////	printf ( "\033[25;1H");//move cursor to row 25 col 1
////	printf ( "OVW");
////	printf ( "\033[9;1H");//move cursor to row 9 col 1
//	printf ( "enter your text ");//prompt
////	//printf ( "%s", input);
////	printf ( "\033[9;17H");//move cursor to row 9 col 17
////	col = 17;
////	row = 9;
//	while ( ( ch = getchar ()) != '\n') {
//		if ( isprint( ch)) {
//			if ( insert && each < end && end < SIZE-3) {
//				//expand
//				end++;
//				for ( to = end; to >= each; to--) {
//					input[to + 1] = input[to];
//				}
////				printf ( "\033[9;17H");//move cursor to row 9 col 12
//				printf ( "\033[K");//erase to end of line
//				printf ( "%s", input);
//			}
////			printf ( "\033[%d;%dH", row, col);
//			printf ( "%c", ch);
//			input[each] = ch;
//			each++;
//			if ( each > end) {
//				end = each;
//			}
//			col++;
//			if ( each == end) {
//				input[each] = '\0';
//			}
//			if ( each >= SIZE-1) {
//				break;
//			}
//			continue;
//		}
//
//		if ( ch == ESC) {
//			if ( !kbhit ( )) {
//				continue;
//			}
//			ch = getchar ( );
//			if ( ch == OTHER) {
//				ch = getchar ( );
//				if ( ch == HOME) {
//					col -= each;
//					each = 0;
//					printf ( "\033[%d;%dH", row, col);
//					ch = getchar ( );
//				}
//				if ( ch == END) {
//					col += end - each;
//					each = end;
//					printf ( "\033[%d;%dH", row, col);
//					ch = getchar ( );
//				}
//			}
//			if ( ch == BRACKETLEFT) {
//				ch = getchar ( );
//				if ( ch == INSERT) {
//					ch = getchar ( );
//					if ( ch == TILDE) {
//						insert = !insert;
//						printf ( "\033[25;1H");//move cursor to row 25 col 1
//						if ( insert) {
//							printf ( "INS");
//						}
//						else {
//							printf ( "OVW");
//						}
//						printf ( "\033[%d;%dH", row, col);
//					}
//				}
//				if ( ch == DELETE) {
//					ch = getchar ( );
//					if ( ch == TILDE) {
//						//contract
//						for ( to = each; to <= end; to++) {
//							input[to] = input[to + 1];
//						}
//						end--;
//						printf ( "\033[9;17H");//move cursor to row 10 col 1
//						printf ( "\033[K");//erase to end of line
//						printf ( "%s", input);
//						printf ( "\033[%d;%dH", row, col);
//					}
//				}
//				if ( ch == ARROWRIGHT) {
//					if ( each < end) {
//						printf ( "\033[C");//cursor right
//						each++;
//						col++;
//					}
//				}
//				if ( ch == ARROWLEFT) {
//					if ( each) {
//						printf ( "\033[D");//cursor left
//						each--;
//						col--;
//					}
//				}
//			}
//			else {
//				ungetc ( ch, stdin);
//			}
//		}
//	}
//	printf ( "\n\ninput was [%s]\n", input);
//	printf ( "\n\nbye\n");
//
//	//restore terminal
//	tcsetattr( STDIN, TCSANOW, &oldattr );
//
//	return 0;
//}