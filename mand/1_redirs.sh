# **************************************************************************** #
#                                    REDIRS                                    #
# **************************************************************************** #
#Test Number 793 input
grep hi <./test_files/infile

#Test Number 794 input
grep hi "<infile" <         ./test_files/infile

#Test Number 795 input
grep hi <./test_files/infile_big <./test_files/infile

#Test Number 796 input
cat <"./test_files/file name with spaces"

#Test Number 797 input
cat <./test_files/infile_big ./test_files/infile

#Test Number 798 input
cat <"1""2""3""4""5"

#Test Number 799 input
cat <"./test_files/infile"

#Test Number 800 input
echo <"./test_files/infile_big" | cat <"./test_files/infile"

#Test Number 801 input
echo <"./test_files/infile_big" | cat "./test_files/infile"

#Test Number 802 input
echo hi | cat <"./test_files/infile"

#Test Number 803 input
echo hi | cat "./test_files/infile"

#Test Number 804 input
cat <"./test_files/infile" | echo hi

#Test Number 805 input
cat <"./test_files/infile" | grep hello

#Test Number 806 input
cat <"./test_files/infile_big" | echo hi

#Test Number 807 input
cat <missing

#Test Number 808 input
cat <missing | cat

#Test Number 809 input
cat <missing | echo oi

#Test Number 810 input
cat <missing | cat <"./test_files/infile"

#Test Number 811 input
echo <123 <456 hi | echo 42

#Test Number 812 input
ls >./outfiles/outfile01

#Test Number 813 input
ls >         ./outfiles/outfile01

#Test Number 814 input
ls >./outfiles/outfile01 >./outfiles/outfile02

#Test Number 815 input
ls >./outfiles/outfile01 >./test_files/invalid_permission

#Test Number 816 input
ls >"./outfiles/outfile with spaces"

#Test Number 817 input
ls >"./outfiles/outfile""1""2""3""4""5"

#Test Number 818 input
ls >"./outfiles/outfile01" >./test_files/invalid_permission >"./outfiles/outfile02"

#Test Number 819 input
ls >./test_files/invalid_permission >"./outfiles/outfile01" >./test_files/invalid_permission

#Test Number 820 input
cat <"./test_files/infile" >"./outfiles/outfile01"

#Test Number 821 input
echo hi >./outfiles/outfile01 | echo bye

#Test Number 822 input
echo hi >./outfiles/outfile01 >./outfiles/outfile02 | echo bye

#Test Number 823 input
echo hi >./outfiles/outfile01 >./test_files/invalid_permission | echo bye

#Test Number 824 input
echo hi >./test_files/invalid_permission | echo bye

#Test Number 825 input
echo hi >./test_files/invalid_permission >./outfiles/outfile01 | echo bye

#Test Number 826 input
cat <"./test_files/infile" >./test_files/invalid_permission

#Test Number 827 input
cat >./test_files/invalid_permission <"./test_files/infile"

#Test Number 828 input
cat <missing >./outfiles/outfile01

#Test Number 829 input
cat >./outfiles/outfile01 <missing

#Test Number 830 input
cat <missing >./test_files/invalid_permission

#Test Number 831 input
cat >./test_files/invalid_permission <missing

#Test Number 832 input
cat >./outfiles/outfile01 <missing >./test_files/invalid_permission

#Test Number 833 input
ls >>./outfiles/outfile01

#Test Number 834 input
ls >>      ./outfiles/outfile01

#Test Number 835 input
ls >>./outfiles/outfile01 >./outfiles/outfile01

#Test Number 836 input
ls >./outfiles/outfile01 >>./outfiles/outfile01

#Test Number 837 input
ls >./outfiles/outfile01 >>./outfiles/outfile01 >./outfiles/outfile02

#Test Number 838 input
ls >>./outfiles/outfile01 >>./outfiles/outfile02

#Test Number 839 input
ls >>./test_files/invalid_permission

#Test Number 840 input
ls >>./test_files/invalid_permission >>./outfiles/outfile01

#Test Number 841 input
ls >>./outfiles/outfile01 >>./test_files/invalid_permission

#Test Number 842 input
ls >./outfiles/outfile01 >>./test_files/invalid_permission >>./outfiles/outfile02

#Test Number 843 input
ls <missing >>./test_files/invalid_permission >>./outfiles/outfile02

#Test Number 844 input
ls >>./test_files/invalid_permission >>./outfiles/outfile02 <missing

#Test Number 845 input
echo hi >>./outfiles/outfile01 | echo bye

#Test Number 846 input
echo hi >>./outfiles/outfile01 >>./outfiles/outfile02 | echo bye

#Test Number 847 input
echo hi >>./test_files/invalid_permission | echo bye

#Test Number 848 input
echo hi >>./test_files/invalid_permission >./outfiles/outfile01 | echo bye

#Test Number 849 input
cat <minishell.h>./outfiles/outfile

#Test Number 850 input
cat <minishell.h|ls

### SIMPLE ###
#Test Number 851 input
/bin/echo 42 > tmp_redir_out 42
#Test Number 852 input
cat tmp_redir_out
#Test Number 853 input
rm tmp_redir_out

#Test Number 854 input
/bin/echo "cat this text\n" > tmp_redir_out
#Test Number 855 input
cat <tmp_redir_out
#Test Number 856 input
rm tmp_redir_out

#Test Number 857 input
cat | cat | ls

#Test Number 858 input
cat < /dev/null

#Test Number 859 input
/bin/echo 42 > /dev/null

#Test Number 860 input
/bin/echo 42 >> /dev/null

### OVERWRITE ###
#Test Number 861 input
/bin/echo 42 > /dev/null > /dev/null > /dev/null > /dev/null > tmp_redir_out
#Test Number 862 input
cat tmp_redir_out
#Test Number 863 input
rm tmp_redir_out

#Test Number 864 input
/bin/echo 42 > tmp_redir_out > tmp_redir_out1 > tmp_redir_out2 > tmp_redir_out3
#Test Number 865 input
/bin/echo 0
#Test Number 866 input
cat tmp_redir_out
#Test Number 867 input
/bin/echo 1
#Test Number 868 input
cat tmp_redir_out1
#Test Number 869 input
/bin/echo 2
#Test Number 870 input
cat tmp_redir_out2
#Test Number 871 input
/bin/echo 3
#Test Number 872 input
cat tmp_redir_out3
#Test Number 873 input
rm tmp_redir_out tmp_redir_out1 tmp_redir_out2 tmp_redir_out3

#Test Number 874 input
/bin/echo 42 > /dev/null > tmp_redir_out
#Test Number 875 input
/bin/echo 2 >> /dev/null >> tmp_redir_out
#Test Number 876 input
cat tmp_redir_out
#Test Number 877 input
rm tmp_redir_out

### PERMISSION DENIED ###
#Test Number 878 input
touch tmp_redir_out_file1
#Test Number 879 input
chmod -r tmp_redir_out_file1
#Test Number 880 input
/bin/echo 1 > tmp_redir_out tmp_redir_out_file1

#Test Number 881 input
/bin/grep 1 < inputfile

#Test Number 882 input
/bin/grep 1 < NO_SUCH_FILE

#Test Number 883 input
/bin/grep 1 < inputfile < inputfile

#Test Number 884 input
/bin/grep 1 < NO_SUCH_FILE < inputfile

#Test Number 885 input
rm -f tmp_std_outfile

#Test Number 886 input
rm -f tmp_std_outfile

#Test Number 887 input
rm -f tmp_std_outfile

#Test Number 888 input
/bin/echo 1 >/dev/null | /usr/bin/grep 1

#Test Number 889 input
/bin/echo 1 >/dev/null | /bin/echo 2

#Test Number 890 input
/bin/echo >/dev/null 1 | /usr/bin/grep 1

#Test Number 891 input
/bin/echo >/dev/null 1 | /bin/echo 2

### HERE_DOC ###
#Test Number 892 input
cat << lim
#Test Number 893 input
 "lim"
#Test Number 894 input
HELLO
#Test Number 895 input
42
#Test Number 896 input
 lim
#Test Number 897 input
testing your minishell
#Test Number 898 input
limm
#Test Number 899 input
lim

#Test Number 900 input
<<lim cat
#Test Number 901 input
 "lim"
#Test Number 902 input
HELLO
#Test Number 903 input
42
#Test Number 904 input
 lim
#Test Number 905 input
testing your minishell
#Test Number 906 input
limm
#Test Number 907 input
lim

#Test Number 908 input
cat << lim
#Test Number 909 input
test
#Test Number 910 input
lim

#Test Number 911 input
cat << EOF
#Test Number 912 input
"EOF"
#Test Number 913 input
!! HELLO
#Test Number 914 input
@42 !!
#Test Number 915 input
 EOF\t\b\n
#Test Number 916 input
testing your minishell :)
#Test Number 917 input
limm
#Test Number 918 input
EOF

#Test Number 919 input
cat << hello
#Test Number 920 input
$USER
#Test Number 921 input
$NOVAR
#Test Number 922 input
$HOME
#Test Number 923 input
hello

#Test Number 924 input
cat << 'lim'
#Test Number 925 input
$USER
#Test Number 926 input
$NOVAR
#Test Number 927 input
$HOME
#Test Number 928 input
lim

#Test Number 929 input
cat << lim''
#Test Number 930 input
$USER
#Test Number 931 input
$NOVAR
#Test Number 932 input
$HOME
#Test Number 933 input
lim

#Test Number 934 input
cat << "lim"
#Test Number 935 input
$USER
#Test Number 936 input
$NOVAR
#Test Number 937 input
$HOME
#Test Number 938 input
lim

#Test Number 939 input
cat << 'lim'
#Test Number 940 input
$USER
#Test Number 941 input
$NOVAR
#Test Number 942 input
$HOME
#Test Number 943 input
lim

#Test Number 944 input
> out
/bin/rm -f out

#Test Number 945 input
< out
/bin/rm -f out

#Test Number 946 input
>> out
/bin/rm -f out
