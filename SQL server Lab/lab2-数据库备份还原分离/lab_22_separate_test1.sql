--Detach DB sample_1
use master
exec sp_detach_db test1, true	--sp_detach_db is provided by SQL server, used to separate the DB which is no need from the server