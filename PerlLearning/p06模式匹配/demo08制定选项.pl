$number = <STDIN>;
if ( $number =~ /^-?\d+$|^-?0[xX][\da-fA-F]+$/ ) {
  $number += 0;
  print "$number is a legal integer.\n";
}
else {
  print "$number is not a legal integer.\n";
}
