@arr1 = ( 1 .. 10 );
print "@arr1\n";    # 1 2 3 4 5 6 7 8 9 10
@arr2 = ( 2, 6 .. 11, 99 );
print "@arr2\n";    # 2 6 7 8 9 10 11 99
@arr3 = ( 1.9 .. 5.4 );    # 1 2 3 4 5
print "@arr3\n";
@day_of_month = ( "01" .. "31" );
print "@day_of_month\n";
# 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31

# 含有变量或表达式
$var1=33;
$var2=22;
@arr4=($var1..$var2*2);# 33 34 35 36 37 38 39 40 41 42 43 44
print "@arr4\n";
$fred="Fred";
print(("Hello, ".$fred."!\n")x2);
# Hello, Fred!
# Hello, Fred!
