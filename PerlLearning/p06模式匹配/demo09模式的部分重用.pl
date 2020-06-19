$string = "Now is: 12-08-30 !";
$string=~/\d{2}([\W])\d{2}\1\d{2}/;

=pod
print $&."\n";
result is:
12-08-30
=cut