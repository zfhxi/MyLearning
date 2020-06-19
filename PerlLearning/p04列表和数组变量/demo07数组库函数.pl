@array = ( "b", "a", "d", "c" );
print "@array\n";    # b a d c
@array = sort @array;
print "@array\n";    # a b c d
@array = reverse @array;
print "@array\n";    # d c b a
$string = join( "::", @array, "i" );
print "$string\n";    # d::c::b::a::i
@array2 = split( /::/, $string );
print "@array2\n";    # d c b a i
