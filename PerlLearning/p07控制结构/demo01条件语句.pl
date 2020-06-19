=pod
$password = <STDIN>;
chomp($password);
if ( length($password) < 8 ) {
  print "error: length less than 8";
}
elsif ( $password !~ /[a-z]/ ) {
  print "error: with no letter";
}
elsif ( $password !~ /[0-9]/ ) {
  print "error: with no digit";
}
elsif ( $password !~ /[A-Z]/ ) {
  print "error: with no daxie";
}
elsif ( $password !~ /^([A-Za-z][A-Z0-9a-z_]{7,})$/ ) {
  print "error: unknown char!";
}
else {
  print "pass";
}
print "\n";
=cut

print ((3>2?"2":"3")."\n");
=pod
result is:
2
=cut