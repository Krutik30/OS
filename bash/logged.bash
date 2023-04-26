if [ $# -ne 1 ]; then
  echo "Usage: $0 <username>"
  exit 1
fi

if who | grep -wq "^$1"; then
  login_time=$(who | grep -w "^$1" | awk '{print $3, $4}')

  echo "$1 is currently logged in since $login_time"
else
  echo "$1 is not currently logged in"
fi
