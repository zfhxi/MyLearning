@arr    = ( 1, 2, 3, 4 );
$scalar = $arr[0];
print $scalar. "\n";    # 1
$arr[3] = 5;
$scalar = $arr[4];
print $scalar. "\n";
$arr[6] = 17;
print "@arr\n";         # 1 2 3 4 5   17
