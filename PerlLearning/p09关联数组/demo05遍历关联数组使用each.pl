%ages = ( "Maris" => 61, "Aaron" => 25, "Young" => 53 );
while ( ( $name, $age ) = each(%ages) ) {
  print "$name: $age\n";
}

=pod
result is:
Maris: 61
Young: 53
Aaron: 25
=cut
