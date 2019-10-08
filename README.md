# Regular expression WIP

## [1] is working

### Class

|   exemple     |      Descriotion                                    |
|---------------|-----------------------------------------------------|
| [] 	        |   The characters "[]"                               |       
| [0] 	        |   The character "0"                                 |     
| [0-9] 	    |   Any number                                        |   
| [^0-9] 	    |   Any character other than a number                 |                     
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
