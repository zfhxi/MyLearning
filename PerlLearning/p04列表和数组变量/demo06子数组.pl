@array    = ( 1, 2, 3, 4, 5 );
@subarray = @array[ 1, 2, 4 ];
print "@subarray\n";    # 2 3 5
@subarray2 = @array[ 2 .. 4 ];
print "@subarray2\n";    # 3 4 5

@array[ 0, 1 ] = ( 11, 22 );
print "@array\n";        # 11 22 3 4 5
@array[ 1 .. 3 ] = ( 111, 222, 333 );
print "@array\n";        # 11 111 222 333 5

# 交换数组元素
@array[ 1, 2 ] = @array[ 2, 1 ];
print "@array\n";        # 11 222 111 333 5
