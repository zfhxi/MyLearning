=pod
$string="abc123def123";
$string=~s/123/456/;
print $string."\n";
result is:
abc456def123
=cut

# 使用模式次序变量
=pod
$string="abc123def123";
$string=~s/123/456/;
$string=~s/(\d+)/[$1]/;
print $string."\n";
result is:
abc[456]def123
=cut

# 使用替换操作符选项
=pod
$string="abc123def";
$string=~s/(\d+)/$&x2/e;
print $string."\n";
result is:
abc123123def
=cut