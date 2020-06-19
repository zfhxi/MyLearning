# 匹配范围小写字母
$line  = "Hello, This is a demo!";
@array = $line =~ /[f-z]+/g;

=pod
print "@array\n";
# 输出
llo his is mo
=cut

# 匹配
@array = $line =~ /[A-Z]+/g;

=pod
print "@array\n";
# 输出
H T
=cut

$line  = "My age is 49!\n";
@array = $line =~ /[0-9]+/g;

=pod
print "@array\n";
# 输出
49
=cut
