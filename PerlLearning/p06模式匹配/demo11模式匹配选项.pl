# 匹配所有可能

=pod
while ( "balata" =~ /.a/g ) {
  $match = $&;
  print("$match\n");
}
result is:
ba
la
ta
=cut

# 忽略大小写

=pod
open(in,"<manuscript.txt");
$str="";
while($line=<in>){
  chomp($line);
  $str.=" ".$line;
}

@matches=$str=~/\bwe\b/gi;
print @matches."\n";

foreach $var(@matches){
  print $var."\n";
}
close(in);
result is:
10
We
we
We
We
We
we
We
we
we
we
=cut

# 将字符串看做多行

=pod
open(in,"<manuscript.txt");
$str="";
while($line=<in>){
  $str.=$line;
}
@matches=$str=~/^we/gim;
print @matches."\n";

foreach $var (@matches){
  print $var."\n";
}
result is:
2
We
We
=cut

# 将字符串看做单行例
=pod
$str = "axxx\nxxxbc";
if ( $str =~ /a.*bc/ ) {
  print "Y\n";
}
elsif ( $str =~ /a.*bc/s ) {
  print "Yes\n";
}
else {
  print "N\n";
}
result is:
Yes
=cut

# 模式匹配中忽略空格
=pod
$str="123 abcdefg";
if($str=~/1 2 3\sabc/x){
  print "Yes\n";
}else{
  print "No\n";
}
result is:
Yes
=cut