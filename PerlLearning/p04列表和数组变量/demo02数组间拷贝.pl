# 数组拼接
@list1 = ( 2, 3, 4 );
@list2 = ( 1, @list1, 5 );
print "@list2\n";    # 1 2 3 4 5

# 将数组元素赋值给变量
@array=(5,7,11);
($var1,$var2)=@array;
print $var1."\n".$var2."\n";# 5 7

# 标准输入初始化数组
@arr=<STDIN>;
print "数组内容是： @arr\n";