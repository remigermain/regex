# Regular expression WIP


## Prototype
### ft_regex_cmp
> Compare s1 to reg's pattern
```
int	ft_regex_cmp(t_regex *st, char *s1, char *reg)
```

*  return 0 if si not match
*  return positive integer for number that match
*  return -1 for error allocation memory
*  t_regex the struct with all information
*  s1 is your string
*  reg is your regex pattern


### ft_regex_replace
> Compare s1 to reg's pattern and replace all capturing string with rep's string

```
char	*ft_regex_replace(char *s1, char *reg, char *rep, enum e_regex_replace mod)
```
*  return NULL ptr if error in allocation memory
*  s1 is your string
*  reg is your regex pattern
*  rep is for replace string
*  enum is for mod 

| mod | Description |
|-----|-------------|
| REG_FIRST| Replace first pattern matching|
| REG_LAST| Replace last pattern matching|
|REG_ALL| Replace all pattern matching|

### ft_regex_free
> You need to be free the structure after matching

```
void	ft_regex_free(t_regex *st)
```
*  free t_regex struct

## REGEX

### Class

|   exemple     |      Description                                    |
|---------------|-----------------------------------------------------|
| [] 	        |   nothings                              |       
| [0] 	        |   The character "0"                                 |     
| [0-9] 	    |   Any number                                        |   
| [[:isdigit:]] |   Any number                                        |  
| [\d]          |   Any number                                        |  
| [^0-9] 	    |   Any character other than a number                 |       
| [^[:isdigit:]]|   Any character other than a number                 |   
| [^\d]|   Any character other than a number                 |   
| [-0-9] 	    |   Any number or a "-"                               |       
| [0-9-] 	    |   Any number or a "-"                               |       
| [^-0-9] 	    |   Any character except a number or a "-"            |                          
| []0-9] 	    |   Any number or a "]"                               |       
| [0-9]] 	    |   Any number followed by a "]"                      |                
| [0-9-z] 	    |   Any number, or any a "-", or "z". |                                     
| [0-9\\-a\\]]    |   Any number, or a "-", a "a", or a "]"             |            

#### Character class 


|POSIX       |    Non standard |   perl    |       Description                                  |
|------------|-----------------|-----------|----------------------------------------------------|
|            |    [:word:]     |   \w      |    Alphanumeric characters plus "_"                |
|            |                 |   \W      |    Non-word characters                             |    
|            |    [:ascii:]    |           |    ASCII characters                                |        
|[:alnum:]   |                 |           |    Alphanumeric characters                         |             
|[:alpha:]   |                 |           |    Alphabetic characters                           |           
|[:blank:]   |                 |           |    Space and tab                                   |   
|[:cntrl:]   |                 |           |    Control characters                              |       
|[:digit:]   |                 |   \d      |    Control characters                              |       
|            |                 |   \D      |    Non-digits                                      |
|[:graph:]   |                 |           |    Visible characters                              |        
|[:lower:]   |                 |           |    Lowercase letters                               |       
|[:print:]   |                 |           |    Visible characters and the space character      |                                
|[:punct:]   |                 |           |    Punctuation characters                          |            
|[:space:]   |                 |   \s      |    Whitespace characters                           |          
|            |                 |   \S      |    Non-whitespace characters                       |               
|[:upper:]   |                 |           |    Uppercase letters                               |       
|[:xdigit:]  |                 |           |    Uppercase letters                               |     

### Quantifier
>  By default , quantifier as ``Greedy`` means match longest possible string . The ``lazy`` mode of quantifiers is an opposite to the ``greedy`` mode. It means: “repeat minimal number of times”.
If you need ``lazy`` quantifier , add ``?`` at the end of quantifier

| quantifier | lazy |Description  |
|----------|-|--------------|
|  ?   |??    | Matches the preceding element zero or one time. For example, ab?c matches only "ac" or "abc".  |
|  +   |+?    | Matches the preceding element one or more times. For example, ab+c matches "abc", "abbc", "abbbc", and so on, but not "ac". |
|  \*   |\*?   | Matches the preceding element zero or more times. For example, ab*c matches "abc", "abbc", "ac"|
| {m,n}  |{m,n}?  |  Matches the preceding element at least m and not more than n times. For example, a{3,5} matches only "aaa", "aaaa", and "aaaaa". This is not found in a few older instances of regexes. BRE mode requires \{m,n\}. |
| {,n}   |{,n}?  |  Matches the preceding element zero or n time|
| {m,}    |{m,}? |  Matches the preceding element at least m time or more |
| {m;n}    |{m;n}?|  Matches the preceding element m time or n time |
| {m}      |-|  Matches the preceding element m time|


### Sepcial

| metachar |  Description  |
|----------|---------------|
| ^  | Matches the starting position within the string. In line-based tools, it matches the starting position of any line. |
| \|   |  The choice (also known as alternation or set union) operator matches either the expression before or the expression after the operator. For example, abc\|def matches "abc" or "def". |
| . | Matches any single character (many applications exclude newlines, and exactly which characters are considered newlines is flavor-, character-encoding-, and platform-specific, but it is safe to assume that the line feed character is included). Within POSIX bracket expressions, the dot character matches a literal dot. For example, a.c matches "abc", etc., but [a.c] matches only "a", ".", or "c". |
| $ | Matches the ending position of the string or the position just before a string-ending newline. In line-based tools, it matches the ending position of any line. |
| \n | newline|
| \t | tab |
| \r | return |
| \e | escape |
| \0x44 | hex ascii code|
| \0777 | octal ascii code |

### Enclose

| metachar |  Description  |
|----------|---------------|
| ( )     | Defines a marked subexpression. The string matched within the parentheses can be recalled later (see the next entry, \n). A marked subexpression is also called a block or capturing group. BRE mode requires \( \). |
