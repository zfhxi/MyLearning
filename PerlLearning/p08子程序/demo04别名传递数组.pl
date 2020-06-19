@myarray = ( 1, 2, 3, 4, 5 );

sub my_sub {
  local (*subarray) = @_;
  for ( $i = 0; $i < @subarray; $i++ ) {
    $subarray[$i] **= 2;
  }
}

&my_sub(*myarray);
foreach $var (@myarray) {
  print $var. ' ';
}
print "\n";
