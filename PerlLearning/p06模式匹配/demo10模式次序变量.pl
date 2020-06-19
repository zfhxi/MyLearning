$string = "This string contains the number 25.11.";
$string =~ /-?(\d+)\.?(\d+)/;
$integerpart = $1;
$decimalpart = $2;
$totalpart   = $&;

=pod
print $integerpart. "\n";
print $decimalpart. "\n";
print $totalpart. "\n";
result is:
25
11
25.11
=cut