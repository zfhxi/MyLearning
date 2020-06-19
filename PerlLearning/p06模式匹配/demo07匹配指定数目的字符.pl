open( in,  "<ace2.fasta" ) or die("Can not open this file to read!");
open( out, ">ify.xls" )    or die("Can not open this file to write!");

while ( $line = <in> ) {
  chomp($line);
  if ( $line =~ /^\>/ ) {
    if ($lines) {
      if ( $lines =~ /P{4,}/ ) {
        print out "\tY\n";
      }
      else {
        print out "\tN\n";
      }
    }

    $line =~ /(\S+)/o;
    $title = $1;
    $title =~ /([^>]+)/o;
    $subtitle = $1;
    print out $subtitle;
    $lines = "";
  }
  else {
    $lines .= $line;
  }
}

# 文件读完后，$lines 还有内容未被处理
if ($lines) {
  if ( $lines =~ /P{4,}/ ) {
    print out "\tY\n";
  }
  else {
    print out "\tN\n";
  }
}

close(in);
close(out);
