-- Crate DB sample_1
use master
create database test1
on
	(name = test1_dat,filename = 'd:\exercise\test1dat.mdf')
log on
	(name = test1_log,filename = 'd:\exercise\test1log.ldf')
go