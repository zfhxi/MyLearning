$vars=@ARGV[0];
$varnum=@ARGV;
print $vars."\n".$varnum."\n";
while($line=<>){
  print $line
}
=pod
# 终端下运行：
perl demo04命令行参数.pl demo02_outfile.txt demo02写文件.pl
=cut