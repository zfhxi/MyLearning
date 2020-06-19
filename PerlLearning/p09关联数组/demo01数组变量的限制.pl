# 文件中单词计数
open( in, "<testfile" ) or die("Can't open this file! $!\n");
@wordlist  = ();
@wordcount = ();
while ( $line = <in> ) {
  while ( $line =~ /\b([A-Z]\S+)/g ) {
    $word = $1;
    $word =~ s/[;.,!:-]$//;    # 去除结尾的符号
    for ( $count = 0; $count < @wordlist; $count++ ) {
      $existFlag = 0;
      if ( $wordlist[$count] eq $word ) {
        $existFlag = 1;
        $wordcount[$count] += 1;
        last;
      }
    }
    if ( $existFlag == 0 ) {
      $oldlength             = @wordlist;
      $wordlist[$oldlength]  = $word;
      $wordcount[$oldlength] = 1;
    }
  }
}
close(in);

foreach $idx ( 0 .. @wordlist - 1 ) {
  print "$wordlist[$idx]: $wordcount[$idx]\n";
}

=pod
result is:
Hello: 2
World: 1
This: 2
Perl: 2
=cut
