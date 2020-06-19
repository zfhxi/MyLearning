@arr = ( 11, 22, 33 );
$arr = "ok";
print "$arr[0]\n";

# 下列输出： ok[0]
print "$arr\[0]\n";
print "$arr" . "[0]\n";
print "${arr}[0]\n";

# I don't understand
print "$\{arr}" . "\n";
