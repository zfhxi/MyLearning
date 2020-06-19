@array  = ( 32, 33, 34 );
$scalar = @array;
print "$scalar\n";    #3
($scalar) = @array;
print "$scalar\n";    #32

$count=1;
while($count<=@array){
  print('$array['.($count-1)."]:\t".$array[$count-1]."\n");
  $count++;
}