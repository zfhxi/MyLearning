$string="25abc8/abcd";
$string=~/abc(?![0-9])./;
$matched=$&;
print $matched."\n";
=pod
result is:
abcd
=cut