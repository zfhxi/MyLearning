$line  = "Hello,123, This is the world of Perl!";
@array = $line =~ /\d+/g;

=pod
print join( "::", @array, "\n" );
123::
=cut

@array = $line =~ /\D+/g;

=pod
print join( "::", @array, "\n" );
Hello,::, This is the world of Perl!::
=cut

@array = $line =~ /\w+/g;

=pod
print join( "::", @array, "\n" );
Hello::123::This::is::the::world::of::Perl::
=cut

@array = $line =~ /\W+/g;

=pod
print join( "::", @array, "\n" );
,::, :: :: :: :: :: ::!::
=cut

@array = $line =~ /\s+/g;

=pod
print join( "::", @array, "\n" );
 :: :: :: :: :: ::
=cut

@array = $line =~ /\S+/g;

=pod
print join( "::", @array, "\n" );
Hello,123,::This::is::the::world::of::Perl!::
=cut
