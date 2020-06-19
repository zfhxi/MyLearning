$number = 11;
$text   = "This text contains the number $number.\n"
    ;    # This text contains the number 11.

# 单引号、双引号区别
$text = 'this is two
lines of text';
## 等价与
$text = "this is two\nlines of text\n";

# 字符串和数值的转换

# 字符串转数字
$string = "43";
$number = 1;
$result = $string + $number;    # 44

# 含有非数字的字符串
$result = "hello" * 5;          # 0
$result = "12a34" + 1;          #13
