
#ifndef ALPHABET_H
#define ALPHABET_H


/*** defines ***/

#define DEFAULT_ALPHABET " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ"


/*** init ***/

extern void charset_init(char *charset);


/*** getters ***/

extern int get_alphabet_length(void);
extern char get_next_char(unsigned char c);


/*** methods ***/

extern int is_alphabet(unsigned char c);
extern int str_is_alphabet(char *str);

extern int get_word_dist(const char* str1, const char* str2);


#endif
