# Regular expression WIP

## [1] is working

### Class

|   exemple     |      Descriotion                                    |
|---------------|-----------------------------------------------------|
| [] 	        |   The characters "[]"                               |       
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
| [0-9-z] 	    |   Any number, or any character between "9" and "z". |                                     
| [0-9\-a\]]    |   Any number, or a "-", a "a", or a "]"             |            

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

### quantifier

| metachar |  Description  |
|----------|---------------|
|  ?       | Matches the preceding element zero or one time. For example, ab?c matches only "ac" or "abc".  |
|  +      |Matches the preceding element one or more times. For example, ab+c matches "abc", "abbc", "abbbc", and so on, but not "ac". |
|  \*     | Matches the preceding element zero or more times. For example, ab*c matches "abc", "abbc", "ac"|
| {m,n}      |  Matches the preceding element at least m and not more than n times. For example, a{3,5} matches only "aaa", "aaaa", and "aaaaa". This is not found in a few older instances of regexes. BRE mode requires \{m,n\}. |
| {,n} |  Matches the preceding element zero or n time|
| {m,} |  Matches the preceding element at least m time or more |
 {m;n} |  Matches the preceding element m time or n time |

### sepcial

| metachar |  Description  |
|----------|---------------|
| ^  | Matches the starting position within the string. In line-based tools, it matches the starting position of any line. |
| . | Matches any single character (many applications exclude newlines, and exactly which characters are considered newlines is flavor-, character-encoding-, and platform-specific, but it is safe to assume that the line feed character is included). Within POSIX bracket expressions, the dot character matches a literal dot. For example, a.c matches "abc", etc., but [a.c] matches only "a", ".", or "c". |
| $ | Matches the ending position of the string or the position just before a string-ending newline. In line-based tools, it matches the ending position of any line. |