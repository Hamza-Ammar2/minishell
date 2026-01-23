# **************************************************************************** #
#                                  VARIABLES                                   #
# **************************************************************************** #

### SIMPLE VARS ###
#Test Number 1010 input
/bin/echo $?

#Test Number 1011 input
/bin/echo $HOME

#Test Number 1012 input
/bin/echo $HOME$USER

#Test Number 1013 input
/bin/echo $HOME$NOTHING$USER$

#Test Number 1014 input
export a="asd"

#Test Number 1015 input
export a="asd" b="de" o= c="hellomi" X

#Test Number 1016 input
export miert ne lehetne ezt is

#Test Number 1017 input
export a="asd"
#Test Number 1018 input
unset a

#Test Number 1019 input
export a="asd" b="de" o= c="hellomi" X
#Test Number 1020 input
unset o

#Test Number 1021 input
export a="asd" b="de" o= c="hellomi" X
#Test Number 1022 input
unset X

#Test Number 1023 input
export a="asd" b="de" o= c="hellomi" X
#Test Number 1024 input
unset o a X b c

#Test Number 1025 input
export a="asd" b="de" o= c="hellomi" X
#Test Number 1026 input
unset o asd B x X wqd c

#Test Number 1027 input
export T=a T=b T=c
#Test Number 1028 input
echo $T

#Test Number 1029 input
export miert ne lehetne ezt is

#Test Number 1030 input
/bin/echo $"HOME"$USER

#Test Number 1031 input
/bin/echo $"HOM"E$USER

#Test Number 1032 input
/bin/echo $"'HOM'E"$USER

#Test Number 1033 input
/bin/echo $'HOM'E$USER

#Test Number 1034 input
/bin/echo $"HOME"

#Test Number 1035 input
/bin/echo $'HOME'

#Test Number 1036 input
/bin/echo $

#Test Number 1037 input
/bin/echo "$"

#Test Number 1038 input
/bin/echo '$='

#Test Number 1039 input
/bin/echo "$""$"

#Test Number 1040 input
/bin/echo $"$"

#Test Number 1041 input
/bin/echo $"42$"

#Test Number 1042 input
/bin/echo "$"$

#Test Number 1043 input
/bin/echo $'$'

#Test Number 1044 input
/bin/echo '$'$

#Test Number 1045 input
/bin/echo "$ "

#Test Number 1046 input
/bin/echo '$ '

#Test Number 1047 input
/bin/echo $TESTNOTFOUND

#Test Number 1048 input
/bin/echo $HOME$TESTNOTFOUND

#Test Number 1049 input
/bin/echo $TESTNOTFOUND$HOME

#Test Number 1050 input
/bin/echo $TESTNOTFOUND$HOME$

#Test Number 1051 input
cd ..$PWD

#Test Number 1052 input
mkdir test
#Test Number 1053 input
cd $PWD/test
#Test Number 1054 input
cd..
#Test Number 1055 input
rm -rf test

#Test Number 1056 input
/bin/echo $PWD/random_folder

#Test Number 1057 input
/bin/echo ""$?""
#Test Number 1058 input
/bin/echo " "$?" "
#Test Number 1059 input
/bin/echo $?"42"
#Test Number 1060 input
/bin/echo ''$?''"42"
#Test Number 1061 input
/bin/echo 'HELLO'$?:''"42"

#Test Number 1062 input
/bin/echo "$?"
#Test Number 1063 input
/bin/echo '$?'
#Test Number 1064 input
/bin/echo "'$?'"
#Test Number 1065 input
/bin/echo '"$?"'

### UPDATE PWD ###
#Test Number 1066 input
mkdir "tmp_test_folder"
#Test Number 1067 input
/bin/echo $PWD
#Test Number 1068 input
cd "tmp_test_folder"
#Test Number 1069 input
/bin/echo $PWD
#Test Number 1070 input
cd ..
#Test Number 1071 input
/bin/echo $PWD
#Test Number 1072 input
rm -rf "tmp_test_folder"

#Test Number 1073 input
mkdir "tmp_test folder"
#Test Number 1074 input
/bin/echo $PWD
#Test Number 1075 input
cd "tmp_test folder"
#Test Number 1076 input
/bin/echo $PWD
#Test Number 1077 input
cd ..
#Test Number 1078 input
/bin/echo $PWD
#Test Number 1079 input
rm -rf "tmp_test folder"

### SCMD IN VARIABLE ###
#Test Number 1080 input
export tmp_test="/bin/echo 42"
#Test Number 1081 input
$tmp_test
#Test Number 1082 input
$tmp_test 42
#Test Number 1083 input
export tmp_test="/bin/echo"
#Test Number 1084 input
$tmp_test 42 42

#Test Number 1085 input
export tmp_test="/bin/echo 42"
#Test Number 1086 input
"tmp_test"

### VARIABLE SPLITTING ###
#Test Number 1087 input
export X="  A  B  "
#Test Number 1088 input
/bin/echo "1"$X'2'

#Test Number 1089 input
export X=" A  B  "
#Test Number 1090 input
/bin/echo "1"$X'2'

#Test Number 1091 input
export X="A  B  "
#Test Number 1092 input
/bin/echo "1"$X'2'

#Test Number 1093 input
export X="  A  B "
#Test Number 1094 input
/bin/echo "1"$X'2'

#Test Number 1095 input
export X="  A  B"
#Test Number 1096 input
/bin/echo "1"$X'2'

#Test Number 1097 input
export X="  A B  "
#Test Number 1098 input
/bin/echo "1"$X'2'

#Test Number 1099 input
export X="  AB  "
#Test Number 1100 input
/bin/echo "1"$X'2'

#Test Number 1101 input
export X="  A  B  "
#Test Number 1102 input
/bin/echo $X'2'

#Test Number 1103 input
export X="  A  B  "
#Test Number 1104 input
/bin/echo $X"1"

#Test Number 1105 input
export X=""
#Test Number 1106 input
/bin/echo "1"$X'2'

#Test Number 1107 input
export X=" "
#Test Number 1108 input
/bin/echo "1"$X'2'

#Test Number 1109 input
export X="   "
#Test Number 1110 input
/bin/echo "1"$X'2'

#Test Number 1111 input
export X="  A  B  "
#Test Number 1112 input
/bin/echo ?$X'2'

#Test Number 1113 input
export X="  A  B  "
#Test Number 1114 input
/bin/echo "1"$X?

#Test Number 1115 input
export X="  A  B  "
#Test Number 1116 input
/bin/echo "1"$X2?
