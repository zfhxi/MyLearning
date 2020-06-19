%fruit = ( "apples", 17, "bananas", 9, "oranges", "none" );
foreach $capword ( keys(%fruit) ) {
  print "$capword: $fruit{$capword}\n";
}

=pod
result is:
oranges: none
apples: 17
bananas: 9
=cut

%fruits = ( "apples" => 17, "bananas" => 9, "oranges" => "none" );
foreach $capword ( keys(%fruits) ) {
  print "$capword: $fruit{$capword}\n";
}

=pod
result is:
bananas: 9
apples: 17
oranges: none
=cut
