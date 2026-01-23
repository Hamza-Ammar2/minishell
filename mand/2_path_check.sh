# **************************************************************************** #
#                                  PATH FAILS                                  #
# **************************************************************************** #

#Test Number 1285 input
unset PATH
#Test Number 1286 input
echo $PATH
#Test Number 1287 input
/bin/ls
#Test Number 1288 input
echo 1
#Test Number 1289 input
cd -
#Test Number 1290 input
echo 42

#Test Number 1291 input
unset PATH
#Test Number 1292 input
echo 42
#Test Number 1293 input
unset PATH
#Test Number 1294 input
unset PATH
#Test Number 1295 input
unset PATH
#Test Number 1296 input
echo $PATH
#Test Number 1297 input
echo 1
#Test Number 1298 input
echo 42

#Test Number 1299 input
export PATH=""
#Test Number 1300 input
echo $PATH

#Test Number 1301 input
echo 1

#Test Number 1302 input
cd -

#Test Number 1303 input
cd .

#Test Number 1304 input
cd ~

#Test Number 1305 input
cd ~/Desktop/
#Test Number 1306 input
pwd

#Test Number 1307 input
export PATH=
#Test Number 1308 input
echo $PATH
#Test Number 1309 input
echo 1

#Test Number 1310 input
export PATH=1
#Test Number 1311 input
echo $PATH
#Test Number 1312 input
echo 1

#Test Number 1313 input
env -i ./minishell
#Test Number 1314 input
cd /bin/
#Test Number 1315 input
ls

#Test Number 1316 input
touch tmp_x_file1
#Test Number 1317 input
tmp_x_file1
#Test Number 1318 input
echo $?
#Test Number 1319 input
./tmp_x_file1
#Test Number 1320 input
echo $?
#Test Number 1321 input
export PATH=$HOME
#Test Number 1322 input
echo $PATH
#Test Number 1323 input
tmp_x_file1
#Test Number 1324 input
echo $?
#Test Number 1325 input
./tmp_x_file1
#Test Number 1326 input
echo $?
#Test Number 1327 input
unset PATH
#Test Number 1328 input
tmp_x_file1
#Test Number 1329 input
echo $?
#Test Number 1330 input
./tmp_x_file1
#Test Number 1331 input
echo $?
#Test Number 1332 input
echo 42
/bin/rm -f tmp_x_file1

#Test Number 1333 input
cd doesntexist

#Test Number 1334 input
export PATH=""
#Test Number 1335 input
ls
