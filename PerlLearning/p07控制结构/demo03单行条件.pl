( $var1, $var2, $var3, $var4 ) = ( 0, 0, 2, 3 );
print("\$var1 This is zero.\n") if ( $var1 == 0 );
print("\$var2 This is zero.\n") unless ( $var2 != 0 );
print("\$var3 Not zero yet.\n") while ( $var3-- > 0 );
print("\$var4 Not zero yet.\n") until ( $var4-- == 0 );

=pod
result is:
$var1 This is zero.
$var2 This is zero.
$var3 Not zero yet.
$var3 Not zero yet.
$var4 Not zero yet.
$var4 Not zero yet.
$var4 Not zero yet.
=cut