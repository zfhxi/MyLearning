$a = "abc";
$b = "xyz";

print $a lt $b;           #1
print $a gt $b;           #0
print "abc" cmp "abd";    #-1
print "abc" cmp "abc";    #0
print "abc" cmp "abb";    #1
