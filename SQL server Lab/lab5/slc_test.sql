use Library
select Rname, datename(year,GETDATE())-Rage as Born_Year
from Reader