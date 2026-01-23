# **************************************************************************** #
#                                PARSING HELL                                  #
# **************************************************************************** #

#Test Number 90 input
">>" asd

#Test Number 91 input
>">" asd
/bin/rm -f ">"

#Test Number 92 input
>> '$USER'
#Test Number 93 input
cat $USER
/bin/rm -f '$USER'

#Test Number 94 input
>> '$USER'
#Test Number 95 input
cat '$USER'
/bin/rm -f '$USER'

#Test Number 96 input
"echo "

#Test Number 97 input
"echo -nnnnn"

#Test Number 98 input
"ECho" -n -nnn"" "-"nnnnn

#Test Number 99 input
"ECHO" "-n"

#Test Number 100 input
ECHO '''''-''n'

#Test Number 101 input
echo '' -n

#Test Number 102 input
echo "" "" "" -n -n -n -n

#Test Number 103 input
cat << $USER
#Test Number 104 input
why
#Test Number 105 input
not
#Test Number 106 input
$USER

#Test Number 107 input
export T=">>"
#Test Number 108 input
$T lol

#Test Number 109 input
cat << "$USER"
#Test Number 110 input
why
#Test Number 111 input
not
#Test Number 112 input
$USER

#Test Number 113 input
cat << "$US"E"R"
#Test Number 114 input
because
#Test Number 115 input
we
#Test Number 116 input
love
#Test Number 117 input
bash
#Test Number 118 input
$USER

#Test Number 119 input
>> $HOME

#Test Number 120 input
>> "$H"OM"E"
#Test Number 121 input
cat OME
/bin/rm -f OME

#Test Number 122 input
>> "$USER'$USER'"
#Test Number 123 input
cat "$USER'$USER'"
/bin/rm -f "$USER'$USER'"

#Test Number 124 input
>> "$USER"
#Test Number 125 input
cat $USER
/bin/rm -f $USER

#Test Number 126 input
cd $HOME/Desktop/
#Test Number 127 input
pwd

#Test Number 128 input
cd "$HOME"/Desktop/
#Test Number 129 input
pwd

#Test Number 130 input
cd "$H"O"ME"/Desktop/
#Test Number 131 input
echo $?

#Test Number 132 input
export T=n
#Test Number 133 input
echo "-"$T$T

#Test Number 134 input
export T=ech
#Test Number 135 input
echo $To

#Test Number 136 input
export T=ech
#Test Number 137 input
echo $T"o"

#Test Number 138 input
export T=ech
#Test Number 139 input
echo $T"o "

#Test Number 140 input
export T=ech
#Test Number 141 input
echo $T"o -n"

#Test Number 142 input
export T=ech
#Test Number 143 input
echo $T"o -n"

#Test Number 144 input
export T=ech
#Test Number 145 input
echo $T'o'

#Test Number 146 input
export T="-n test1 -n test 2"
#Test Number 147 input
echo $T

#Test Number 148 input
export T=ech
#Test Number 149 input
echo $T'o '

#Test Number 150 input
"ECHO"

#Test Number 151 input
'echo'

#Test Number 152 input
'PWD'

#Test Number 153 input
"PWD"

#Test Number 154 input
echo "-nnnnn "

#Test Number 155 input
ECHO -nn

#Test Number 156 input
ECHO -n -n

#Test Number 157 input
ECHO "-"""n""n""n""n""n""nnnnnn-n

#Test Number 158 input
ECHO "-"""n""n""n""n""n""nnnnnn -n

#Test Number 159 input
export T=nnnnnnnn
#Test Number 160 input
echo "-""$T"nnnnnnnnnnnnn -nnnnnnnn"$T" '-'"$T"

#Test Number 161 input
export T=nnnnnnnn
#Test Number 162 input
echo "-""$T"nnnnnnnnnnnnn -nnnnnnnn"$T" '-''$T'

#Test Number 163 input
export T=nnnnnnnn
#Test Number 164 input
echo "-"'$T'nnnnnnnnnnnnn -nnnnnnnn'$T' '-'"$T "

#Test Number 165 input
export T=nnnnnnnn
#Test Number 166 input
echo "-"'$T'nnnnnnnnnnnnn -nnnnnnnn$T '-''$T '

#Test Number 167 input
export T=e E=c S=h L=o
#Test Number 168 input
$T$E$S$L

#Test Number 169 input
export T=e E=c S=h L=o L=ok
#Test Number 170 input
$T$E$S$L

#Test Number 171 input
export T=e E=c S=h L=o
#Test Number 172 input
$T$E$S$L -n

#Test Number 173 input
export T=E E=c S=h L=o
#Test Number 174 input
$T$E$S$L -n

#Test Number 175 input
export T=E E=c S=h L=o
#Test Number 176 input
$T$E$S$L -nn

#Test Number 177 input
export T=e E=c S=h L=o
#Test Number 178 input
$T$E$S$L -nn

#Test Number 179 input
export T=e E=c S=h L=o
#Test Number 180 input
$T$E"c"$L -nn

#Test Number 181 input
export T=e E=c S=h L=o
#Test Number 182 input
$T$E"C"$L -nn

#Test Number 183 input
export T=e E=c S=h L=o
#Test Number 184 input
$T$E"C"$L "" -""n

#Test Number 185 input
$NOVAR

#Test Number 186 input
export T="s"
#Test Number 187 input
l$T

#Test Number 188 input
export T="s"
#Test Number 189 input
l$T -a

#Test Number 190 input
export T="l"
#Test Number 191 input
$Ts

#Test Number 192 input
export T="l"
#Test Number 193 input
$Ts -a

#Test Number 194 input
LS

#Test Number 195 input
Ls

#Test Number 196 input
lS

#Test Number 197 input
ls

#Test Number 198 input
PWD

#Test Number 199 input
pWD

#Test Number 200 input
pwd

#Test Number 201 input
pwD

#Test Number 202 input
ENV

#Test Number 203 input
CAT

#Test Number 204 input
EXPORT

#Test Number 205 input
export T="|"
#Test Number 206 input
echo segfault $T grep segfault

#Test Number 207 input
export T='|'
#Test Number 208 input
echo segfault $T grep segfault

#Test Number 209 input
export T=">"
#Test Number 210 input
echo segfault $T grep segfault

#Test Number 211 input
export T='<'
#Test Number 212 input
echo segfault $T grep segfault

#Test Number 213 input
export T="<<"
#Test Number 214 input
echo segfault $T grep segfault

#Test Number 215 input
export T='<<'
#Test Number 216 input
echo segfault $T grep segfault

#Test Number 217 input
export T="|"
#Test Number 218 input
$T$T$T$T$T$T$T

#Test Number 219 input
export T="echo segfault | grep segfault"
#Test Number 220 input
$T

#Test Number 221 input
export T=-nnnnnnnn"nnnnnnn "
#Test Number 222 input
echo $T

#Test Number 223 input
export T=-"n                    "
#Test Number 224 input
Echo $T

#Test Number 225 input
EXIT 123

#Test Number 226 input
Exit

#Test Number 227 input
UNSET USER

#Test Number 228 input
Unset USER

#Test Number 229 input
EXPORT T=LA
#Test Number 230 input
echo $T

#Test Number 231 input
Export T=LA
#Test Number 232 input
echo $T

#Test Number 233 input
"e"'x''p''o''r''t' L=T
#Test Number 234 input
echo $T

#Test Number 235 input
e""""""""""""cho

#Test Number 236 input
export T='|'
#Test Number 237 input
echo $T echo lala $T echo $T echo ?

#Test Number 238 input
export T="<<"
#Test Number 239 input
$T.

#Test Number 240 input
OLDPWD

#Test Number 241 input
USER

#Test Number 242 input
" ls"

#Test Number 243 input
" cat"

#Test Number 244 input
" echo"

#Test Number 245 input
" PWD"

#Test Number 246 input
" pwd"

#Test Number 247 input
"PWD "

#Test Number 248 input
"pwd "

#Test Number 249 input
'pwd '

#Test Number 250 input
p""''''w''''''""""""''''''''''''''''''''''''''''''''d

#Test Number 251 input
'''''''''''''''' echo ok

#Test Number 252 input
           ''echo ok

#Test Number 253 input
           ""echo ok

#Test Number 254 input
           ""echo"" ok

#Test Number 255 input
           ""'echo'"" ok

#Test Number 256 input
echo "         |       "  | echo maybe

#Test Number 257 input
echo "|"  | echo maybe

#Test Number 258 input
echo '|'  | echo maybe

#Test Number 259 input
echo -nnnnnnnnnnnn

#Test Number 260 input
export L=amazing L=ok L=cool
#Test Number 261 input
echo $L

#Test Number 262 input
export L=amazing L=ok L=cool
#Test Number 263 input
export L=ok
#Test Number 264 input
echo $L

#Test Number 265 input
echo '$'$'$'$'$'

#Test Number 266 input
echo '$'$'$'$'$'$'$'

#Test Number 267 input
echo "$"$'$'$"$"$"$"$'$'

#Test Number 268 input
echo $/ $/ 

#Test Number 269 input
echo $U/SER

#Test Number 270 input
echo "$/ $/"

#Test Number 271 input
echo $/"$/"

#Test Number 272 input
echo '$/'

#Test Number 273 input
exit 9223372036854775805

#Test Number 274 input
exit 123"123"

#Test Number 275 input
<| echo ok

#Test Number 276 input
>| echo sure

#Test Number 277 input
cd --
