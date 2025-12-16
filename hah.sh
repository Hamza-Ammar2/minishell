#!/bin/sh

cat < < (
  echo "from pipe"
  cat << EOF
from heredoc
EOF
)
