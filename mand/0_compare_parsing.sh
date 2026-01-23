# **************************************************************************** #
#                                COMPARE PARSING                               #
# **************************************************************************** #

### comparing your input parsing to bash ###

#Test Number 1 input
/bin/echo ""$?""

#Test Number 2 input
/bin/echo $?"42"

#Test Number 3 input
/bin/echo ''$?''"42"

#Test Number 4 input
/bin/echo '"$USER"'

#Test Number 5 input
/bin/echo "'$USER'"

#Test Number 6 input
/bin/echo ""'$USER'""

#Test Number 7 input
/bin/echo '"'$USER'"'

#Test Number 8 input
/bin/echo "''$USER''"

#Test Number 9 input
/bin/echo "'"'$USER'"'"

#Test Number 10 input
/bin/echo '"'"$USER"'"'

#Test Number 11 input
/bin/echo $"HOME"$USER

#Test Number 12 input
/bin/echo $"HOM"E$USER

#Test Number 13 input
/bin/echo "exit_code ->$? user ->$USER home -> $HOME"

#Test Number 14 input
/bin/echo $"HOME"

#Test Number 15 input
/bin/echo $"42$"

#Test Number 16 input
/bin/echo "$ "

#Test Number 17 input
/bin/echo hi >./outfiles/outfile01 | /bin/echo bye

#Test Number 18 input
/bin/echo <123 <456 hi | /bin/echo 42

#Test Number 19 input
/bin/echo '$='

#Test Number 20 input
/bin/echo '$ '

#Test Number 21 input
/bin/echo "$?"

#Test Number 22 input
/bin/echo '$?'

#Test Number 23 input
/bin/echo "'$?'"

#Test Number 24 input
/bin/echo \$USER

#Test Number 25 input
/bin/echo \\$USER

#Test Number 26 input
/bin/echo \\\$USER

#Test Number 27 input
/bin/echo \\\\$USER

#Test Number 28 input
/bin/echo \\\\\$USER

#Test Number 29 input
/bin/echo \\\\\\\\\$USER

#Test Number 30 input
/bin/echo \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\$USER \$PATH \\$PWD

#Test Number 31 input
/bin/echo "cat lol.c | cat > lol.c"

#Test Number 32 input
/bin/echo "cat lol.c '|' cat > lol.c"

#Test Number 33 input
/bin/echo '$USER' "$USER" "text  ' text"

#Test Number 34 input
/bin/echo $USER =intergalaktikus miaf*szomez

#Test Number 35 input
/bin/echo -n"-n" bonjour

#Test Number 36 input
/bin/echo "'$USER'"

#Test Number 37 input
/bin/echo " '$USER' "

#Test Number 38 input
/bin/echo text"$USER"

#Test Number 39 input
/bin/echo text"'$USER'" ' $USER '

#Test Number 40 input
/bin/echo "text"   "$USER"    "$USER"

#Test Number 41 input
/bin/echo '              $USER          '

#Test Number 42 input
/bin/echo ''''''''''$USER''''''''''

#Test Number 43 input
/bin/echo """"""""$USER""""""""

#Test Number 44 input
/bin/echo '""""""""$USER""""""""'

#Test Number 45 input
/bin/echo ""'""""""$USER""""""'""

#Test Number 46 input
/bin/echo """"""""'$USER'""""""""

#Test Number 47 input
/bin/echo """""""'"$USER"'"""""""

#Test Number 48 input
/bin/echo """"""'""$USER""'""""""

#Test Number 49 input
/bin/echo ""'""'""""$USER""""'""'""

#Test Number 50 input
/bin/echo '""'""'""""$USER""""'""'""'

#Test Number 51 input
/bin/echo $USER'$USER'text oui oui     oui  oui $USER oui      $USER ''

#Test Number 52 input
/bin/echo "text" "text$USER" ... "$USER"

#Test Number 53 input
/bin/echo

#Test Number 54 input
/bin/echo ''

#Test Number 55 input
/bin/echo ""

#Test Number 56 input
/bin/echo '' ""

#Test Number 57 input
/bin/echo /bin/echo

#Test Number 58 input
/bin/echo test1

#Test Number 59 input
/bin/echo 'test1'

#Test Number 60 input
/bin/echo "/bin/echo hallo"

#Test Number 61 input
/bin/echo /bin/echo"1"

#Test Number 62 input
/bin/echo "test1 test2"

#Test Number 63 input
/bin/echo "test1  test2" test3

#Test Number 64 input
/bin/echo " test1 test2 " 'test3 '

#Test Number 65 input
/bin/echo test1		test2

#Test Number 66 input
/bin/echo $USER$TESTNOTFOUND$HOME$

#Test Number 67 input
/bin/echo $USER$TESTNOTFOUND$HOME$WTF$PWD

#Test Number 68 input
/bin/echo -n test1

#Test Number 69 input
/bin/echo -n "test1 test2"

#Test Number 70 input
/bin/echo -n "test1 test2" test3

#Test Number 71 input
/bin/echo -n " test1 test2 " 'test3 '

#Test Number 72 input
/bin/echo -n test1		test2

#Test Number 73 input
/bin/echo test1 -n

#Test Number 74 input
/bin/echo "test1 -n"

#Test Number 75 input
/bin/echo -n -n test1

#Test Number 76 input
/bin/echo -n -n -n -n -n test1

#Test Number 77 input
/bin/echo "  -nn "

#Test Number 78 input
/bin/echo "-n test1 -n test2"

#Test Number 79 input
/bin/echo "test1 -n test2"

#Test Number 80 input
/bin/echo ~42

#Test Number 81 input
/bin/echo -n -n -nasd

#Test Number 82 input
/bin/echo -n -n -n-nnnnn

#Test Number 83 input
/bin/echo -n -nnnnnnn -n -nnn -nnnnn -n-n

#Test Number 84 input
/bin/echo -n -nnnnnnn -n -nnn -nnnnn -n feel my pain

#Test Number 85 input
/bin/echo -n -n -n-n

#Test Number 86 input
/bin/echo "'totally logical'"

#Test Number 87 input
/bin/echo 'totally logical'

#Test Number 88 input
/bin/echo ''totally logical''

#Test Number 89 input
/bin/echo ""'totally logical'""