our $stepNum = 0;

sub hnaoi {
  my ( $n, $start, $end, $extra ) = @_;
  if ( $n == 1 ) {
    $stepNum++;
    print "Steps: $stepNum == Move disk #$n from $start to $end.\n";
  }
  else {
    hnaoi( $n - 1, $start, $extra, $end );
    $stepNum++;
    print "Steps: $stepNum == Move disk #$n from $start to $end.\n";
    hnaoi( $n - 1, $extra, $end, $start );
  }
}

&hnaoi( 3, 'A', 'B', 'C' );

=pod
result is:
Steps: 1 == Move disk #1 from A to B.
Steps: 2 == Move disk #2 from A to C.
Steps: 3 == Move disk #1 from B to C.
Steps: 4 == Move disk #3 from A to B.
Steps: 5 == Move disk #1 from C to A.
Steps: 6 == Move disk #2 from C to B.
Steps: 7 == Move disk #1 from A to B.
=cut
