$var1 = 2, $var2 = $var1--;
print $var1. "\n" . $var2 . "\n";

$var3   = 26;
$result = ( ++$var3, $var3 + 5 );    #32
print $result. "\n";

$var4    = 26;
$result1 = ++$var4, $var4 + 5;
print $var4. "\n" . $result1 . "\n";    #27 27
