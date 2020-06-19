
=pod
sub printNums {
  my ( $num1, $num2, $num3 ) = @_;
  print "@_\n";
  print "$num1\n";
  print "$num2\n";
  print "$num3\n";
}

printNums(4,2,3);
result is:
4 2 3
4
2
3
=cut

# 传递数组

=pod
our @mylist=();
sub addlist {
  my (@list) = @_;
  push(@mylist,@list);
  print "@mylist\n";
}

addlist(1,2,3,4);
addlist((2,3,4));
addlist(("a"),2,("b","C"));
result is:
1 2 3 4
1 2 3 4 2 3 4
1 2 3 4 2 3 4 a 2 b C
=cut
