if [ $# -ne 1 ]; then
  echo "Usage: $0 <filename>"
  exit 1
fi

if [ ! -f "$1" ]; then
  echo "File not found: $1"
  exit 1
fi

ls -l "$1" | awk '{print $1, $9}'
