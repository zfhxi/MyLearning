%words = (
  "abel"    => "baker",
  "baker"   => "charlie",
  "charlie" => "delta",
  "delta"   => ""
);
$header = "abel";

$p = $header;
while ( $words{$p} ) {
  print $p. " => " . $words{$p} . "\n";
  $p = $words{$p};
}

=pod
result is:
abel => baker
baker => charlie
charlie => delta
=cut
