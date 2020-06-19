$foo = 26;
@foo = ( "here is", "a", "list" );

sub test {
  local (*var) = @_;
  $var = 33;
  foreach $var (@var) {
    $var .= " hi";
  }
}
&test(*foo);
print "$foo\n";
foreach $var (@foo) {
  print $var. "\n";
}

=pod
result is:
33
here is hi
a hi
list hi
=cut
