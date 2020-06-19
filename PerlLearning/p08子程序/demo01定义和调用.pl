# 先调用

=pod
&printhello;
result is:
hello
=cut

# 定义
sub printhello {
  print "hello\n";
}

# 后调用

=pod
printhello;
# do printhello; # 等价与上
result is:
hello
=cut

# 前向引用

=pod
sub printWorld;

printWorld;

sub printWorld{
  print "World\n";
}

result is:
World
=cut
