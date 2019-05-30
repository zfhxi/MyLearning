use Library

SELECT * FROM Reader r 
WHERE NOT EXISTS(
    SELECT * FROM Borrow b1
    WHERE b1.Rno='R01' AND NOT EXISTS(
        SELECT * FROM Borrow b2
        WHERE b2.Rno=r.Rno AND b2.Bno=b1.Bno
    )
)