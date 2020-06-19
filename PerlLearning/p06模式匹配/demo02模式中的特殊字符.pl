# +
$line  = "this is a string: deeeeeef !";
@array = split( /de+f/, $line );

=pod
print join("\n",@array,"\n");
# 输出
this is a string: 
 !
=cut

# []、[^]
$line  = "this is a test, isok ?";
@array = split( /is[^ +]/, $line );

=pod
print join( "\n", @array, "\n" );
# 输出
this is a test, 
k ?
=cut

# *、?
$line  = "this is a test!!!";
@array = split( /th?/, $line );

=pod
print join( "\n", @array, "\n" );
# 输出
is is a 
es
!!!
=cut

# 转义字符
$line = "this is a test. * !!!";
# @array=split(/*/,$line); # Quantifier follows nothing in regex
@array=split(/\*/,$line);
=pod
# 输出
this is a test. 
 !!!
=cut
# @array=split(/\./,$line);
@array=split(/\Q.\E/,$line); # 与上行等价
=pod
# 输出
this is a test
 * !!!
=cut

print join("\n",@array,"\n");