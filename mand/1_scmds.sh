# **************************************************************************** #
#                                     SCMD                                     #
# **************************************************************************** #

#Test Number 947 input
ls

#Test Number 948 input
cat cmds.sh

#Test Number 949 input
/bin/echo test1

#Test Number 950 input
""

#Test Number 951 input
touch ""

#Test Number 952 input
touch "  "
/bin/rm -f "  "


#Test Number 953 input
touch "
#Test Number 954 input
"
/bin/rm -f "
#Test Number 955 input
"

#Test Number 956 input
mkdir " "
/bin/rm -rf " "

#Test Number 957 input
asd
#Test Number 958 input
expr $? + $?

#Test Number 959 input
expr 21 + 21

#Test Number 960 input
"ls"

#Test Number 961 input
"cat cmds.sh"

#Test Number 962 input
"/bin/echo" test1

#Test Number 963 input
'/bin/echo test1'

#Test Number 964 input
awk '$1 ~ /^d/ {print $9}'

#Test Number 965 input
awk 'BEGIN{for(i=1;i<=10;i++){for(j=1;j<=10;j++){printf("%4d ",i*j)} printf("\n")}}' /dev/null | tail -n 10

#Test Number 966 input
awk 'BEGIN{for(i=1;i<=1000000;i++)print int(i)}' | awk '{sum+=$1} END {print sum/NR}'

#Test Number 967 input
asd
#Test Number 968 input
echo asd
#Test Number 969 input
echo $?

#Test Number 970 input
asd
#Test Number 971 input
pwd
#Test Number 972 input
echo $?

#Test Number 973 input
asd
#Test Number 974 input
unset USER
#Test Number 975 input
asd
#Test Number 976 input
pwd

#Test Number 977 input
asd
#Test Number 978 input
pwd
#Test Number 979 input
asd
#Test Number 980 input
echo asd
#Test Number 981 input
echo $?

#Test Number 982 input
asd
#Test Number 983 input
cd ..
#Test Number 984 input
echo $?

#Test Number 985 input
asd
#Test Number 986 input
unset PATH
#Test Number 987 input
echo $?

#Test Number 988 input
touch whatever
#Test Number 989 input
cat <"./whatever" >"./whatever"
#Test Number 990 input
rm -rf whatever

#Test Number 991 input
ls >"./ with spaces"
#Test Number 992 input
rm -rf " with spaces"

# **************************************************************************** #
#                                  BROKEN SCMD                                 #
# **************************************************************************** #

#Test Number 993 input
"."

#Test Number 994 input
.ls

#Test Number 995 input
./ls

#Test Number 996 input
"./"ls

#Test Number 997 input
"./""ls"

#Test Number 998 input
"./"''"ls"

#Test Number 999 input
3123

#Test Number 1000 input
lsa

#Test Number 1001 input
/ls

#Test Number 1002 input
EechoE

#Test Number 1003 input
/ls/

#Test Number 1004 input
/bin/

#Test Number 1005 input
/bin/cats

#Test Number 1006 input
./4242424242.sh

#Test Number 1007 input
rm -f something

#Test Number 1008 input
| echo -n oui

#Test Number 1009 input
| | |


