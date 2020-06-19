open( in, "<testfile" ) or die("Can't open this file! $！ \n");
while ( $line = <in> ) {
  while ( $line =~ /\b([A-Z]\S+)/g ) {
    $word = $1;
    $word =~ s/[;.,!:-]$//;    # 去除符号
    $wordlist{$word} += 1;
  }
}
close(in);

=pod
foreach $capword ( keys(%wordlist) ) {
  print "$capword: $wordlist{$capword}\n";
}
=cut

=pod
foreach $capword ( sort { $a cmp $b } keys(%wordlist) ) {
  print "$capword: $wordlist{$capword}\n";
}
result is:
Hello: 2
Perl: 2
This: 2
World: 1
=cut

=pod
foreach $capword ( sort { $wordlist{$a} <=> $wordlist{$b} } keys(%wordlist) )
{
  print "$capword: $wordlist{$capword}\n";
}
result is:
World: 1
Perl: 2
This: 2
Hello: 2
=cut


=pod
result is:
Perl: 2
World: 1
Hello: 2
This: 2
=cut
