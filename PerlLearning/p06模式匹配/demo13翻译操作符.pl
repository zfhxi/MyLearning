=pod
$string = "abcdefghiabc";
$string =~ tr/abc/def/;
print $string. "\n";

result is:
defdefghidef
=cut

# 所有小写字母转化为大写字母
=pod
$string='Hello World!';
$string=~tr/a-z/A-Z/;
print $string."\n";
result is:
HELLO WORLD!
=cut

# 删除重复字符
=pod
$string="www.baidu.comm";
$string=~tr/a-z/a-z/s;
print $string."\n";
result is:
w.baidu.com
=cut

