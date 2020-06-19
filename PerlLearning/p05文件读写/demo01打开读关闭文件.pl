open(MYFILE,"<ace.fasta") or die("Can not open file!\n");
=pod
while($line=<MYFILE>){
  chomp($line);
  print $line."\n";
}
# 等价于如下：
=cut
@lines=<MYFILE>;
print("@lines\n");

close(MYFILE);