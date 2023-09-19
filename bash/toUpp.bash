# # echo "Enter String for Upper Case : "
# # a = $(awk 'BEGIN { 

# #     getline str;
# #     print toUpper(str);

# # }')

# # echo "To Upper : "
# # echo $a;

# #!/bin/bash

# echo "Enter a string:"
# read string

# # Convert string to uppercase
# uppercase_string=$(echo "$string" | tr '[:lower:]' '[:upper:]')

# echo "Uppercase string: $uppercase_string"


#!/usr/bin/awk
# Returns Uppercased string
function find_uppercase(str){
 string = toupper(str)
 return string
}

function find_lowercase(str){
    string = tolower(str)
    return string;
}
# Main function
function main(stringg){

 #Find Uppercase of the string
 result = find_uppercase(stringg)
 print "Input string =", stringg
 print "Uppercased string =", result
}
# Script execution starts here
BEGIN {
 main("hi hello how do you do!”)
}