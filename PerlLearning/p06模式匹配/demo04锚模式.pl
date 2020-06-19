$line  = "Hello, This is a demo!";
@array = $line =~ /\bi.+\b/g;

=pod
print "@array\n";
# 输出
is a demo
=cut

@array = $line =~ /\b[a-zA-Z]+!$/g;

=pod
print join( "\n", @array, "\n" );
# 输出
demo!
=cut

$line  = "hello abcdefghi, def ,abcdef";
@array = $line =~ /\B.+def\B/g;
=pod
print join( "\n", @array, "\n" );
# 输出
ello abcdef
=cut

# 判断输入的字符串是哪一种变量
$varname = <STDIN>;
chomp($varname);
if ( $varname =~ /^\$[A-Za-z][_0-9a-zA-Z]*$/ ) {
  print "$varname is a legal scalar variable\n";
}
elsif ( $varname =~ /^@[A-Za-z][_0-9a-zA-Z]*$/ ) {
  print "$varname is a legal array variable\n";
}
elsif ( $varname =~ /^[A-Za-z][_0-9a-zA-Z]*$/ ) {
  print "$varname is a legal file variable\n";
}
else {
  print "I do not understand what $varname is.\n";
}

