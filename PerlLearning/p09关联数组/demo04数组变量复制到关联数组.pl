@fruit = ( "apple", 17, "bananas", 9, "oranges", "none" );
%fruit = @fruit;
foreach $fu ( keys(%fruit) ) {
  print "$fruit{$fu}\n";
}

=pod
result is:
none
17
9
=cut

%fruits = ( "grapes" => 11, "lemons" => 27 );
@fruits = %fruits;

print "@fruits\n";

=pod
grapes 11 lemons 27
=cut
