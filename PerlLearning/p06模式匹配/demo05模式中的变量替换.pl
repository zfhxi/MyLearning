$line    = "12\t34\t56";
$pattern = "[\\t]+";
@words   = split( /$pattern/, $line );
print join( "::", @words, "\n" );
