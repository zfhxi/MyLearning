/*
use Library
alter table Borrow
add constraint FK_Borrow_Reader
foreign key(Rno)references Reader(Rno)
*/
/*
select fk.*
,obj.name --外键名
,obj2.name --外键表
,obj3.name --主键表
from sysforeignkeys fk inner join sysobjects obj on fk.constid=obj.id
inner join sysobjects obj2 on fk.fkeyid = obj2.id
inner join sysobjects obj3 on fk.rkeyid = obj3.id
order by obj2.name
*/