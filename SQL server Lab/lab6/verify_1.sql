/*
use Library
alter table Borrow
add constraint pk_borrnum primary key(Borrnum), 
constraint borrnum_uni unique(Borrnum)

alter table Reader
add constraint pk_Rno primary key(Rno), 
constraint rno_uni unique(Rno);
*/

insert into Borrow values(null,'R04','B02','2015-06-05','2015-08-10')
insert into Borrow values(7,'R04','B02','2015-06-05','2015-08-10')