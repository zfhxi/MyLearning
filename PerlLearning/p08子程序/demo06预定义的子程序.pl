BEGIN {
  print("start!\n");
}
AUTOLOAD {
  print("subroutine $AUTOLOAD not found!\n");
  print("arguements passed: @_\n");
}

END {
  print("END\n");
}

pasdf( 1, 2, 3 );

=pod
result is:
start!
subroutine main::pasdf not found!
arguements passed: 1 2 3
END
=cut
