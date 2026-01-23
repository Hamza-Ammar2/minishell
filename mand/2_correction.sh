# **************************************************************************** #
#                                  CORRECTION                                  #
# **************************************************************************** #

#Test Number 1117 input
/bin/echo
#Test Number 1118 input
/bin/echo 1
#Test Number 1119 input
/bin/cat 42

#Test Number 1120 input
""

#Test Number 1121 input
"   "

#Test Number 1122 input
"    "

#Test Number 1123 input
"		"

#Test Number 1124 input
"			"

#Test Number 1125 input
/bin/echo hello 42

#Test Number 1126 input
/bin/sleep 0

#Test Number 1127 input
/bin/echo -n 1

#Test Number 1128 input
echo

#Test Number 1129 input
echo hello world

#Test Number 1130 input
echo -n 42

#Test Number 1131 input
echo -n 42 -n

#Test Number 1132 input
echo 42 -n

#Test Number 1133 input
echo -n -n -n 42

#Test Number 1134 input
echo -n -n -n -n 42

#Test Number 1135 input
exit

#Test Number 1136 input
exit 42

#Test Number 1137 input
exit ""

#Test Number 1138 input
exit 1 2 3

#Test Number 1139 input
exit 42 42

#Test Number 1140 input
exit A

#Test Number 1141 input
exit A 1

#Test Number 1142 input
exit 1 A

#Test Number 1143 input
/bin/echo 42
#Test Number 1144 input
echo $?

#Test Number 1145 input
/bin/cat 42
#Test Number 1146 input
echo $?

#Test Number 1147 input
/bin/exe42 42

#Test Number 1148 input
42 42

#Test Number 1149 input
/bin/echo 42
#Test Number 1150 input
expr $? + $?

#Test Number 1151 input
/bin/cat 42
#Test Number 1152 input
expr $? + $?

#Test Number 1153 input
echo "Hello World"

#Test Number 1154 input
echo "  ""Hello World"

#Test Number 1155 input
echo "  "Hello "World "

#Test Number 1156 input
"echo" 42

#Test Number 1157 input
"echo 42"

#Test Number 1158 input
echo " cat ' lol.c"

#Test Number 1159 input
/bin/echo @World"42"Hello

#Test Number 1160 input
echo 'Hello World'

#Test Number 1161 input
echo '  ' Hello World

#Test Number 1162 input
echo '  'Hello 'World '

#Test Number 1163 input
'echo' 42

#Test Number 1164 input
'e'cho 42

#Test Number 1165 input
echo 'cat lol.c << cat > lol.c'

#Test Number 1166 input
echo @World'42'Hello

#Test Number 1167 input
echo "" ''

#Test Number 1168 input
echo """"''""''""

#Test Number 1169 input
echo " "" " ' ' " " ' ' " "

#Test Number 1170 input
echo 1 '|' echo 2

#Test Number 1171 input
echo 1 '&&' echo 2

#Test Number 1172 input
echo 1 '||' echo 2

#Test Number 1173 input
echo 1 '>' echo 2

#Test Number 1174 input
echo 1 '>>' file 2

#Test Number 1175 input
'<<' lim echo 1 >>/dev/null

#Test Number 1176 input
echo "$USER"

#Test Number 1177 input
echo "   $   "

#Test Number 1178 input
echo '$USER'

#Test Number 1179 input
echo '   $   '

#Test Number 1180 input
echo "$HO ME"

#Test Number 1181 input
echo '$HO ME'

#Test Number 1182 input
echo $"HOME"

#Test Number 1183 input
echo $'HOME'

#Test Number 1184 input
echo ""$PWD""

#Test Number 1185 input
echo ''$PWD''

#Test Number 1186 input
echo $USE"R"$HOME

#Test Number 1187 input
echo $"HOME"$USER

#Test Number 1188 input
echo $"HOM"E$USER

#Test Number 1189 input
echo $"'HOM'E"$USER

#Test Number 1190 input
echo $'HOM'E$USER

#Test Number 1191 input
echo $"HOME"

#Test Number 1192 input
echo $'HOME'

#Test Number 1193 input
echo $

#Test Number 1194 input
echo "$"

#Test Number 1195 input
echo '$='

#Test Number 1196 input
echo "$""$"

#Test Number 1197 input
echo $"$"

#Test Number 1198 input
echo $"42$"

#Test Number 1199 input
echo "$"$

#Test Number 1200 input
echo $'$'

#Test Number 1201 input
echo '$'$

#Test Number 1202 input
env | grep HOME

#Test Number 1203 input
env | grep $USER

#Test Number 1204 input
export USER=
#Test Number 1205 input
env | grep USER

#Test Number 1206 input
export USER="@?/"
#Test Number 1207 input
env | grep USER

#Test Number 1208 input
export NEW="4 2"
#Test Number 1209 input
env | grep NEW

#Test Number 1210 input
export NEW="4=2"
#Test Number 1211 input
env | grep NEW

#Test Number 1212 input
export NEW=4=2
#Test Number 1213 input
env | grep 4=2

#Test Number 1214 input
export =

#Test Number 1215 input
export ''=''

#Test Number 1216 input
export ""=""

#Test Number 1217 input
export export

#Test Number 1218 input
export =============123

#Test Number 1219 input
export echo

#Test Number 1220 input
unset

#Test Number 1221 input
unset env

#Test Number 1222 input
unset PATH
#Test Number 1223 input
echo $PATH
#Test Number 1224 input
unset PATH
#Test Number 1225 input
echo $PATH
#Test Number 1226 input
unset HOME
#Test Number 1227 input
echo $HOME

#Test Number 1228 input
export NEW=42
#Test Number 1229 input
env | grep NEW
#Test Number 1230 input
unset NEW
#Test Number 1231 input
env | grep NEW
#Test Number 1232 input
unset NEW
#Test Number 1233 input
unset NEW
#Test Number 1234 input
unset NEW
#Test Number 1235 input
unset NEW
#Test Number 1236 input
unset NEW
#Test Number 1237 input
env | grep NEW

#Test Number 1238 input
cd .
#Test Number 1239 input
/bin/ls

#Test Number 1240 input
cd ..
#Test Number 1241 input
/bin/ls

#Test Number 1242 input
cd /notsuchdir
#Test Number 1243 input
/bin/ls

#Test Number 1244 input
cd /////
#Test Number 1245 input
/bin/ls

#Test Number 1246 input
cd "cmds/"
#Test Number 1247 input
/bin/ls

#Test Number 1248 input
cd cmds/
#Test Number 1249 input
/bin/ls

#Test Number 1250 input
cd ./cmds/
#Test Number 1251 input
/bin/ls

#Test Number 1252 input
mkdir bla_test
#Test Number 1253 input
chmod -wrx bla_test
#Test Number 1254 input
cd bla_test
#Test Number 1255 input
chmod +wrx bla_test
#Test Number 1256 input
rm -r bla_test

#Test Number 1257 input
pwd

#Test Number 1258 input
cd $HOME
#Test Number 1259 input
pwd

#Test Number 1260 input
pwd pwd

#Test Number 1261 input
pwd hello

#Test Number 1262 input
unset PATH
#Test Number 1263 input
pwd

#Test Number 1264 input
unset PATH
#Test Number 1265 input
cd /bin
#Test Number 1266 input
ls

#Test Number 1267 input
unset PATH
#Test Number 1268 input
cd /bin/../bin/
#Test Number 1269 input
ls

#Test Number 1270 input
unset PATH
#Test Number 1271 input
cd /bin/../bin/../bin/../bin/../bin/../bin/../bin/../bin/
#Test Number 1272 input
../bin/../bin/ls

#Test Number 1273 input
unset PATH
#Test Number 1274 input
cd /bin/
#Test Number 1275 input
sleep 2

#Test Number 1276 input
mkdir tmp_path_test1 tmp_path_test2
#Test Number 1277 input
printf '#include <unistd.h>\nint main(){write(1, \"1\\n\", 2);}' > tmp_path_test1/test1.c
#Test Number 1278 input
gcc tmp_path_test1/test1.c -o tmp_path_test1/a.out
#Test Number 1279 input
printf '#include <unistd.h>\nint main(){write(1, \"2\\n\", 2);}' > tmp_path_test2/test2.c
#Test Number 1280 input
gcc tmp_path_test2/test2.c -o tmp_path_test2/a.out
#Test Number 1281 input
export PATH=tmp_path_test1:tmp_path_test2
#Test Number 1282 input
a.out
#Test Number 1283 input
export PATH=tmp_path_test2:tmp_path_test1
#Test Number 1284 input
a.out
/bin/rm -rf tmp_path_test1 tmp_path_test2

### REDIRS

### PIPES

### GO WILD

### ENV Var expansion

