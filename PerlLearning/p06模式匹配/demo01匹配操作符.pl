$question = <STDIN>;
if ( $question =~ /please/ ) {
  print "Thank you for being polite!\n";
}
if ( $question !~ /thank/ ) {
  print "You have not said thanks!\n";
}
