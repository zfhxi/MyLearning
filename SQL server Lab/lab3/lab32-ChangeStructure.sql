/*
use sales
-- add email column
alter table test2
add email char(40) not null

use sales
-- alter column
alter table test2
alter column email char(20) NULL

*/
use sales
-- delete column
alter table test2
drop column email