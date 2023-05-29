# echo "Enter String for Upper Case : "
# a = $(awk 'BEGIN { 

#     getline str;
#     print toUpper(str);

# }')

# echo "To Upper : "
# echo $a;

#!/bin/bash

echo "Enter a string:"
read string

# Convert string to uppercase
uppercase_string=$(echo "$string" | tr '[:lower:]' '[:upper:]')

echo "Uppercase string: $uppercase_string"
