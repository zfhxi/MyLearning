-- Subjoin 
use master
create database test1
on(filename='d:\exercise\test1dat.mdf')	--the mdf file path which you want add the db from
for attach;
go